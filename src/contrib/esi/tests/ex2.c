

#include "petsc/vector.h"


extern int ESI_Vector_test(esi::Vector<double,int> *);
int main(int argc,char **args)
{
  esi::ErrorCode ierr;
  double         norm,dot;

  PetscInitialize(&argc,&args,0,0);

  esi::petsc::Map<int> *map = new esi::petsc::Map<int>(MPI_COMM_WORLD,5,PETSC_DECIDE);

  MPI_Comm *comm;
  map->getRunTimeModel("MPI",static_cast<void*>(comm));
  int rank;
  MPI_Comm_rank(*comm,&rank);


  esi::petsc::Vector<double,int> *vector = new esi::petsc::Vector<double,int>(map);

  ierr = ESI_Vector_test((vector));
  if (ierr) {printf("Error in ESI_Vector_Test()\n");return ierr;}

  esi::MapPartition<int> *gmap; vector->getMapPartition(gmap);

  delete map;

  vector->put(3.0);
  vector->scale(4.2);
  vector->norm1(norm);
  vector->dot((*vector),dot);

  PetscPrintf(*comm,"norm %g dot %g\n",norm,dot);

  double *array;

  vector->getCoefPtrReadWriteLock(array);
  array[0] = 22.3;
  vector->norm1(norm);
  vector->dot(*vector,dot);

  PetscPrintf(*comm,"norm %g dot %g\n",norm,dot);

  delete vector;
  PetscFinalize();

  return 0;
}
