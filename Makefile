all:
	gcc cbcp.c -o cbcp -lX11 -O3
	gcc cbps.c -o cbps -lX11 -O3

install:
	cp cbcp ~/bin
	cp cbps ~/bin

uninstall:
	rm -f ~/bin/cbcp 2>/dev/null
	rm -f ~/bin/cbps 2>/dev/null

clean:
	rm -f cbcp 2>/dev/null
	rm -f cbps 2>/dev/null
