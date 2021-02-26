/*	spaw.c
 *
 *	Various operating system access commands.
 *
 *	<odified by Petri Kutvonen
 */

#include <stdio.h>
#include <unistd.h>

#include "edef.h"
#include "efunc.h"
#include "estruct.h"

#if VMS
#define EFN 0 /* Event flag.          */

#include <descrip.h>
#include <iodef.h>
#include <ssdef.h> /* Random headers.      */
#include <stsdef.h>

extern int oldmode[3]; /* In "termio.c"        */
extern int newmode[3]; /* In "termio.c"        */
extern short iochan;   /* In "termio.c"        */
#endif

#if V7 | USG | BSD
#include <signal.h>
#ifdef SIGWINCH
extern int chg_width, chg_height;
extern void sizesignal(int);
#endif
#endif

#if MSDOS & (MSC | TURBO)
#include <process.h>
#endif

/*
 * Create a subjob with a copy of the command intrepreter in it. When the
 * command interpreter exits, mark the screen as garbage so that you do a full
 * repaint. Bound to "^X C". The message at the start in VMS puts out a newline.
 * Under some (unknown) condition, you don't get one free when DCL starts up.
 */
int spawncli(int f, int n) {
#if V7 | USG | BSD
  char *cp;
#endif

  /* don't allow this command if restricted */
  if (restflag)
    return resterr();

#if VMS
  movecursor(term.t_nrow, 0); /* In last line.        */
  mlputs("(Starting DCL)\r\n");
  TTflush(); /* Ignore "ttcol".      */
  sgarbf = true;
  sys(NULL);
  sleep(1);
  mlputs("\r\n(Returning from DCL)\r\n");
  TTflush();
  sleep(1);
  return true;
#endif
#if MSDOS & (MSC | TURBO)
  movecursor(term.t_nrow, 0); /* Seek to last line.   */
  TTflush();
  TTkclose();
  shellprog("");
  TTkopen();
  sgarbf = true;
  return true;
#endif
#if V7 | USG | BSD
  movecursor(term.t_nrow, 0); /* Seek to last line.   */
  TTflush();
  TTclose();  /* stty to old settings */
  TTkclose(); /* Close "keyboard" */
  if ((cp = getenv("SHELL")) != NULL && *cp != '\0')
    system(cp);
  else
#if BSD
    system("exec /bin/csh");
#else
    system("exec /bin/sh");
#endif
  sgarbf = true;
  sleep(2);
  TTopen();
  TTkopen();
#ifdef SIGWINCH
  /*
   * This fools the update routines to force a full
   * redraw with complete window size checking.
   *		-lbt
   */
  chg_width = term.t_ncol;
  chg_height = term.t_nrow + 1;
  term.t_nrow = term.t_ncol = 0;
#endif
  return true;
#endif
}

#if BSD | __hpux | SVR4

int bktoshell(int f, int n) { /* suspend MicroEMACS and wait to wake up */
  vttidy();
  /******************************
          int pid;

          pid = getpid();
          kill(pid,SIGTSTP);
  ******************************/
  kill(0, SIGTSTP);
  return true;
}

void rtfrmshell(void) {
  TTopen();
  curwp->w_flag = WFHARD;
  sgarbf = true;
}
#endif

/*
 * Run a one-liner in a subjob. When the command returns, wait for a single
 * character to be typed, then mark the screen as garbage so a full repaint is
 * done. Bound to "C-X !".
 */
int spawn(int f, int n) {
  int s;
  char line[NLINE];

  /* don't allow this command if restricted */
  if (restflag)
    return resterr();

#if VMS
  if ((s = mlreply("!", line, NLINE)) != true)
    return s;
  movecursor(term.t_nrow, 0);
  TTflush();
  s = sys(line); /* Run the command.     */
  if (clexec == false) {
    mlputs("\r\n\n(End)"); /* Pause.               */
    TTflush();
    tgetc();
  }
  sgarbf = true;
  return s;
#endif
#if MSDOS
  if ((s = mlreply("!", line, NLINE)) != true)
    return s;
  movecursor(term.t_nrow, 0);
  TTkclose();
  shellprog(line);
  TTkopen();
  /* if we are interactive, pause here */
  if (clexec == false) {
    mlputs("\r\n(End)");
    tgetc();
  }
  sgarbf = true;
  return true;
#endif
#if V7 | USG | BSD
  if ((s = mlreply("!", line, NLINE)) != true)
    return s;
  TTflush();
  TTclose(); /* stty to old modes    */
  TTkclose();
  system(line);
  fflush(stdout); /* to be sure P.K.      */
  TTopen();

  if (clexec == false) {
    mlputs("(End)"); /* Pause.               */
    TTflush();
    while ((s = tgetc()) != '\r' && s != ' ')
      ;
    mlputs("\r\n");
  }
  TTkopen();
  sgarbf = true;
  return true;
#endif
}

/*
 * Run an external program with arguments. When it returns, wait for a single
 * character to be typed, then mark the screen as garbage so a full repaint is
 * done. Bound to "C-X $".
 */

int execprg(int f, int n) {
  int s;
  char line[NLINE];

  /* don't allow this command if restricted */
  if (restflag)
    return resterr();

#if VMS
  if ((s = mlreply("!", line, NLINE)) != true)
    return s;
  TTflush();
  s = sys(line);         /* Run the command.     */
  mlputs("\r\n\n(End)"); /* Pause.               */
  TTflush();
  tgetc();
  sgarbf = true;
  return s;
#endif

#if MSDOS
  if ((s = mlreply("$", line, NLINE)) != true)
    return s;
  movecursor(term.t_nrow, 0);
  TTkclose();
  execprog(line);
  TTkopen();
  /* if we are interactive, pause here */
  if (clexec == false) {
    mlputs("\r\n(End)");
    tgetc();
  }
  sgarbf = true;
  return true;
#endif

#if V7 | USG | BSD
  if ((s = mlreply("!", line, NLINE)) != true)
    return s;
  TTputc('\n'); /* Already have '\r'    */
  TTflush();
  TTclose(); /* stty to old modes    */
  TTkclose();
  system(line);
  fflush(stdout); /* to be sure P.K.      */
  TTopen();
  mlputs("(End)"); /* Pause.               */
  TTflush();
  while ((s = tgetc()) != '\r' && s != ' ')
    ;
  sgarbf = true;
  return true;
#endif
}

/*
 * Pipe a one line command into a window
 * Bound to ^X @
 */
int pipecmd(int f, int n) {
  int s;             /* return status from CLI */
  struct window *wp; /* pointer to new window */
  struct buffer *bp; /* pointer to buffer to zot */
  char line[NLINE];  /* command line send to shell */
  static char bname[] = "command";

  static char filnam[NSTRING] = "command";

#if MSDOS
  char *tmp;
  FILE *fp;
  int len;
#endif

  /* don't allow this command if restricted */
  if (restflag)
    return resterr();

#if MSDOS
  if ((tmp = getenv("TMP")) == NULL && (tmp = getenv("TEMP")) == NULL)
    strcpy(filnam, "command");
  else {
    strcpy(filnam, tmp);
    len = strlen(tmp);
    if (len <= 0 || filnam[len - 1] != '\\' && filnam[len - 1] != '/')
      strcat(filnam, "\\");
    strcat(filnam, "command");
  }
#endif

#if VMS
  mlwrite("Not available under VMS");
  return false;
#endif

  /* get the command to pipe in */
  if ((s = mlreply("@", line, NLINE)) != true)
    return s;

  /* get rid of the command output buffer if it exists */
  if ((bp = bfind(bname, false, 0)) != false) {
    /* try to make sure we are off screen */
    wp = wheadp;
    while (wp != NULL) {
      if (wp->w_bufp == bp) {
#if PKCODE
        if (wp == curwp)
          delwind(false, 1);
        else
          onlywind(false, 1);
        break;
#else
        onlywind(false, 1);
        break;
#endif
      }
      wp = wp->w_wndp;
    }
    if (zotbuf(bp) != true)

      return false;
  }
#if MSDOS
  strcat(line, " >>");
  strcat(line, filnam);
  movecursor(term.t_nrow, 0);
  TTkclose();
  shellprog(line);
  TTkopen();
  sgarbf = true;
  if ((fp = fopen(filnam, "r")) == NULL) {
    s = false;
  } else {
    fclose(fp);
    s = true;
  }
#endif

#if V7 | USG | BSD
  TTflush();
  TTclose(); /* stty to old modes    */
  TTkclose();
  strcat(line, ">");
  strcat(line, filnam);
  system(line);
  TTopen();
  TTkopen();
  TTflush();
  sgarbf = true;
  s = true;
#endif

  if (s != true)
    return s;

  /* split the current window to make room for the command output */
  if (splitwind(false, 1) == false)
    return false;

  /* and read the stuff in */
  if (getfile(filnam, false) == false)
    return false;

  /* make this window in VIEW mode, update all mode lines */
  curwp->w_bufp->b_mode |= MDVIEW;
  wp = wheadp;
  while (wp != NULL) {
    wp->w_flag |= WFMODE;
    wp = wp->w_wndp;
  }

  /* and get rid of the temporary file */
  unlink(filnam);
  return true;
}

/*
 * filter a buffer through an external DOS program
 * Bound to ^X #
 */
int filter_buffer(int f, int n) {
  int s;               /* return status from CLI */
  struct buffer *bp;   /* pointer to buffer to zot */
  char line[NLINE];    /* command line send to shell */
  char tmpnam[NFILEN]; /* place to store real file name */
  static char bname1[] = "fltinp";

  static char filnam1[] = "fltinp";
  static char filnam2[] = "fltout";

  /* don't allow this command if restricted */
  if (restflag)
    return resterr();

  if (curbp->b_mode & MDVIEW) /* don't allow this command if      */
    return rdonly();          /* we are in read only mode     */

#if VMS
  mlwrite("Not available under VMS");
  return false;
#endif

  /* get the filter name and its args */
  if ((s = mlreply("#", line, NLINE)) != true)
    return s;

  /* setup the proper file names */
  bp = curbp;
  strcpy(tmpnam, bp->b_fname); /* save the original name */
  strcpy(bp->b_fname, bname1); /* set it to our new one */

  /* write it out, checking for errors */
  if (writeout(filnam1) != true) {
    mlwrite("(Cannot write filter file)");
    strcpy(bp->b_fname, tmpnam);
    return false;
  }
#if MSDOS
  strcat(line, " <fltinp >fltout");
  movecursor(term.t_nrow - 1, 0);
  TTkclose();
  shellprog(line);
  TTkopen();
  sgarbf = true;
  s = true;
#endif

#if V7 | USG | BSD
  TTputc('\n'); /* Already have '\r'    */
  TTflush();
  TTclose(); /* stty to old modes    */
  TTkclose();
  strcat(line, " <fltinp >fltout");
  system(line);
  TTopen();
  TTkopen();
  TTflush();
  sgarbf = true;
  s = true;
#endif

  /* on failure, escape gracefully */
  if (s != true || (readin(filnam2, false) == false)) {
    mlwrite("(Execution failed)");
    strcpy(bp->b_fname, tmpnam);
    unlink(filnam1);
    unlink(filnam2);
    return s;
  }

  /* reset file name */
  strcpy(bp->b_fname, tmpnam); /* restore name */
  bp->b_flag |= BFCHG;         /* flag it as changed */

  /* and get rid of the temporary file */
  unlink(filnam1);
  unlink(filnam2);
  return true;
}

#if VMS
/*
 * Run a command. The "cmd" is a pointer to a command string, or NULL if you
 * want to run a copy of DCL in the subjob (this is how the standard routine
 * LIB$SPAWN works. You have to do wierd stuff with the terminal on the way in
 * and the way out, because DCL does not want the channel to be in raw mode.
 */
int sys(char *cmd) {
  struct dsc$descriptor cdsc;
  struct dsc$descriptor *cdscp;
  long status;
  long substatus;
  long iosb[2];

  status = SYS$QIOW(EFN, iochan, IO$_SETMODE, iosb, 0, 0, oldmode,
                    sizeof(oldmode), 0, 0, 0, 0);
  if (status != SS$_NORMAL || (iosb[0] & 0xFFFF) != SS$_NORMAL)
    return false;
  cdscp = NULL;      /* Assume DCL.          */
  if (cmd != NULL) { /* Build descriptor.    */
    cdsc.dsc$a_pointer = cmd;
    cdsc.dsc$w_length = strlen(cmd);
    cdsc.dsc$b_dtype = DSC$K_DTYPE_T;
    cdsc.dsc$b_class = DSC$K_CLASS_S;
    cdscp = &cdsc;
  }
  status = LIB$SPAWN(cdscp, 0, 0, 0, 0, 0, &substatus, 0, 0, 0);
  if (status != SS$_NORMAL)
    substatus = status;
  status = SYS$QIOW(EFN, iochan, IO$_SETMODE, iosb, 0, 0, newmode,
                    sizeof(newmode), 0, 0, 0, 0);
  if (status != SS$_NORMAL || (iosb[0] & 0xFFFF) != SS$_NORMAL)
    return false;
  if ((substatus & STS$M_SUCCESS) == 0) /* Command failed.      */
    return false;
  return true;
}
#endif

#if MSDOS & (TURBO | MSC)

/*
 * SHELLPROG: Execute a command in a subshell
 *
 * char *cmd;		Incoming command line to execute
 */
int shellprog(char *cmd) {
  char *shell;           /* Name of system command processor */
  char *p;               /* Temporary pointer */
  char swchar;           /* switch character to use */
  union REGS regs;       /* parameters for dos call */
  char comline[NSTRING]; /* constructed command line */

  /*  detect current switch character and set us up to use it */
  regs.h.ah = 0x37; /*  get setting data  */
  regs.h.al = 0x00; /*  get switch character  */
  intdos(&regs, &regs);
  swchar = (char)regs.h.dl;

  /*  get name of system shell  */
  if ((shell = getenv("COMSPEC")) == NULL) {
    return false; /*  No shell located  */
  }

  /* trim leading whitespace off the command */
  while (*cmd == ' ' || *cmd == '\t') /*  find out if null command */
    cmd++;

  /**  If the command line is not empty, bring up the shell  **/
  /**  and execute the command.  Otherwise, bring up the     **/
  /**  shell in interactive mode.   **/

  if (*cmd) {
    strcpy(comline, shell);
    strcat(comline, " ");
    comline[strlen(comline) + 1] = 0;
    comline[strlen(comline)] = swchar;
    strcat(comline, "c ");
    strcat(comline, cmd);
    return execprog(comline);
  } else
    return execprog(shell);
}

/*
 * EXECPROG:
 *	A function to execute a named program
 *	with arguments
 *
 * char *cmd;		Incoming command line to execute
 */
int execprog(char *cmd) {
  char *sp;            /* temporary string pointer */
  char f1[38];         /* FCB1 area (not initialized */
  char f2[38];         /* FCB2 area (not initialized */
  char prog[NSTRING];  /* program filespec */
  char tail[NSTRING];  /* command tail with length byte */
  union REGS regs;     /* parameters for dos call  */
  struct SREGS segreg; /* segment registers for dis call */
  struct pblock {      /* EXEC parameter block */
    short envptr;      /* 2 byte pointer to environment string */
    char *cline;       /* 4 byte pointer to command line */
    char *fcb1;        /* 4 byte pointer to FCB at PSP+5Ch */
    char *fcb2;        /* 4 byte pointer to FCB at PSP+6Ch */
  } pblock;
  char *flook();

  /* parse the command name from the command line */
  sp = prog;
  while (*cmd && (*cmd != ' ') && (*cmd != '\t'))
    *sp++ = *cmd++;
  *sp = 0;

  /* and parse out the command tail */
  while (*cmd && ((*cmd == ' ') || (*cmd == '\t')))
    ++cmd;
  *tail = (char)(strlen(cmd)); /* record the byte length */
  strcpy(&tail[1], cmd);
  strcat(&tail[1], "\r");

  /* look up the program on the path trying various extentions */
  if ((sp = flook(prog, true)) == NULL)
    if ((sp = flook(strcat(prog, ".exe"), true)) == NULL) {
      strcpy(&prog[strlen(prog) - 4], ".com");
      if ((sp = flook(prog, true)) == NULL)
        return false;
    }
  strcpy(prog, sp);

  /* get a pointer to this PSPs environment segment number */
  segread(&segreg);

  /* set up the EXEC parameter block */
  pblock.envptr = 0;   /* make the child inherit the parents env */
  pblock.fcb1 = f1;    /* point to a blank FCB */
  pblock.fcb2 = f2;    /* point to a blank FCB */
  pblock.cline = tail; /* parameter line pointer */

  /* and make the call */
  regs.h.ah = 0x4b; /* EXEC Load or Execute a Program */
  regs.h.al = 0x00; /* load end execute function subcode */
  segreg.ds = ((unsigned long)(prog) >> 16); /* program name ptr */
  regs.x.dx = (unsigned int)(prog);
  segreg.es = ((unsigned long)(&pblock) >> 16); /* set up param block ptr */
  regs.x.bx = (unsigned int)(&pblock);
#if TURBO | MSC
  intdosx(&regs, &regs, &segreg);
  if (regs.x.cflag == 0) {
    regs.h.ah = 0x4d;     /* get child process return code */
    intdos(&regs, &regs); /* go do it */
    rval = regs.x.ax;     /* save child's return code */
  } else
#if MSC
    rval = -1;
#else
    rval = -_doserrno; /* failed child call */
#endif
#endif
  return (rval < 0) ? false : true;
}
#endif
