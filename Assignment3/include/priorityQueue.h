/**
 * @file priorityQueue.h
 * @author Tejinder Purba | 0968799 | tpurba@mail.uoguelph.ca
 * @date July 19th 2017
 * @brief File containing the function definitions of a priority queue
 **/


#ifndef _QUEUE_
#define _QUEUE_
#define MIN_HEAP 0 ///< min heap definer
#define MAX_HEAP 1 ///< max heap definer
#define HEAP_TYPE unsigned char ///< type for heap



/**
*Queue struct for a priority queue. Contains a heap as a member, which will be used to encapsulate and create the queue.
**/
typedef struct Queue {
    Heap *theHeap; ///<  pointer to heap that is to store all heap properties
} Queue;

/**
*Data struct containing the different values which will be stored in each node in the queue.
**/
typedef struct PQNode {
    char *clientNum; ///< name of client to be stored
    char *sympCode; ///< symptom code of client to be stored
    float *priorityNum; ///< priority number of client to be stored
    float *procTime; ///< time for patient to be processed
    float *waitTime; ///< time patient has been waiting in queue
    float *finishTime; ///< time patient is discharged
} PQNode;

#include "extraFunctions.h"

/**Function to initialize a priority queue and point to the heap. Allocates memory to the queue.
*@return pointer to the queue.
*@param initialSize original size of the queue to be created.
*@param htype type defining either a min or max heap .
*@param destroyDataFP function pointer to delete a single piece of data from the heap.
*@param printNodeFP function pointer to print data from a queue.
*@param compareFP function pointer to compare two nodes of the heap in order to test for equality or order.
**/
Queue *create(size_t initialSize, HEAP_TYPE htype, void (*destroyDataFP)(void *data),void (*printNodeFP)(void *toBePrinted),int (*compareFP)(const void *first, const void *second));

/**Destroys the queue and frees subsequent heap nodes and variables.
*@pre 'Heap' type must exist and be used in order to keep track of the heap.
*@param temp queue pointer to the head of the queue.
**/
void destroy(Queue *temp);

/**Checks if queue is empty.
*@pre 'Heap' type must exist and be used in order to keep track of the heap.
*@param temp queue pointer to the head of the queue.
**/
int isEmpty(Queue *temp);

/**Inserts a Node to the heap inside the queue.
*@pre 'Heap' type must exist and be used in order to keep track of the heap.
*@param temp queue pointer to the head of the queue.
*@param toBeAdded a pointer to data that is to be added to the queue.
**/
void insert(Queue *temp, void *toBeAdded);

/**Removes the root node from the from of the heap inside the queue.
*@pre 'Heap' type must exist and be used in order to keep track of the heap.
*@param temp pointer to the head of the queue.
**/
void removeMax(Queue *temp);

/**Checks for starvation property of low priority patients.
*@param temp Queue pointer to the priority queue.
**/
void starvation (Queue *temp);

#endif
