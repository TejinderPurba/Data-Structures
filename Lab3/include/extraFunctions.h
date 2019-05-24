/**
 * @file extraFunctions.h
 * @author Tejinder Purba | 0968799 | tpurba@mail.uoguelph.ca
 * @date July 10th 2017
 * @brief File containing the function definitions of an array heap
 **/

#ifndef _HEAPTYPES_
#define _HEAPTYPES_
#ifndef _HEAP_API_
#define MIN_HEAP 0
#define MAX_HEAP 1
#define HEAP_TYPE unsigned char
#endif
#endif

/**
*Node of the binary tree heap.
**/
typedef struct Node
{
    void * data; ///<  pointer to generic data that is to be stored in the binary tree heap
} Node;

/**
*Heap struct for binary tree implementation of a Heap
**/
typedef struct Heap
{
    Node **heap; ///< contains all of the heap nodes
    int size; ///< current size of the heap
    int initialSize; ///< initial size of the heap
    HEAP_TYPE type; ///< flag for choosing between min and max heap
    void (*destroyData)(void *data); ///< function pointer to a function to delete a single piece of data from the heap
    void (*printNode)(void *toBePrinted); ///< function pointer to a function that prints out a data element of the heap
    int (*compare)(const void *first, const void *second); ///< function pointer to a comparison function for the purpose of inserting and deleting elements
} Heap;

#include "heap.h"

/**Function to swap elements until heap property is satisfied starting at root node.
 *@param heap Pointer to a heap to be heapified
 *@param newNode point to node to start heapifying
 **/
void heapifyDown (Heap * heap, Node * newNode);

/**Function to swap elements until heap property is satisfied starting at last node.
 *@param heap Pointer to a heap to be heapified
 *@param newNode point to node to start heapifying
 **/
void heapifyUp (Heap * heap, Node * newNode);

