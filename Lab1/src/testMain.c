/**
 * @file testMain.c
 * @author Tejinder Purba
 * @date May 29th 2017
 * @brief File containing a main for testing of doubly-linked list functions
 **/

#include <stdio.h>
#include <stdlib.h>
#include "LinkedListAPI.h"

void printFunction(void *one) 
{
    Node *test = one;
    printf("%d ", *(int*)test->data); 
  
    return;
}

void deleteFunction(void *one) 
{
    Node *test = one;
    free(test);
    
    return;
}

int compareFunction(const void *one, const void *two) 
{

    return *(int*)one - *(int*)two; 

}


int main() 
{

    List *test = initializeList(printFunction, deleteFunction, compareFunction);
    int *d1 = NULL, *d2 = NULL, *d3 = NULL, *d4 = NULL;
    void *store;
    int returnValue = 0;
    d1 = malloc(sizeof(int));
    d2 = malloc(sizeof(int));
    d3 = malloc(sizeof(int));
    d4 = malloc(sizeof(int));

    *d1 = 45;
    *d2 = 123;
    *d3 = 63;
    *d4 = 20;

    insertFront(test, (void*)d1);
    insertFront(test, (void*)d2);
    insertBack(test, (void*)d3);
    insertBack(test, (void*)d4);
    printf("\nTests:\n\nForwards Expected: 123 45 63 20 |  Actual: ");
    printForward(test);
    printf("\n\nBackwards Expected: 20 63 45 123 |  Actual: ");
    printBackwards(test);
    printf("\n");

    deleteList(test);
    printf("\nForwards NULL Expected: |  Actual: ");
    printForward(test);
    printf("\n\nBackwards NULL Expected: |  Actual: ");
    printBackwards(test);
    printf("\n");

    insertFront(test, (void*)d1);
    insertFront(test, (void*)d2);
    insertBack(test, (void*)d3);
    insertBack(test, (void*)d4);
    store = getFromFront(test);
    printf("\nGetFromFront Expected: 123 |  Actual: %d\n", *(int*)store);
    store = getFromBack(test);
    printf("\nGetFromBack Expected: 20 |  Actual: %d\n", *(int*)store);

    printf("\nDeleteDataFromList Expected: 123 45 20 |  Actual: ");
    deleteDataFromList(test, (void*)d3);
    printForward(test);
    printf("\n");

    printf("\nDeleteList Expected: |  Actual:  ");
    deleteList(test);
    printForward(test);
    printf("\n");

    insertSorted(test, (void*)d1);
    insertSorted(test, (void*)d2);
    insertSorted(test, (void*)d3);
    insertSorted(test, (void*)d4);
    printf("\nInsertSorted Expected: 20 45 63 123 |  Actual: ");
    printForward(test);
    printf("\n");

    deleteList(test);
    printf("\nInsertFront/InsertSorted Expected 20 63 45 123 123 |  Actual: ");
    insertFront(test, (void*)d1);
    insertFront(test, (void*)d2);
    insertSorted(test, (void*)d4);
    insertSorted(test, (void*)d3);
    insertSorted(test, (void*)d2);
    printForward(test);
    printf("\n");

    deleteList(test);
    printf("\nInsertFront Expected 123 45 63 |  Actual ");
    insertFront(test, (void*)d3);
    insertFront(test, (void*)d1);
    insertFront(test, (void*)d2);
    printForward(test);
    printf("\n\nInsertBack Expected 123 45 63 20 45 |  Actual: ");
    insertBack(test, (void*)d4);
    insertBack(test, (void*)d1);
    printForward(test);
    printf("\n");

    deleteList(test);
    *d1 = 0;
    *d2 = 5;
    printf("\nChanged Data Expected: 5 0 |  Actual: ");
    insertFront(test, (void*)d1);
    insertFront(test, (void*)d2);
    printForward(test);
    printf("\n");
    *d1 = 45;
    *d2 = 123;

    deleteList(test);
    insertFront(test, (void*)d1);
    insertFront(test, (void*)d4);
    insertFront(test, (void*)d3);
    returnValue = deleteDataFromList(test, (void*)d2);
    printf("\nDeletion Data Not Found Expected: Return: -1 |  Actual: ");
    printf("Return: %d", returnValue);
    printf("\n");

    deleteList(test);
    store = getFromFront(test);
    printf("\nGetFromFront NULL List Expected: NULL |  Actual: ");
    if (store == NULL) {
        printf("NULL\n");
    }
    store = getFromBack(test);
    printf("\nGetFromBack NULL List Expected: NULL |  Actual: ");
    if (store == NULL) {
        printf("NULL\n");
    }

    printf("\nDeleteList Null List Expected: |  Actual: ");
    deleteList(test);
    printForward(test);
    printf("\n");

    *d1 = 12983820;
    *d2 = 39483984;
    *d3 = 33948394;
    *d4 = 11203929;
    insertSorted(test, (void*)d1);
    insertSorted(test, (void*)d2);
    insertSorted(test, (void*)d3);
    insertSorted(test, (void*)d4);
    printf("\nInsertSorted Large Values Expected: 11203929 12983820 33948394 39483984 |  Actual: ");
    printForward(test);
    printf("\n\n");
    deleteList(test);

    free(d1);
    free(d2);
    free(d3);
    free(d4);
    free(test);
    
    return 0;
}
