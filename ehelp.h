#ifndef EHELP_H_
#define EHELP_H_
const char *HELP_TEXT = "\
=>                      Edit 0.1 HELP INDEX\n\
.. The very basics\n\
.. Cursor movement\n\
.. File commands\n\
.. Miscellaneous character commands\n\
.. Mode commands\n\
.. Keys and commands\n\
.. Deleting and inserting\n\
.. Formatting\n\
.. Window commands\n\
.. Buffer commands\n\
.. Searching and replacing\n\
.. Accessing the operating system\n\
.. Macro commands\n\
.. Miscellaneous\n\
.. Functions\n\
.. System variables\n\
.. File name completion\n\
-------------------------------------------------------------------------------\n\
=>                      THE VERY BASICS\n\
Notations: ^X means <Ctrl> and X. The <Meta> key is <Esc> on most systems.\n\
Exiting:   ^G aborts almost any operation. ^X ^C will get you out of edit.\n\
\n\
A BUFFER is a named area containing a FILE being edited. Many buffers may\n\
be active at once. Many WINDOWS may be active at once on the screen. All\n\
windows may show different parts of the same buffer, or each may display a\n\
different one.\n\
-------------------------------------------------------------------------------\n\
=>                      CURSOR MOVEMENT\n\
Backward character ....      ^B         Forward character .....      ^F\n\
Previous word ......... Meta  B         Next word ............. Meta  F\n\
Beginning of line .....      ^A         End of line ...........      ^E\n\
Previous line .........      ^P         Next line .............      ^N\n\
Previous paragraph .... Meta  P         Next paragraph ........ Meta  N\n\
Previous page .........      ^Z         Next page .............      ^V\n\
Beginning of file ..... Meta  <         End of file ........... Meta  >\n\
-------------------------------------------------------------------------------\n\
=>                      FILE COMMANDS\n\
Find file .............   ^X ^F         Quick exit ............ Meta  Z\n\
View file .............   ^X ^V         Exit edit .............   ^X ^C\n\
Insert file ...........   ^X ^I\n\
Change file name ......   ^X  N         Filter buffer .........   ^X  #\n\
Save file .............   ^X ^D\n\
Read file .............   ^X ^R\n\
Write file ............   ^X ^W         Execute file .......... not bound\n\
-------------------------------------------------------------------------------\n\
=>                      MISCELLANEOUS CHARACTER COMMANDS\n\
Newline ...............      ^M         Transpose characters ..      ^T\n\
Newline and indent ....      ^J         Trim line .............   ^X ^T\n\
Open line .............      ^O\n\
Handle tab ............      ^I         Quote character .......   ^X  Q\n\
Insert space ..........      ^C\n\
Goto line ............. Meta  G         Abort command .........      ^G\n\
Goto matching fence ... Meta ^F\n\
-------------------------------------------------------------------------------\n\
=>                      MODE COMMANDS\n\
Add mode ..............   ^X  M         Add global mode	....... Meta  M\n\
Delete mode ...........   ^X ^M         Delete global mode .... Meta ^M\n\
OVER   :: Overwrite, don't insert       MAGIC  :: Match patterns in search\n\
WRAP   :: Automatic carriage return     ^ $  Beginning and end of line\n\
VIEW   :: View only, don't change       .    Any character   \\c   Character c\n\
CMODE  :: C program indenting           c*   Any number of character c\n\
EXACT  :: Match case in search          [ ]  Character class\n\
-------------------------------------------------------------------------------\n\
=>                      KEYS AND COMMANDS\n\
Bind to key ........... Meta  K         Help .................. Meta  ?\n\
Unbind key ............ Meta ^K         Apropos ............... Meta  A\n\
Describe key ..........   ^X  ?         Abort command .........      ^G\n\
Describe bindings ..... not bound\n\
Meta prefix ...........      Esc    ::  Although meta-prefix can be bound to\n\
Cntlx prefix ..........      ^X     ::  some other key, no other command can\n\
Execute named command . Meta  X     ::  be bound to Esc.\n\
-------------------------------------------------------------------------------\n\
=>                      DELETING AND INSERTING\n\
Delete previous character    ^H         Delete next character .      ^D\n\
Delete previous word .. Meta ^H         Delete next word ...... Meta  D\n\
Kill to end of line ...      ^K         Set mark .............. Meta Space\n\
Kill region ...........      ^W         Yank ..................      ^Y\n\
Kill paragraph ........ Meta ^W         Exchange point and mark   ^X ^X\n\
Delete blank lines ....   ^X ^O     ::  A region is defined as the area between\n\
Copy region ........... Meta  W     ::  the mark and the current position.\n\
-------------------------------------------------------------------------------\n\
=>                      FORMATTING\n\
Case word upper ....... Meta  U         Case word lower ....... Meta  L\n\
Case region upper .....   ^X ^U         Case region lower .....   ^X ^L\n\
Case word capitalize .. Meta  C         Trim line .............   ^X ^T\n\
                                        Detab line ............   ^X ^A\n\
Set fill column .......   ^X  F         Entab line ............   ^X ^E\n\
Fill paragraph ........ Meta  Q         Change screen size .... Meta ^D\n\
Justify paragraph ..... Meta  J         Change screen width ... Meta ^T\n\
-------------------------------------------------------------------------------\n\
=>                      WINDOW COMMANDS\n\
Split current window ..   ^X  2         Next window ...........   ^X  O\n\
Delete other windows ..   ^X  1         Previous window .......   ^X  P\n\
Delete window .........   ^X  0         Scroll next up ........ Meta ^Z\n\
Grow window ...........   ^X  Z         Scroll next down ...... Meta ^V\n\
Shrink window .........   ^X ^Z         Resize window .........   ^X  W\n\
Move window up ........   ^X ^P         Save window ........... not bound\n\
Move window down ......   ^X ^N         Restore window ........ not bound\n\
-------------------------------------------------------------------------------\n\
=>                      BUFFER COMMANDS\n\
Next buffer ...........   ^X  X         Buffer position .......   ^X  =\n\
Select buffer .........   ^X  B         Unmark buffer ......... Meta  ~\n\
List buffers ..........   ^X ^B\n\
Delete buffer .........   ^X  K         Write message ......... not bound\n\
Name buffer ........... Meta ^N         Clear message line .... not bound\n\
Filter buffer .........   ^X  #\n\
Pipe command ..........   ^X  @         Execute buffer ........ not bound\n\
-------------------------------------------------------------------------------\n\
=>                      SEARCHING AND REPLACING\n\
Search forward ........ Meta  S     ::  End string with Meta.\n\
Incremental search ....   ^X  S     ::  Search next ^X, stop Meta, cancel ^G.\n\
Search reverse ........      ^R\n\
Reverse incremental search              Hunt forward ..........  Alt-S\n\
.......................   ^X  R         Hunt backward .........  Alt-R\n\
Replace string ........ Meta  R\n\
Query replace string .. Meta ^R     ::  Yes/no Y/N, replace rest !, cancel ^G.\n\
-------------------------------------------------------------------------------\n\
=>                      ACCESSING THE OPERATING SYSTEM\n\
Quick exit ............ Meta  Z     ::  Write out all changed buffers and exit.\n\
Exit edit .............   ^X ^C     ::  Exit without automatic save.\n\
I shell ...............   ^X  C     ::  Start a new command processor.\n\
Shell command .........   ^X  !     ::  Execute one operating system command.\n\
Pipe command ..........   ^X  @     ::  Pipe command results to a new buffer. *\n\
Filter buffer .........   ^X  #     ::  Filter buffer through a program.      *\n\
Execute program .......   ^X  $     ::  * Not under VMS.\n\
-------------------------------------------------------------------------------\n\
=>                      MACRO COMMANDS\n\
Begin macro ...........   ^X  (\n\
End macro .............   ^X  )\n\
Execute macro .........   ^X  E\n\
Store macro ........... not bound\n\
Execute macro nn ...... not bound\n\
Store procedure ....... not bound\n\
Execute procedure ..... Meta ^E\n\
-------------------------------------------------------------------------------\n\
=>                      MISCELLANEOUS\n\
Universal argument ....      ^U         Set mark .............. Meta Space\n\
Clear and redraw ......      ^L         Exchange point and mark   ^X ^X\n\
Redraw display ........ Meta ^L\n\
Execute named command . Meta  X         Insert string ......... not bound\n\
Execute command line .. not bound       Overwrite string ...... not bound\n\
Set encryption key .... Meta  E         Wrap word ............. not bound\n\
Count words ........... Meta ^C         Update screen ......... not bound\n\
-------------------------------------------------------------------------------\n\
=>                      SYSTEM VARIABLES\n\
Set ................... Meta ^A         Current buffer name ... $cbufname\n\
Tabulator (4, 8)....... $tab            Current file name ..... $cfname\n\
Screen resolution ..... $sres       ::  NORMAL, CGA, EGA, VGA\n\
Display commands ...... $discmd     ::  true, false\n\
Scrolling enabled ..... $scroll     ::  true, false, can only be reset\n\
Scrolling movement .... $jump       ::  # lines, default 1, 0 = 1/2 page\n\
Page overlap .......... $overlap    ::  # lines, default 0, 0 = 1/3 page\n\
-------------------------------------------------------------------------------\n\
=>                      FUNCTIONS\n\
&neg, &abs, &add, &sub, &tim, &div, &mod ... Arithmetic\n\
&equ, &les, &gre ........................... Arithmetic comparisons\n\
&not, &and, &or ............................ Logical\n\
&lef s len, &rig s pos, &mid s pos len ..... Substring\n\
&cat, &len, &upp, &low, &asc, &chr ......... Other string operations\n\
&seq, &sle, &sgr ........................... String comparisons\n\
&sin ....................................... String index\n\
-------------------------------------------------------------------------------\n\
=>                      FILE NAME COMPLETION\n\
\n\
File name completion can be used with all file commands (find-file, view-file,\n\
...) but it works only under UNIX and MS-DOS. It is invoked by a <Space> or\n\
<Tab>. If there exist more than one possible completions they are displayed one\n\
by one. If the file name contains wild card characters, the name is expanded \n\
instead of simple completion. Special characters can be entered verbatim by\n\
prefixing them with ^V (or ^Q).\n\
-------------------------------------------------------------------------------\n\
";
#endif /* EHELP_H */
