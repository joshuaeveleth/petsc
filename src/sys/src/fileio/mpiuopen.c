
#ifndef lint
static char vcid[] = "$Id: mpiuopen.c,v 1.2 1996/02/08 18:26:06 bsmith Exp bsmith $";
#endif
/*
      Some PETSc utilites routines (beginning with MPIU_) to add simple
  IO capability to MPI.
*/
#include "petsc.h"
#include <stdio.h>
#include <stdarg.h>
#if defined(HAVE_STDLIB_H)
#include <stdlib.h>
#endif
#include "pinclude/petscfix.h"

/*@C
    PetscFOpen - The first process in the communicator opens a file,
                all others do nothing.

  Input Parameters:
.  comm - the communicator
.  name - the filename
.  mode - usually "w"
@*/
FILE *PetscFOpen(MPI_Comm comm,char *name,char *mode)
{
  int  rank;
  FILE *fd;
  MPI_Comm_rank(comm,&rank);
  if (!rank) fd = fopen(name,mode);
  else fd = 0;
  return fd;
}
/*@C
     PetscFClose - The first processor in the communicator closes a 
                  file, all others do nothing.

  Input Parameters:
.  comm - the communicator
.  fd - the file, opened with PetscFOpen()

@*/
int PetscFClose(MPI_Comm comm,FILE *fd)
{
  int  rank;
  MPI_Comm_rank(comm,&rank);
  if (!rank) return fclose(fd);
  else return 0;
}

