#ifndef lint
static char vcid[] = "$Id: ex2.c,v 1.37 1996/08/15 12:45:25 bsmith Exp bsmith $";
#endif

static char help[] = "Tests vector scatter-gather operations.  Input arguments are\n\
  -n <length> : vector length\n\n";

#include "petsc.h"
#include "is.h"
#include "vec.h"
#include "sys.h"
#include <math.h>

int main(int argc,char **argv)
{
  int           n = 5, ierr, idx1[2] = {0,3}, idx2[2] = {1,4},flg;
  Scalar        one = 1.0, two = 2.0;
  Vec           x,y;
  IS            is1,is2;
  VecScatter    ctx = 0;

  PetscInitialize(&argc,&argv,(char*)0,help);
  OptionsGetInt(PETSC_NULL,"-n",&n,&flg);

  /* create two vector */
  ierr = VecCreateSeq(MPI_COMM_SELF,n,&x); CHKERRA(ierr);
  ierr = VecDuplicate(x,&y); CHKERRA(ierr);

  /* create two index sets */
  ierr = ISCreateGeneral(MPI_COMM_SELF,2,idx1,&is1); CHKERRA(ierr);
  ierr = ISCreateGeneral(MPI_COMM_SELF,2,idx2,&is2); CHKERRA(ierr);

  ierr = VecSet(&one,x); CHKERRA(ierr);
  ierr = VecSet(&two,y); CHKERRA(ierr);
  ierr = VecScatterCreate(x,is1,y,is2,&ctx); CHKERRA(ierr);
  ierr = VecScatterBegin(x,y,INSERT_VALUES,SCATTER_FORWARD,ctx);CHKERRA(ierr);
  ierr = VecScatterEnd(x,y,INSERT_VALUES,SCATTER_FORWARD,ctx); CHKERRA(ierr);
  
  ierr = VecView(y,VIEWER_STDOUT_SELF); CHKERRA(ierr);

  ierr = VecScatterBegin(y,x,INSERT_VALUES,SCATTER_FORWARD,ctx);CHKERRA(ierr);
  ierr = VecScatterEnd(y,x,INSERT_VALUES,SCATTER_FORWARD,ctx); CHKERRA(ierr);
  ierr = VecScatterDestroy(ctx); CHKERRA(ierr);

  PetscPrintf(MPI_COMM_SELF,"-------\n");
  ierr = VecView(x,VIEWER_STDOUT_SELF); CHKERRA(ierr);

  ierr = ISDestroy(is1); CHKERRA(ierr);
  ierr = ISDestroy(is2); CHKERRA(ierr);

  ierr = VecDestroy(x); CHKERRA(ierr);
  ierr = VecDestroy(y); CHKERRA(ierr);

  PetscFinalize();
  return 0;
}
 
