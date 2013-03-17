#include <petsc-private/tsimpl.h>      /*I "petscts.h"  I*/

PetscFunctionList TSList              = NULL;
PetscBool         TSRegisterAllCalled = PETSC_FALSE;

#undef __FUNCT__
#define __FUNCT__ "TSSetType"
/*@C
  TSSetType - Sets the method for the timestepping solver.

  Collective on TS

  Input Parameters:
+ ts   - The TS context
- type - A known method

  Options Database Command:
. -ts_type <type> - Sets the method; use -help for a list of available methods (for instance, euler)

   Notes:
   See "petsc/include/petscts.h" for available methods (for instance)
+  TSEULER - Euler
.  TSSUNDIALS - SUNDIALS interface
.  TSBEULER - Backward Euler
-  TSPSEUDO - Pseudo-timestepping

   Normally, it is best to use the TSSetFromOptions() command and
   then set the TS type from the options database rather than by using
   this routine.  Using the options database provides the user with
   maximum flexibility in evaluating the many different solvers.
   The TSSetType() routine is provided for those situations where it
   is necessary to set the timestepping solver independently of the
   command line or options database.  This might be the case, for example,
   when the choice of solver changes during the execution of the
   program, and the user's application is taking responsibility for
   choosing the appropriate method.  In other words, this routine is
   not for beginners.

   Level: intermediate

.keywords: TS, set, type

@*/
PetscErrorCode  TSSetType(TS ts,TSType type)
{
  PetscErrorCode (*r)(TS);
  PetscBool      match;
  PetscErrorCode ierr;

  PetscFunctionBegin;
  PetscValidHeaderSpecific(ts, TS_CLASSID,1);
  ierr = PetscObjectTypeCompare((PetscObject) ts, type, &match);CHKERRQ(ierr);
  if (match) PetscFunctionReturn(0);

  ierr = PetscFunctionListFind(PetscObjectComm((PetscObject)ts),TSList, type,PETSC_TRUE, (void (**)(void)) &r);CHKERRQ(ierr);
  if (!r) SETERRQ1(PETSC_COMM_SELF,PETSC_ERR_ARG_UNKNOWN_TYPE, "Unknown TS type: %s", type);
  if (ts->ops->destroy) {
    ierr = (*(ts)->ops->destroy)(ts);CHKERRQ(ierr);

    ts->ops->destroy = NULL;
  }
  ierr = PetscMemzero(ts->ops,sizeof(*ts->ops));CHKERRQ(ierr);

  ts->setupcalled = PETSC_FALSE;

  ierr = PetscObjectChangeTypeName((PetscObject)ts, type);CHKERRQ(ierr);
  ierr = (*r)(ts);CHKERRQ(ierr);
#if defined(PETSC_HAVE_AMS)
  if (PetscAMSPublishAll) {
    ierr = PetscObjectAMSPublish((PetscObject)ts);CHKERRQ(ierr);
  }
#endif
  PetscFunctionReturn(0);
}

#undef __FUNCT__
#define __FUNCT__ "TSGetType"
/*@C
  TSGetType - Gets the TS method type (as a string).

  Not Collective

  Input Parameter:
. ts - The TS

  Output Parameter:
. type - The name of TS method

  Level: intermediate

.keywords: TS, timestepper, get, type, name
.seealso TSSetType()
@*/
PetscErrorCode  TSGetType(TS ts, TSType *type)
{
  PetscFunctionBegin;
  PetscValidHeaderSpecific(ts,TS_CLASSID,1);
  PetscValidPointer(type,2);
  *type = ((PetscObject)ts)->type_name;
  PetscFunctionReturn(0);
}

/*--------------------------------------------------------------------------------------------------------------------*/

#undef __FUNCT__
#define __FUNCT__ "TSRegister"
/*@C
  TSRegister - See TSRegisterDynamic()

  Level: advanced
@*/
PetscErrorCode  TSRegister(const char sname[], const char path[], const char name[], PetscErrorCode (*function)(TS))
{
  char           fullname[PETSC_MAX_PATH_LEN];
  PetscErrorCode ierr;

  PetscFunctionBegin;
  ierr = PetscStrcpy(fullname, path);CHKERRQ(ierr);
  ierr = PetscStrcat(fullname, ":");CHKERRQ(ierr);
  ierr = PetscStrcat(fullname, name);CHKERRQ(ierr);
  ierr = PetscFunctionListAdd(PETSC_COMM_WORLD,&TSList, sname, fullname, (void (*)(void))function);CHKERRQ(ierr);
  PetscFunctionReturn(0);
}

/*-------------------------------------------------------------------------------------------------------------------*/
#undef __FUNCT__
#define __FUNCT__ "TSRegisterDestroy"
/*@C
   TSRegisterDestroy - Frees the list of timestepping routines that were registered by TSRegister()/TSRegisterDynamic().

   Not Collective

   Level: advanced

.keywords: TS, timestepper, register, destroy
.seealso: TSRegister(), TSRegisterAll(), TSRegisterDynamic()
@*/
PetscErrorCode  TSRegisterDestroy(void)
{
  PetscErrorCode ierr;

  PetscFunctionBegin;
  ierr = PetscFunctionListDestroy(&TSList);CHKERRQ(ierr);
  TSRegisterAllCalled = PETSC_FALSE;
  PetscFunctionReturn(0);
}
