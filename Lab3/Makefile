
CC = gcc

CFLAGS = -Wall -std=c99 -pedantic -g  

test: src/testMain.c src/extraFunctions.c src/heap.c include/extraFunctions.h include/heap.h  
	$(CC) $(CFLAGS) src/testMain.c src/extraFunctions.c src/heap.c -Iinclude -o bin/testMe

cppcheck:
	cppcheck --enable=all --language=c --std=c99 --inconclusive --suppress=missingInclude src/*.c -i ./include

doxy: Doxyfile
	doxygen

clean:
	rm bin/*


