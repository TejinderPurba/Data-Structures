/**
 * @file heap.c
 * @author Tejinder Purba | 0968799 | tpurba@mail.uoguelph.ca
 * @date July 19th 2017
 * @brief File containing the function definitions and implementations of an array heap
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "extraFunctions.h"
#include "heap.h"

Heap *createHeap(size_t initialSize, HEAP_TYPE htype, void (*destroyDataFP)(void *data),void (*printNodeFP)(void *toBePrinted),int (*compareFP)(const void *first, const void *second))
{
    Heap *newHeap;
    int i = 0;

    if (htype != MIN_HEAP && htype != MAX_HEAP) {
        return NULL;
    }
    if (destroyDataFP == NULL) {
        return NULL;
    }
    if (printNodeFP == NULL) {
        return NULL;
    }
    if (compareFP == NULL) {
        return NULL;
    }
    newHeap = malloc(sizeof(Heap));
    if (initialSize > 0) {
        newHeap->heap = malloc(sizeof(Node) * initialSize);
    }
    else {
        free(newHeap);
        return NULL;
    }
    newHeap->type = htype;
    newHeap->size = 0;
    newHeap->initialSize = initialSize;
    newHeap->destroyData = destroyDataFP;
    newHeap->printNode = printNodeFP;
    newHeap->compare = compareFP;

    for (i = 0; i < initialSize; ++i) {
        newHeap->heap[i] = NULL;
    }
    return newHeap;
}

Node *createHeapNode(void *data)
{
    if (data != NULL) {
        Node *newNode = malloc(sizeof(Node));
        newNode->data = data;
        return newNode;
    }
    else {
        return NULL;
    }
}

void insertHeapNode(Heap *heap, void *data)
{
    if (heap != NULL) {
        if (heap->size == heap->initialSize) {
            heap->initialSize = heap->initialSize + 10;
            heap->heap = realloc(heap->heap, sizeof(Node) * heap->initialSize);
        }
        Node *newNode = createHeapNode(data);
        if (newNode == NULL) {
            return;
        }
        heap->heap[heap->size] = newNode;
        ++heap->size;
        heapifyUp(heap, newNode);
    }
    return;
}

void deleteMinOrMax(Heap *heap)
{
    if (heap != NULL) {
        void (*deleteFunc)(void *data);
        deleteFunc = heap->destroyData;
        Node *parent;
        Node *child;
        parent = heap->heap[0];
        if (parent == NULL) {
            return;
        }
        child = heap->heap[heap->size-1];
        heap->heap[0] = child;
        deleteFunc(parent->data);
        free(parent);
        heap->heap[heap->size-1] = NULL;
        --heap->size;
        heapifyDown(heap, heap->heap[0]);
    }
    return;
}

void *getMinOrMax(Heap *heap)
{
    if (heap != NULL) {
        if (heap->heap[0] != NULL) {
            return (void*)heap->heap[0]->data;
        }
        else {
            return NULL;
        }
    }
    else {
        return NULL;
    }
}

void changeHeapType(Heap *heap)
{
    if (heap != NULL) {
        int i = 0;
        if (heap->type == MIN_HEAP) {
            heap->type = MAX_HEAP;
        }
        else if (heap->type == MAX_HEAP) {
            heap->type = MIN_HEAP;
        }
        for (i = 0; i < heap->size; ++i) {
            heapifyUp(heap, heap->heap[i]);
        }
    }
    return;
}

void deleteHeap(Heap *heap)
{
    if (heap != NULL) {
        int i = 0;
        int size = heap->size;

        for (i = 0; i < size; ++i) {
            deleteMinOrMax(heap);
        }

        free(heap->heap);
        free(heap);
    }
    return;
}
