
CC = gcc

CFLAGS = -Wall -std=c99 -pedantic -g  

main: src/hashTableMain.c src/hashTableAPI.c src/extraFunctions.c include/HashTableAPI.h include/ExtraFunctions.h
	$(CC) $(CFLAGS) src/hashTableMain.c src/hashTableAPI.c src/extraFunctions.c -Iinclude -lncurses -o bin/hashTableMain

test: src/testMain.c src/hashTableAPI.c src/extraFunctions.c include/HashTableAPI.h include/ExtraFunctions.h
	$(CC) $(CFLAGS) src/testMain.c src/hashTableAPI.c src/extraFunctions.c -Iinclude -lncurses -o bin/testMe

cppcheck:
	cppcheck --enable=all --language=c --std=c99 --inconclusive --suppress=missingInclude src/*.c -i ./include

doxy: Doxyfile
	doxygen

clean:
	rm bin/*


