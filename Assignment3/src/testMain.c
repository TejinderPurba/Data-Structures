/**
 * @file testMain.c
 * @author Tejinder Purba | 0968799 | tpurba@mail.uoguelph.ca
 * @date July 19th 2017
 * @brief File containing a main for testing of priority queue functions
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "extraFunctions.h"
#include "heap.h"
#include "priorityQueue.h"

void destroyDataFP(void *data) {

    free((int*)data);
    return;
}

void printNodeFP(void *toBePrinted) {
    if (toBePrinted != NULL) {
        Node *temp = toBePrinted;
        printf("\n%d \n", *(int*)temp->data);
    }
    return;
}

int compareFP(const void *first, const void *second) {
    return *(int*)first - *(int*)second;
}


int main() {

    int *d1 = malloc(sizeof(float));
    int grade = 0;
    Node *temp;

    /*
     *Test 1 Goal: To test whether a priority queue is created and correctly allocated
     */
    printf("\nTest 1: Create Function\n");
    Queue *test = create(0, MIN_HEAP, destroyDataFP, printNodeFP, compareFP);
    if (test == NULL) {
        printf("        SUCCESS: Priority Queue of size 0 not created\n");
        ++grade;
    }
    else {
        printf("        FAIL: Queue created\n");
    }

    test = create(15, MIN_HEAP, destroyDataFP, printNodeFP, compareFP);

    if (test != NULL) {
        printf("        SUCCESS: Priority Queue of size 15 created\n");
        ++grade;
    }
    else {
        printf("        FAIL: Queue not created\n");
    }

    destroy(test);

    test = create(10, -1, destroyDataFP, printNodeFP, compareFP);
    if (test == NULL) {
        printf("        SUCCESS: Priority Queue with heap type -1 not created\n");
        ++grade;
    }
    else {
        printf("        FAIL: Queue created\n");
    }

    /*
     *Test 2 Goal: To test whether queue heap nodes are created and allocated correctly
     */
    printf("\nTest 2: Insert Function\n");
    *d1 = 20;
    test = create(0, MIN_HEAP, destroyDataFP, printNodeFP, compareFP);
    insert(test, (void*)d1);
    if (test == NULL) {
        printf("        SUCCESS: Data not inserted into NULL Priority Queue\n");
        ++grade;
    }
    else {
        printf("        FAIL: Data inserted\n");
    }

    test = create(5, MIN_HEAP, destroyDataFP, printNodeFP, compareFP);
    insert(test, (void*)d1);
    temp = test->theHeap->heap[0];
    if (temp != NULL) {
        printf("        SUCCESS: Data inserted into Priority Queue\n");
        ++grade;
    }
    else {
        printf("        FAIL: Data not inserted\n");
    }

    /*
     *Test 3 Goal: To test whether root nodes are removed correctly
     */
    printf("\nTest 3: RemoveMax Function\n");
    removeMax(test);
    temp = test->theHeap->heap[0];

    if (temp == NULL) {
        printf("        SUCCESS: Priority Queue value '12' deleted\n");
        ++grade;
    }
    else {
        printf("        FAIL: Priority Queue value not deleted\n");
    }

    removeMax(test);
    temp = test->theHeap->heap[0];

    if (temp == NULL) {
        printf("        SUCCESS: Empty Priority Queue handled correctly\n");
        ++grade;
    }
    else {
        printf("        FAIL: Empty Priority Queue deleted\n");
    }

    free(d1);
    destroy(test);

    printf("\nFINAL RESULTS: %d/7\n\n", grade);

    return 0;
}
