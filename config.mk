# chaosbot version
VERSION = 0.02

# paths
PREFIX = /usr/local
MANPREFIX = ${PREFIX}/share/man

# includes and libs
INCS = -I. -I/usr/include
LIBS = -L/usr/lib -lc -lircclient

# flags
CPPFLAGS = -D_BSD_SOURCE -D_POSIX_C_SOURCE=200809L -DVERSION=\"${VERSION}\"
CFLAGS   = -std=c99 -pedantic -lm -W -Wno-unused-parameter -Wno-unused-function \
	-Wno-unused-label -Wpointer-arith -Wformat -Wreturn-type -Wsign-compare \
	-Wmultichar -Wformat-nonliteral -Winit-self -Wuninitialized -Wno-deprecated \
	-Wformat-security -Wall -Werror -Wextra -Wno-missing-field-initializers \
	-Os ${INCS} ${CPPFLAGS}
LDFLAGS  = -s ${LIBS}

# compiler and linker
CC = cc
