/**
 * @file testMain.c
 * @author Tejinder Purba | 0968799 | tpurba@mail.uoguelph.ca
 * @date July 10th 2017
 * @brief File containing a main for testing of binary heap functions
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "extraFunctions.h"
#include "heap.h"

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

    int *d1 = malloc(sizeof(int));
    int *d2 = malloc(sizeof(int));
    int *d3 = malloc(sizeof(int));
    int *d4 = malloc(sizeof(int));
    int *d7;
    int grade = 0;
    Node *temp;
    void *store;

    /*
     *Test 1 Goal: To test whether a heap is created and correctly allocated
     */
    printf("\nTest 1: CreateHeap Function\n");
    Heap *minHeap = createHeap(0, MIN_HEAP, destroyDataFP, printNodeFP, compareFP);
    if (minHeap == NULL) {
        printf("        SUCCESS: Min Heap Table of size 0 not created\n");
        ++grade;
    }
    else {
        printf("        FAIL: Min Heap created\n");
    }
    Heap *maxHeap = createHeap(0, MAX_HEAP, destroyDataFP, printNodeFP, compareFP);
    if (maxHeap == NULL) {
        printf("        SUCCESS: Max Heap Table of size 0 not created\n");
        ++grade;
    }
    else {
        printf("        FAIL: Max Heap created\n");
    }

    minHeap = createHeap(15, MIN_HEAP, destroyDataFP, printNodeFP, compareFP);

    if (minHeap != NULL && minHeap->heap[14] == NULL) {
        printf("        SUCCESS: Min Heap of size 15 created\n");
        ++grade;
    }
    else {
        printf("        FAIL: Heap not created\n");
    }

    maxHeap = createHeap(15, MAX_HEAP, destroyDataFP, printNodeFP, compareFP);

    if (maxHeap != NULL && maxHeap->heap[14] == NULL) {
        printf("        SUCCESS: Max Heap of size 15 created\n");
        ++grade;
    }
    else {
        printf("        FAIL: Heap not created\n");
    }

    deleteHeap(minHeap);
    deleteHeap(maxHeap);

    minHeap = createHeap(400, MIN_HEAP, destroyDataFP, printNodeFP, compareFP);

    if (minHeap != NULL && minHeap->heap[399] == NULL) {
        printf("        SUCCESS: Min Heap of size 400 created\n");
        ++grade;
    }
    else {
        printf("        FAIL: Heap not created\n");
    }

    maxHeap = createHeap(400, MAX_HEAP, destroyDataFP, printNodeFP, compareFP);

    if (maxHeap != NULL && maxHeap->heap[399] == NULL) {
        printf("        SUCCESS: Max Heap of size 400 created\n");
        ++grade;
    }
    else {
        printf("        FAIL: Heap not created\n");
    }

    deleteHeap(maxHeap);
    deleteHeap(minHeap);

    minHeap = createHeap(10, -1, destroyDataFP, printNodeFP, compareFP);
    if (minHeap == NULL) {
        printf("        SUCCESS: Heap Table with heap type -1 not created\n");
        ++grade;
    }
    else {
        printf("        FAIL: Heap created\n");
    }

    maxHeap = createHeap(10, MAX_HEAP, NULL, NULL, NULL);
    if (maxHeap == NULL) {
        printf("        SUCCESS: Heap Table with NULL function parameters not created\n");
        ++grade;
    }
    else {
        printf("        FAIL: Heap created\n");
    }

    printf("        ~~TESTS PASSED: %d/8~~\n", grade);


    /*
     *Test 2 Goal: To test whether heap nodes are created and allocated correctly
     */
    printf("\nTest 2: CreateHeapNode/InsertHeapNode Function\n");
    *d1 = 20;
    minHeap = createHeap(0, MIN_HEAP, destroyDataFP, printNodeFP, compareFP);
    maxHeap = createHeap(0, MAX_HEAP, destroyDataFP, printNodeFP, compareFP);
    insertHeapNode(minHeap, (void*)d1);
    if (minHeap == NULL) {
        printf("        SUCCESS: Data not inserted into NULL Min Heap\n");
        ++grade;
    }
    else {
        printf("        FAIL: Data inserted\n");
    }
    insertHeapNode(maxHeap, (void*)d1);
    if (maxHeap == NULL) {
        printf("        SUCCESS: Data not inserted into NULL Max Heap\n");
        ++grade;
    }
    else {
        printf("        FAIL: Data inserted\n");
    }

    minHeap = createHeap(1, MIN_HEAP, destroyDataFP, printNodeFP, compareFP);
    maxHeap = createHeap(1, MAX_HEAP, destroyDataFP, printNodeFP, compareFP);
    d7 = NULL;
    insertHeapNode(minHeap, (void*)d7);
    if (minHeap->heap[0] == NULL) {
        printf("        SUCCESS: Min Node with NULL data not created\n");
        ++grade;
    }
    else {
        printf("        FAIL: Node created\n");
    }
    insertHeapNode(maxHeap, (void*)d7);
    if (maxHeap->heap[0] == NULL) {
        printf("        SUCCESS: Max Node with NULL data not created\n");
        ++grade;
    }
    else {
        printf("        FAIL: Node created\n");
    }

    deleteHeap(minHeap);
    deleteHeap(maxHeap);

    minHeap = createHeap(1, MIN_HEAP, destroyDataFP, printNodeFP, compareFP);
    maxHeap = createHeap(1, MAX_HEAP, destroyDataFP, printNodeFP, compareFP);

    *d1 = 23;
    *d2 = 23;
    *d3 = 12;
    *d4 = 12;
    insertHeapNode(minHeap, (void*)d1);
    if (minHeap->heap[0] != NULL) {
        printf("        SUCCESS: Min Node with data '23' created\n");
        ++grade;
    }
    else {
        printf("        FAIL: Node not created\n");
    }
    insertHeapNode(maxHeap, (void*)d2);
    if (maxHeap->heap[0] != NULL) {
        printf("        SUCCESS: Max Node with data '23' created\n");
        ++grade;
    }
    else {
        printf("        FAIL: Node not created\n");
    }

    insertHeapNode(minHeap, (void*)d3);
    if (minHeap->heap[1] != NULL) {
        printf("        SUCCESS: Min Node with data '12' created in Full Heap\n");
        ++grade;
    }
    else {
        printf("        FAIL: Node not created\n");
    }
    insertHeapNode(maxHeap, (void*)d4);
    if (maxHeap->heap[1] != NULL) {
        printf("        SUCCESS: Max Node with data '12' created in Full Heap\n");
        ++grade;
    }
    else {
        printf("        FAIL: Node not created\n");
    }


    printf("        ~~TESTS PASSED: %d/8~~\n", grade-8);


    /*
     *Test 3 Goal: To test whether root nodes are removed correctly
     */
    printf("\nTest 3: DeleteMinOrMax Function\n");
    deleteMinOrMax(minHeap);
    temp = minHeap->heap[0];

    if (*(int*)temp->data == 23) {
        printf("        SUCCESS: Min Heap min value '12' deleted\n");
        ++grade;
    }
    else {
        printf("        FAIL: Min Heap min value not deleted\n");
    }

    deleteMinOrMax(maxHeap);
    temp = maxHeap->heap[0];

    if (*(int*)temp->data == 12) {
        printf("        SUCCESS: Max Heap max value '23' deleted\n");
        ++grade;
    }
    else {
        printf("        FAIL: Max Heap max value not deleted\n");
    }

    deleteMinOrMax(minHeap);
    temp = minHeap->heap[0];

    if (temp == NULL) {
        printf("        SUCCESS: Min Heap min value '23' deleted\n");
        ++grade;
    }
    else {
        printf("        FAIL: Min Heap min value not deleted\n");
    }

    deleteMinOrMax(maxHeap);
    temp = maxHeap->heap[0];

    if (temp == NULL) {
        printf("        SUCCESS: Max Heap max value '12' deleted\n");
        ++grade;
    }
    else {
        printf("        FAIL: Max Heap max value not deleted\n");
    }

    deleteMinOrMax(minHeap);
    temp = minHeap->heap[0];

    if (temp == NULL) {
        printf("        SUCCESS: Empty Min Heap handled correctly\n");
        ++grade;
    }
    else {
        printf("        FAIL: Empty Min Heap deleted\n");
    }

    deleteMinOrMax(maxHeap);
    temp = maxHeap->heap[0];

    if (temp == NULL) {
        printf("        SUCCESS: Empty Max Heap handled correctly\n");
        ++grade;
    }
    else {
        printf("        FAIL: Empty Max Heap deleted\n");
    }

    deleteHeap(minHeap);
    deleteHeap(maxHeap);

    minHeap = NULL;
    maxHeap = NULL;
    temp = NULL;

    deleteMinOrMax(minHeap);

    if (minHeap == NULL) {
        printf("        SUCCESS: NULL Min Heap handled correctly\n");
        ++grade;
    }
    else {
        printf("        FAIL: NULL Min Heap deleted\n");
    }

    deleteMinOrMax(maxHeap);

    if (maxHeap == NULL) {
        printf("        SUCCESS: NULL Max Heap handled correctly\n");
        ++grade;
    }
    else {
        printf("        FAIL: NULL Max Heap deleted\n");
    }

    printf("        ~~TESTS PASSED: %d/8~~\n", grade-16);


    /*
     *Test 4 Goal: To test whether root nodes are returned properly
     */
    printf("\nTest 4: GetMinOrMax Function\n");

    d1 = malloc(sizeof(int));
    d2 = malloc(sizeof(int));
    d3 = malloc(sizeof(int));
    d4 = malloc(sizeof(int));

    *d1 = 34;
    *d2 = 34;
    *d3 = 20;
    *d4 = 20;

    minHeap = createHeap(2, MIN_HEAP, destroyDataFP, printNodeFP, compareFP);
    maxHeap = createHeap(2, MAX_HEAP, destroyDataFP, printNodeFP, compareFP);

    insertHeapNode(maxHeap, (void*)d1);
    insertHeapNode(minHeap, (void*)d2);
    insertHeapNode(maxHeap, (void*)d3);
    insertHeapNode(minHeap, (void*)d4);

    if (maxHeap != NULL && minHeap != NULL) {
        printf("        SUCCESS: Inserted 20 and 34 into each heap\n");
        ++grade;
    }

    store = getMinOrMax(minHeap);

    if (*(int*)store == 20) {
        printf("        SUCCESS: '20' retrieved from Min Heap root node\n");
        ++grade;
    }
    else {
        printf("        FAIL: Incorrect data retrieved\n");
    }

    store = getMinOrMax(maxHeap);

    if (*(int*)store == 34) {
        printf("        SUCCESS: '34' retrieved from Max Heap root node\n");
        ++grade;
    }
    else {
        printf("        FAIL: Incorrect data retrieved\n");
    }

    deleteMinOrMax(minHeap);
    deleteMinOrMax(minHeap);
    deleteMinOrMax(maxHeap);
    deleteMinOrMax(maxHeap);

    store = getMinOrMax(minHeap);

    if (store == NULL) {
        printf("        SUCCESS: NULL retrieved from Empty Min Heap root node\n");
        ++grade;
    }
    else {
        printf("        FAIL: Incorrect data retrieved\n");
    }

    store = getMinOrMax(maxHeap);

    if (store == NULL) {
        printf("        SUCCESS: NULL retrieved from Empty Max Heap root node\n");
        ++grade;
    }
    else {
        printf("        FAIL: Incorrect data retrieved\n");
    }

    deleteHeap(minHeap);
    deleteHeap(maxHeap);

    minHeap = NULL;
    maxHeap = NULL;

    store = getMinOrMax(minHeap);

    if (store == NULL) {
        printf("        SUCCESS: NULL retrieved from NULL Min Heap root node\n");
        ++grade;
    }
    else {
        printf("        FAIL: Incorrect data retrieved\n");
    }

    store = getMinOrMax(maxHeap);

    if (store == NULL) {
        printf("        SUCCESS: NULL retrieved from NULL Max Heap root node\n");
        ++grade;
    }
    else {
        printf("        FAIL: Incorrect data retrieved\n");
    }

    printf("        ~~TESTS PASSED: %d/7~~\n", grade-24);

    /*
     *Test 5 Goal: To test whether heap type is changed properly
     */
    printf("\nTest 5: ChangeHeapType Function\n");

    d1 = malloc(sizeof(int));
    d2 = malloc(sizeof(int));
    d3 = malloc(sizeof(int));
    d4 = malloc(sizeof(int));

    *d1 = 16;
    *d2 = 16;
    *d3 = 23;
    *d4 = 23;

    minHeap = createHeap(2, MIN_HEAP, destroyDataFP, printNodeFP, compareFP);
    maxHeap = createHeap(2, MAX_HEAP, destroyDataFP, printNodeFP, compareFP);

    insertHeapNode(maxHeap, (void*)d1);
    insertHeapNode(minHeap, (void*)d2);
    insertHeapNode(maxHeap, (void*)d3);
    insertHeapNode(minHeap, (void*)d4);

    if (minHeap->heap[0] != NULL && maxHeap->heap[0] != NULL) {
        printf("        SUCCESS: Inserted 16 and 23 into each heap\n");
        ++grade;
    }

    changeHeapType(minHeap);
    store = getMinOrMax(minHeap);

    if (*(int*)store == 23) {
        printf("        SUCCESS: '23' retrieved from Type Changed Min Heap root node\n");
        ++grade;
    }
    else {
        printf("        FAIL: Incorrect data retrieved\n");
    }

    changeHeapType(maxHeap);
    store = getMinOrMax(maxHeap);

    if (*(int*)store == 16) {
        printf("        SUCCESS: '16' retrieved from Type Changed Max Heap root node\n");
        ++grade;
    }
    else {
        printf("        FAIL: Incorrect data retrieved\n");
    }

    changeHeapType(minHeap);
    changeHeapType(maxHeap);
    deleteMinOrMax(minHeap);
    deleteMinOrMax(minHeap);
    deleteMinOrMax(maxHeap);
    deleteMinOrMax(maxHeap);

    changeHeapType(minHeap);

    if (minHeap->type == MAX_HEAP) {
        printf("        SUCCESS: Empty Min Heap type changed to MAX_HEAP\n");
        ++grade;
    }
    else {
        printf("        FAIL: Type not changed\n");
    }

    changeHeapType(maxHeap);

    if (maxHeap->type == MIN_HEAP) {
        printf("        SUCCESS: Empty Max Heap type changed to MIN_HEAP\n");
        ++grade;
    }
    else {
        printf("        FAIL: Type not changed\n");
    }

    deleteHeap(minHeap);
    deleteHeap(maxHeap);

    minHeap = NULL;
    maxHeap = NULL;

    changeHeapType(minHeap);
    changeHeapType(minHeap);

    if (minHeap == NULL) {
        printf("        SUCCESS: NULL Min Heap type changed to MAX_HEAP\n");
        ++grade;
    }
    else {
        printf("        FAIL: Type not changed\n");
    }

    changeHeapType(maxHeap);
    changeHeapType(maxHeap);

    if (maxHeap == NULL) {
        printf("        SUCCESS: NULL Max Heap type changed to MIN_HEAP\n");
        ++grade;
    }
    else {
        printf("        FAIL: Type not changed\n");
    }


    printf("        ~~TESTS PASSED: %d/7~~\n", grade-31);

    /*
     *Test 6 Goal: To test whether heap is deleted properly
     */
    printf("\nTest 6: DeleteHeap Function\n");

    d1 = malloc(sizeof(int));
    d2 = malloc(sizeof(int));
    d3 = malloc(sizeof(int));
    d4 = malloc(sizeof(int));

    *d1 = 3;
    *d2 = 3;
    *d3 = 45;
    *d4 = 45;

    minHeap = createHeap(2, MIN_HEAP, destroyDataFP, printNodeFP, compareFP);
    maxHeap = createHeap(2, MAX_HEAP, destroyDataFP, printNodeFP, compareFP);

    insertHeapNode(maxHeap, (void*)d1);
    insertHeapNode(minHeap, (void*)d2);
    insertHeapNode(maxHeap, (void*)d3);
    insertHeapNode(minHeap, (void*)d4);

    if (maxHeap != NULL && minHeap != NULL) {
        printf("        SUCCESS: Inserted 3 and 45 into each heap\n");
        ++grade;
    }

    deleteHeap(minHeap);
    minHeap = NULL;

    if (minHeap == NULL) {
        printf("        SUCCESS: Min Heap deleted\n");
        ++grade;
    }
    else {
        printf("        FAIL: Min Heap not deleted\n");
    }

    deleteHeap(maxHeap);
    maxHeap = NULL;

    if (maxHeap == NULL) {
        printf("        SUCCESS: Max Heap deleted\n");
        ++grade;
    }
    else {
        printf("        FAIL: Max Heap not deleted\n");
    }

    minHeap = createHeap(2, MIN_HEAP, destroyDataFP, printNodeFP, compareFP);
    maxHeap = createHeap(2, MAX_HEAP, destroyDataFP, printNodeFP, compareFP);

    deleteHeap(minHeap);
    minHeap = NULL;

    if (minHeap == NULL) {
        printf("        SUCCESS: Empty Min Heap deleted\n");
        ++grade;
    }
    else {
        printf("        FAIL: Min Heap not deleted\n");
    }

    deleteHeap(maxHeap);
    maxHeap = NULL;

    if (maxHeap == NULL) {
        printf("        SUCCESS: Empty Max Heap deleted\n");
        ++grade;
    }
    else {
        printf("        FAIL: Max Heap not deleted\n");
    }

    deleteHeap(minHeap);
    minHeap = NULL;

    if (minHeap == NULL) {
        printf("        SUCCESS: Empty Min Heap deleted\n");
        ++grade;
    }
    else {
        printf("        FAIL: Min Heap not deleted\n");
    }

    deleteHeap(maxHeap);
    maxHeap = NULL;

    if (maxHeap == NULL) {
        printf("        SUCCESS: Empty Max Heap deleted\n");
        ++grade;
    }
    else {
        printf("        FAIL: Max Heap not deleted\n");
    }

    printf("        ~~TESTS PASSED: %d/7~~\n", grade-38);

    printf("\nFINAL RESULTS: %d/45\n\n", grade);

    return 0;
}
