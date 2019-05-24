
CC = gcc

CFLAGS = -Wall -std=c99 -pedantic -g  

main: src/queueMain.c src/queueADT.c src/linkedList.c include/LinkedListAPI.h include/QueueADT.h include/Functions.h
	$(CC) $(CFLAGS) src/queueMain.c src/queueADT.c src/linkedList.c src/functions.c -Iinclude -o bin/queueMain

test: src/queueTesting.c src/queueADT.c src/linkedList.c include/LinkedListAPI.h include/QueueADT.h include/Functions.h
	$(CC) $(CFLAGS) src/queueTesting.c src/queueADT.c src/linkedList.c src/functions.c -Iinclude -o bin/queueTesting

cppcheck:
	cppcheck --enable=all --language=c --std=c99 --inconclusive --suppress=missingInclude src/*.c -i ./include

doxy: Doxyfile
	doxygen

clean:
	rm bin/*


