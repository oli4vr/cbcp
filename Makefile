all:
	gcc cbcp.c -o cbcp -lX11 -O3
	gcc cbps.c -o cbps -lX11 -O3

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
