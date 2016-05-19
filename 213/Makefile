all:	exe
exe:	solution.c
	gcc solution.c -Wl,-rpath=./ -fPIC -ldl -o solution

lib:	lib_test.c
	gcc -shared lib_test.c -fPIC -o libtest.so
