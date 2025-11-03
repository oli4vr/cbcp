LIBX11 := $(shell find /usr/lib -name libX11.a)
LIBXCP := $(shell find /usr/lib -name libxcb.a)
LIBXAU := $(shell find /usr/lib -name libXau.a)
LIBXDMCP := $(shell find /usr/lib -name libXdmcp.a)
CFLAGS1 := -static-libgcc -O3
CFLAGS2 := -Wl,--as-needed -Wno-unused-command-line-argument

STATIC_LIBS := $(LIBX11) $(LIBXCP) $(LIBXAU) $(LIBXDMCP) 

all:
	gcc cbcp.c -o cbcp $(CFLAGS1) $(STATIC_LIBS) $(CFLAGS2)
	gcc cbps.c -o cbps $(CFLAGS1) $(STATIC_LIBS) $(CFLAGS2)
	./debpkg.sh </dev/null

install:
	echo "mkdir ~/bin 2>/dev/null; exit 0;" | /bin/bash
	cp cbcp ~/bin
	cp cbps ~/bin

uninstall:
	rm -f ~/bin/cbcp 2>/dev/null
	rm -f ~/bin/cbps 2>/dev/null

clean:
	rm -f cbcp 2>/dev/null
	rm -f cbps 2>/dev/null
	rm -f *.deb 2>/dev/null
