all: lib
exe:	solution.h main.c lib
	gcc main.c -fPIC -L. -lsolution -o hello

lib:	solution.h solution.c
	gcc -shared solution.c -fPIC -o libsolution.so
