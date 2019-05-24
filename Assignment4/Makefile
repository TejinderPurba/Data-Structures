
CC = gcc

CFLAGS = -Wall -std=c99 -pedantic -g  

main: src/binTreeMain.c src/tree.c src/balancedTreeAPI.c src/extraFunctions.c include/tree.h include/balancedTreeAPI.h include/extraFunctions.h
	$(CC) $(CFLAGS) src/binTreeMain.c src/balancedTreeAPI.c src/tree.c src/extraFunctions.c -Iinclude -lncurses -o bin/binTreeMain

test: src/testMain.c src/tree.c src/balancedTreeAPI.c src/extraFunctions.c include/tree.h include/balancedTreeAPI.h include/extraFunctions.h
	$(CC) $(CFLAGS) src/testMain.c src/balancedTreeAPI.c src/tree.c src/extraFunctions.c -Iinclude -lncurses -o bin/testMe

cppcheck:
	cppcheck --enable=all --language=c --std=c99 --inconclusive --suppress=missingInclude src/*.c -i ./include

doxy: Doxyfile
	doxygen

clean:
	rm bin/*


