#ifndef MAIN_SP_H
#define MAIN_SP_H

/* ========================================================================= */
/* external functions and definitions imported from main program to game_sp  */
/* ========================================================================= */

#include "../engines.h"


/* ========================================================================= */
/* functions and definitions that are exported from game_sp to main program  */
/* ========================================================================= */

#include "export.h"


/* ========================================================================= */
/* internal functions and definitions that are not exported to main program  */
/* ========================================================================= */


/* ------------------------------------------------------------------------- */
/* constant definitions                                                      */
/* ------------------------------------------------------------------------- */

/* screen sizes and positions for SP engine */

#define ORIG_TILEX		16
#define ORIG_TILEY		16

#define ZOOM_FACTOR		2

#define TILEX			(ORIG_TILEX		* ZOOM_FACTOR)
#define TILEY			(ORIG_TILEY		* ZOOM_FACTOR)

#define ORIG_SCR_MENUX		20
#define ORIG_SCR_MENUY		12
#define SCR_MENUX		17
#define SCR_MENUY		12
#define SCR_FIELDX		17
#define SCR_FIELDY		17
#define MAX_BUF_XSIZE		(SCR_FIELDX + 2)
#define MAX_BUF_YSIZE		(SCR_FIELDY + 2)

/* often used screen positions */
#define SX			8
#define SY			8
#define SXSIZE			(SCR_FIELDX * TILEX)
#define SYSIZE			(SCR_FIELDY * TILEY)


/* ------------------------------------------------------------------------- */
/* data structure definitions                                                */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/* exported variables                                                        */
/* ------------------------------------------------------------------------- */

extern struct LevelInfo_SP native_sp_level;

extern struct GameInfo_SP game_sp;

extern Bitmap *screenBitmap;

extern Bitmap *sp_objects;


/* ------------------------------------------------------------------------- */
/* exported functions                                                        */
/* ------------------------------------------------------------------------- */

#endif	/* MAIN_SP_H */