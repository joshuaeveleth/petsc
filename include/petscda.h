/* $Id: da.h,v 1.21 1996/02/24 19:07:45 balay Exp bsmith $ */

/*
      Regular array object, for easy parallelism of simple grid 
   problems on regular distributed arrays.
*/
#if !defined(__DA_PACKAGE)
#define __DA_PACKAGE
#include "petsc.h"
#include "vec.h"

#define DA_COOKIE PETSC_COOKIE+14

typedef struct _DA* DA;
typedef enum { DA_STENCIL_STAR, DA_STENCIL_BOX } DAStencilType;
typedef enum { DA_NONPERIODIC, DA_XPERIODIC, DA_YPERIODIC, DA_XYPERIODIC,
               DA_XYZPERIODIC, DA_XZPERIODIC, DA_YZPERIODIC,DA_ZPERIODIC} 
               DAPeriodicType;

extern int   DACreate1d(MPI_Comm,DAPeriodicType,int,int,int,DA *);
extern int   DACreate2d(MPI_Comm,DAPeriodicType,DAStencilType,int,int,int,
                                                           int,int,int,DA *);
extern int   DACreate3d(MPI_Comm,DAPeriodicType,DAStencilType, 
                        int,int,int,int,int,int,int,int, DA *);

extern int   DADestroy(DA);

extern int   DAView(DA,Viewer);

extern int   DAGlobalToLocalBegin(DA,Vec, InsertMode,Vec);
extern int   DAGlobalToLocalEnd(DA,Vec, InsertMode,Vec);
extern int   DALocalToLocalBegin(DA,Vec, InsertMode,Vec);
extern int   DALocalToLocalEnd(DA,Vec, InsertMode,Vec);
extern int   DALocalToGlobal(DA,Vec, InsertMode,Vec);

extern int   DAGetDistributedVector(DA,Vec*);
extern int   DAGetLocalVector(DA,Vec*);
extern int   DAGetCorners(DA,int*,int*,int*,int*,int*,int*);
extern int   DAGetGhostCorners(DA,int*,int*,int*,int*,int*,int*);
extern int   DAGetInfo(DA ,int *,int *,int *,int *,int *,int *,int *,int *,int *);
extern int   DARefine(DA,DA*);

extern int   DAGetGlobalIndices(DA,int*,int**);
extern int   DAGetScatter(DA,VecScatter*,VecScatter*,VecScatter*);

#endif
