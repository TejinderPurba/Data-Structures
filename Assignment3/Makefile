
CC = gcc

CFLAGS = -Wall -std=c99 -pedantic -g  

main: src/priorityQueueMain.c src/heap.c src/extraFunctions.c src/priorityQueue.c include/extraFunctions.h include/heap.h include/priorityQueue.h
	$(CC) $(CFLAGS) src/priorityQueueMain.c src/heap.c src/extraFunctions.c src/priorityQueue.c -Iinclude -lncurses -o bin/priorityQueueMain

base:  src/priorityQueueBase.c src/heap.c src/extraFunctions.c src/priorityQueue.c include/extraFunctions.h include/heap.h include/priorityQueue.h
	$(CC) $(CFLAGS) src/priorityQueueBase.c src/heap.c src/extraFunctions.c src/priorityQueue.c -Iinclude -lncurses -o bin/priorityQueueBase

test:  src/testMain.c src/heap.c src/extraFunctions.c src/priorityQueue.c include/extraFunctions.h include/heap.h include/priorityQueue.h
	$(CC) $(CFLAGS) src/testMain.c src/heap.c src/extraFunctions.c src/priorityQueue.c -Iinclude -lncurses -o bin/testMe

cppcheck:
	cppcheck --enable=all --language=c --std=c99 --inconclusive --suppress=missingInclude src/*.c -i ./include

doxy: Doxyfile
	doxygen

clean:
	rm bin/*


