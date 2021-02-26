/*	edef.h
 *
 *	Global variable definitions
 *
 *	written by Dave G. Conroy
 *	modified by Steve Wilhite, George Jones
 *	greatly modified by Daniel Lawrence
 *	modified by Petri Kutvonen
 */
#ifndef EDEF_H_
#define EDEF_H_

#include <stdlib.h>
#include <string.h>

#include "estruct.h"

/* Some global fuction declarations. */
typedef int (*fn_t)(int, int);

/* Initialized global external declarations. */

extern char *cname[];            /* names of colors */
extern char *execstr;            /* pointer to string to execute */
extern char *fline;              /* dynamic return line */
extern char *mode2name[];        /* text names of modes */
extern char *modename[];         /* text names of modes */
extern char errorm[];            /* error literal */
extern char falsem[];            /* false litereal */
extern char golabel[];           /* current line to go to */
extern char modecode[];          /* letters to represent modes */
extern char palstr[];            /* palette string */
extern char pat[];               /* Search pattern */
extern char rpat[];              /* Replacement pattern */
extern char truem[];             /* true literal */
extern int *kbdend;              /* ptr to end of the keyboard */
extern int *kbdptr;              /* current position in keyboard buf */
extern int abortc;               /* current abort command char*/
extern int clexec;               /* command line execution flag */
extern int cmdstatus;            /* last command status */
extern int cryptflag;            /* currently encrypting? */
extern int ctlxc;                /* current control X prefix char */
extern int discmd;               /* display command flag */
extern int disinp;               /* display input characters */
extern int eolexist;             /* does clear to EOL exist? */
extern int execlevel;            /* execution IF level */
extern int fillcol;              /* Fill column */
extern int flen;                 /* current length of fline */
extern int flickcode;            /* do flicker supression? */
extern int gacount;              /* count until next ASAVE */
extern int gasave;               /* global ASAVE size */
extern int gbcolor;              /* global backgrnd color (black) */
extern int gfcolor;              /* global forgrnd color (white) */
extern int gflags;               /* global control flag */
extern int gmode;                /* global editor mode */
extern int justflag;             /* justify, don't fill */
extern int kbdm[];               /* Holds kayboard macro data */
extern int kbdmode;              /* current keyboard macro mode */
extern int kbdrep;               /* number of repetitions */
extern int kused;                /* # of bytes used in KB */
extern int lastkey;              /* last keystoke */
extern int lbound;               /* leftmost column of current displayed line */
extern int macbug;               /* macro debuging flag */
extern int metac;                /* current meta character */
extern int mpresf;               /* Stuff in message line */
extern int mstore;               /* storing text to macro flag */
extern int nullflag;             /* */
extern int overlap;              /* line overlap in forw/back page */
extern int quotec;               /* quote char during mlreply() */
extern int reptc;                /* current universal repeat char */
extern int restflag;             /* restricted use? */
extern int revexist;             /* does reverse video exist? */
extern int rval;                 /* return value of a subprocess */
extern int saveflag;             /* Flags, saved with the $target var */
extern int scrollcount;          /* number of lines to scroll */
extern int seed;                 /* random number seed */
extern int sgarbf;               /* State of screen unknown */
extern int tabmask;              /* */
extern int taboff;               /* tab offset for display */
extern int ttcol;                /* Column location of HW cursor */
extern int ttrow;                /* Row location of HW cursor */
extern int vtcol;                /* Column location of SW cursor */
extern int vtrow;                /* Row location of SW cursor */
extern long envram;              /* # of bytes current in use by malloc */
extern struct buffer *bstore;    /* buffer to store macro text to */
extern struct key_tab keytab[];  /* key bind to functions table */
extern struct kill *kbufh;       /* kill buffer header pointer*/
extern struct kill *kbufp;       /* current kill buffer chunk pointer */
extern struct name_bind names[]; /* name to function table */
extern struct window *swindow;   /* saved window pointer */

/* Uninitialized global external declarations. */

extern char *dname[]; /* Directive name table.        */
extern char *patmatch;
extern char pat[];            /* Search pattern. */
extern char rpat[];           /* Replacement pattern. */
extern char sres[NBUFN];      /* Current screen resolution. */
extern char tap[];            /* Reversed pattern array. */
extern int curcol;            /* Cursor column */
extern int curgoal;           /* Goal for C-P, C-N */
extern int currow;            /* Cursor row */
extern int lastflag;          /* Flags, last command */
extern int matchoff;
extern int thisflag;          /* Flags, this command */
extern struct buffer *bheadp; /* Head of list of buffers */
extern struct buffer *blistp; /* Buffer for C-X C-B */
extern struct buffer *curbp;  /* Current buffer */
extern struct line *matchline;
extern struct window *curwp;  /* Current window */
extern struct window *wheadp; /* Head of list of windows */
extern unsigned int matchlen;
extern unsigned int mlenold;

/* Vars needed for macro debugging output. */
extern char outline[]; /* Global string to hold debug line text. */

/* Terminal table defined only in term.c */
extern struct terminal term;

#endif /* EDEF_H_ */
