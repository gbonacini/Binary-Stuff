all: websrv


websrv: websrv.asm
	@nasm -f elf64 websrv.asm
	@ld -o websrv websrv.o

clean:
	rm -f websrv.o websrv 

dist: websrv.asm makefile
	tar czvf webserver.tar.gz websrv.asm makefile
