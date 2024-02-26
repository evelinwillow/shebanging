bindir = /usr/local/bin/

warcrime:
	gcc -w src/a.in.c -o shebanging

install:
	sudo gcc -w src/a.in.c -o $(bindir)shebanging
