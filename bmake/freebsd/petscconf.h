#ifdef PETSC_RCS_HEADER
"$Id: petscconf.h,v 1.22 2001/03/14 18:14:28 balay Exp $"
"Defines the configuration for this machine"
#endif

#if !defined(INCLUDED_PETSCCONF_H)
#define INCLUDED_PETSCCONF_H

#define PARCH_freebsd
#define PETSC_ARCH_NAME "freebsd"

#define PETSC_HAVE_POPEN
#define PETSC_HAVE_LIMITS_H
#define PETSC_HAVE_PWD_H 
#define PETSC_HAVE_STDLIB_H 
#define PETSC_HAVE_STRING_H 
#define PETSC_HAVE_DRAND48  
#define PETSC_HAVE_GETDOMAINNAME 
#define PETSC_HAVE_UNISTD_H  
#define PETSC_HAVE_UNAME 
#define PETSC_HAVE_SYS_TIME_H
#define PETSC_HAVE_GETCWD
#define PETSC_HAVE_SLEEP
#define PETSC_HAVE_SYS_PARAM_H
#define PETSC_HAVE_SYS_STAT_H

#define PETSC_BITS_PER_BYTE 8

#define PETSC_HAVE_READLINK
#define PETSC_HAVE_MEMMOVE
#define PETSC_HAVE_TEMPLATED_COMPLEX

#define PETSC_HAVE_FORTRAN_UNDERSCORE_UNDERSCORE
#define PETSC_HAVE_FORTRAN_UNDERSCORE

#if (__GNUC__ == 2 && __GNUC_MINOR__ >= 7)
#define PETSC_HAVE_VPRINTF_CHAR
#endif
#define PETSC_HAVE_SYS_RESOURCE_H
#define PETSC_SIZEOF_VOID_P 4
#define PETSC_SIZEOF_INT 4
#define PETSC_SIZEOF_DOUBLE 8

#define PETSC_USE_DYNAMIC_LIBRARIES 1
#define PETSC_MISSING_DREAL
#define PETSC_PRINTF_FORMAT_CHECK(a,b) __attribute__ ((format (printf, a,b)))

#endif
