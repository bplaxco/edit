PROGRAM=edit

uname_S := $(shell sh -c 'uname -s 2>/dev/null || echo not')

SRC=basic.c bind.c buffer.c crypt.c display.c eval.c exec.c \
	file.c fileio.c ibmpc.c input.c isearch.c line.c lock.c main.c \
	pklock.c posix.c random.c region.c search.c spawn.c tcap.c \
	termio.c window.c word.c names.c globals.c version.c \
	usage.c wrapper.c utf8.c util.c

OBJ=basic.o bind.o buffer.o crypt.o display.o eval.o exec.o \
	file.o fileio.o ibmpc.o input.o isearch.o line.o lock.o main.o \
	pklock.o posix.o random.o region.o search.o spawn.o tcap.o \
	termio.o window.o word.o names.o globals.o version.o \
	usage.o wrapper.o utf8.o util.o

CC=clang
WARNINGS=-Wall -Wstrict-prototypes
CFLAGS=-O2 $(WARNINGS) -g

ifeq ($(uname_S),Linux)
 DEFINES=-DAUTOCONF -DPOSIX -DUSG -D_XOPEN_SOURCE=600 -D_GNU_SOURCE
endif

ifeq ($(uname_S),FreeBSD)
 DEFINES=-DAUTOCONF -DPOSIX -DSYSV -D_FREEBSD_C_SOURCE -D_BSD_SOURCE -D_SVID_SOURCE -D_XOPEN_SOURCE=600
endif

ifeq ($(uname_S),Darwin)
 DEFINES=-DAUTOCONF -DPOSIX -DSYSV -D_DARWIN_C_SOURCE -D_BSD_SOURCE -D_SVID_SOURCE -D_XOPEN_SOURCE=600
endif

LIBS=-lcurses
BINDIR=/usr/bin
LIBDIR=/usr/lib

$(PROGRAM): $(OBJ)
	@echo "  LINK    " $@
	$(CC) $(LDFLAGS) $(DEFINES) -o $@ $(OBJ) $(LIBS)

clean:
	rm -f $(PROGRAM) tags *.o

format:
	clang-format -i *.c *.h

test: clean $(PROGRAM)

install: $(PROGRAM)
	cp $(PROGRAM) ${BINDIR}
	cp emacs.rc ${LIBDIR}/.emacsrc
	chmod 755 ${BINDIR}/$(PROGRAM)
	chmod 644 ${LIBDIR}/.emacsrc

tags:	${SRC}
	@rm -f tags
	ctags ${SRC}

.c.o:
	${CC} ${CFLAGS} ${DEFINES} -c $*.c

basic.o: basic.c estruct.h edef.h
bind.o: bind.c estruct.h edef.h epath.h
buffer.o: buffer.c estruct.h edef.h
crypt.o: crypt.c estruct.h edef.h
display.o: display.c estruct.h edef.h utf8.h
eval.o: eval.c estruct.h edef.h evar.h
exec.o: exec.c estruct.h edef.h
file.o: file.c estruct.h edef.h
fileio.o: fileio.c estruct.h edef.h
ibmpc.o: ibmpc.c estruct.h edef.h
input.o: input.c estruct.h edef.h
isearch.o: isearch.c estruct.h edef.h
line.o: line.c estruct.h edef.h
lock.o: lock.c estruct.h edef.h
main.o: main.c estruct.h efunc.h edef.h ebind.h
pklock.o: pklock.c estruct.h
posix.o: posix.c estruct.h utf8.h
random.o: random.c estruct.h edef.h
region.o: region.c estruct.h edef.h
search.o: search.c estruct.h edef.h
spawn.o: spawn.c estruct.h edef.h
tcap.o: tcap.c estruct.h edef.h
termio.o: termio.c estruct.h edef.h
utf8.o: utf8.c utf8.h
window.o: window.c estruct.h edef.h
word.o: word.c estruct.h edef.h
