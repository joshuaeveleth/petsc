#ifndef lint
static char vcid[] = "$Id: dlinegw.c,v 1.3 1996/03/10 17:28:57 bsmith Exp bsmith $";
#endif
/*
       Provides the calling sequences for all the basic Draw routines.
*/
#include "drawimpl.h"  /*I "draw.h" I*/

/*@
   DrawLineGetWidth - Gets the line width for future draws.  The width is
   relative to the user coordinates of the window; 0.0 denotes the natural
   width; 1.0 denotes the interior viewport. 

   Input Parameter:
.  draw - the drawing context

   Output Parameter:
.  width - the width in user coordinates

.keywords:  draw, line, get, width

.seealso:  DrawLineSetWidth()
@*/
int DrawLineGetWidth(Draw draw,double *width)
{
  PetscValidHeaderSpecific(draw,DRAW_COOKIE);
  if (draw->type == NULLWINDOW) return 0;
  return (*draw->ops.linegetwidth)(draw,width);
}

