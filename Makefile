# chaosbot Makefile
# https://github.com/AMD1212/chaosbot

# directory setup
DESTDIR ?=
prefix  ?= /usr
bindir  ?= $(prefix)/bin

# used programs
INSTALL		:= install
INSTALL_DATA	:= $(INSTALL) -m 644
INSTALL_DIR	:= $(INSTALL) -m 755 -d
INSTALL_PROGRAM	:= $(INSTALL) -m 755
RM		:= rm -f

# default compiler & flags
CC	?= gcc
CFLAGS  ?= -O2

# When debugging, add the following:
CFLAGS := -O -g

CFLAGS  += -Wall
LDFLAGS	+= -lircclient

# make it ;-)
PROGRAM_TARGETS	:= chaosbot

all: chaosbot

chaosbot: chaosbot.o
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) chaosbot.o

chaosbot.o: chaosbot.c chaosbot.h
	$(CC) -c -o $@ chaosbot.c $(CFLAGS)

install:
	$(INSTALL_DIR) $(DESTDIR)$(bindir)
	for program in $(PROGRAM_TARGETS) ; do \
		$(INSTALL_PROGRAM) $$program $(DESTDIR)$(bindir) ; done

clean:
	${RM} chaosbot *.o
