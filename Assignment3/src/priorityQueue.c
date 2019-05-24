/**
 * @file priorityQueue.c
 * @author Tejinder Purba | 0968799 | tpurba@mail.uoguelph.ca
 * @date July 19th 2017
 * @brief File containing the function definitions and implementations of a priority queue
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "extraFunctions.h"
#include "heap.h"
#include "priorityQueue.h"

Queue *create(size_t initialSize, HEAP_TYPE htype, void (*destroyDataFP)(void *data),void (*printNodeFP)(void *toBePrinted),int (*compareFP)(const void *first, const void *second))
{
    Queue *temp;
    temp = malloc(sizeof(Queue));

    temp->theHeap = createHeap(initialSize, htype, destroyDataFP, printNodeFP, compareFP);

    if (temp->theHeap == NULL) {
        free(temp->theHeap);
        free(temp);
        temp = NULL;
    }
    return temp;
}

void destroy(Queue *temp)
{
    deleteHeap(temp->theHeap);
    free(temp);
    return;
}

int isEmpty(Queue *temp)
{
    if (temp->theHeap == NULL) {
        return 0;
    }
    else if (temp->theHeap->size == 0) {
        return 0;
    }
    else {
        return 1;
    }
}

void insert(Queue *temp, void *toBeAdded)
{
    if (temp != NULL) {
        if (toBeAdded != NULL) {
            insertHeapNode(temp->theHeap, (void*)toBeAdded);
        }
        else {
            return;
        }
    }
    return;
}

void removeMax(Queue *temp)
{
    if (temp != NULL) {
        deleteMinOrMax(temp->theHeap);
    }
}

void starvation(Queue *temp)
{
    int i = 0;

    for (i = 0; i < temp->theHeap->size; ++i) {
        PQNode *tmp = temp->theHeap->heap[i]->data;
        if (*tmp->waitTime > 600 && *tmp->waitTime < 900) {
            *tmp->priorityNum -= 1;
            if (*tmp->priorityNum < 1) {
                *tmp->priorityNum = 1;
            }
            heapifyUp(temp->theHeap, temp->theHeap->heap[i]);
        }
        else if (*tmp->waitTime >= 900) {
            *tmp->priorityNum = 1;
            heapifyUp(temp->theHeap, temp->theHeap->heap[i]);
        }
    }
}
