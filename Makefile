# chaosbot - a small irc bot
# See LICENSE file for copyright and license details.


include config.mk

SRC = chaosbot.c
OBJ = ${SRC:.c=.o}

all: options chaosbot

options:
	@echo chaosbot build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"

.c.o:
	@echo CC -c $<
	@${CC} -c $< ${CFLAGS}

config.h:
	@echo creating $@ from config.def.h
	@cp config.def.h $@

${OBJ}: config.h config.mk

chaosbot: chaosbot.o
	@echo CC -o $@
	@${CC} -o $@ chaosbot.o ${LDFLAGS}

clean:
	@echo cleaning
	@rm -f chaosbot ${OBJ} chaosbot-${VERSION}.tar.gz

dist: clean
	@echo creating dist tarball
	@mkdir -p chaosbot-${VERSION}
	@cp LICENSE Makefile README config.mk ${SRC} chaosbot-${VERSION}
	@tar -cf chaosbot-${VERSION}.tar chaosbot-${VERSION}
	@gzip chaosbot-${VERSION}.tar
	@rm -rf chaosbot-${VERSION}

install: all
	@echo installing executables to ${DESTDIR}${PREFIX}/bin
	@mkdir -p ${DESTDIR}${PREFIX}/bin
	@cp -f chaosbot ${DESTDIR}${PREFIX}/bin
	@chmod 755 ${DESTDIR}${PREFIX}/bin/chaosbot

uninstall:
	@echo removing executables from ${DESTDIR}${PREFIX}/bin
	@rm -f ${DESTDIR}${PREFIX}/bin/chaosbot

.PHONY: all options clean dist install uninstall
