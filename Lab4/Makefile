
CC = gcc

CFLAGS = -Wall -std=c99 -pedantic -g  

test: src/testMain.c src/tree.c src/balancedTreeAPI.c include/tree.h include/balancedTreeAPI.h 
	$(CC) $(CFLAGS) src/testMain.c src/balancedTreeAPI.c src/tree.c -Iinclude -o bin/testMe

cppcheck:
	cppcheck --enable=all --language=c --std=c99 --inconclusive --suppress=missingInclude src/*.c -i ./include

doxy: Doxyfile
	doxygen

clean:
	rm bin/*


