# dwm - dynamic window manager
# See LICENSE file for copyright and license details.

include config.mk

SRC = drw.c dwm.c util.c
OBJ = ${SRC:.c=.o}

all: cans-dwm

.c.o:
	${CC} -c ${CFLAGS} $<

${OBJ}: config.mk

cans-dwm: ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	rm -f cans-dwm ${OBJ} cans-dwm-${VERSION}.tar.gz

dist: clean
	mkdir -p cans-dwm-${VERSION}
	cp -R LICENSE Makefile README config.mk\
		drw.h util.h ${SRC} dwm.png transient.c cans-dwm-${VERSION}
	tar -cf cans-dwm-${VERSION}.tar cans-dwm-${VERSION}
	gzip cans-dwm-${VERSION}.tar
	rm -rf cans-dwm-${VERSION}

install: all
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f cans-dwm ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/cans-dwm
	mkdir -p ${DESTDIR}${MANPREFIX}/man1

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/cans-dwm

.PHONY: all clean dist install uninstall
