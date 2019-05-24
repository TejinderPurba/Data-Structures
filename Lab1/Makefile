
CC = gcc

CFLAGS = -Wall -std=c99 -pedantic -g  

test: src/testMain.c src/linkedList.c include/LinkedListAPI.h
	$(CC) $(CFLAGS) src/testMain.c src/linkedList.c  -Iinclude -o bin/linkedList

cppcheck:
	cppcheck --enable=all --language=c --std=c99 --inconclusive --suppress=missingInclude src/*.c -i ./include

doxy: Doxyfile
	doxygen

clean:
	rm bin/*


