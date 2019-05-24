/**
 * @file QueueADT.h
 * @author Tejinder Purba
 * @date June 5th 2017
 * @brief File containing the function definitions of a queue ADT
 */

#ifndef _QUEUE_API_
#define _QUEUE_API_

#include <stdio.h>
#include <stdlib.h>
#include "LinkedListAPI.h"

/**
*Queue struct for a queue. Contains a variable to point to the front of the queue, along with a doubly linked
*list as a member, which will be used to encapsulate and create the queue.
**/
typedef struct Queue{
    List * theList;
    Node * front;
}Queue;

/**
*Data struct containing the different values which will be stored in each node in the queue.
**/
typedef struct Data{
    char *direction;
    char *path;
    float *time;
    float *proc;
    float *front;
    float *finish;
    float *wait;
}Data;

/**Function to initialize a queue and point to the list and front variable. Allocates memory to the queue.
*@return pointer to the queue.
*@param printFunction function pointer to print data from a queue.
*@param deleteFunction function pointer to delete a single piece of data from the list.
*@param compareFunction function pointer to compare two nodes of the list in order to test for equality or order.
**/
Queue *create(void (*printFunction)(void *toBePrinted),void (*deleteFunction)(void *toBeDeleted), float (*compareFunction)(const void *first,const void *second));

/**Detroys the queue and frees subsequent linked lists and variables. 
*@pre 'List' type must exist and be used in order to keep track of the linked list.
*@param temp queue pointer to the head of the queue.
**/
void destroy(Queue *temp);

/**Inserts a Node to the back of a linked list inside the queue. 
*@pre 'List' type must exist and be used in order to keep track of the linked list.
*@param temp queue pointer to the head of the queue.
*@param toBeAdded a pointer to data that is to be added to the queue.
**/
void enqueue(Queue *temp, void *toBeAdded);

/**Removes a Node from the from of the linked list inside the queue. 
*@pre 'List' type must exist and be used in order to keep track of the linked list.
*@param queue pointer to the head of the queue.
**/
void dequeue(Queue *temp);


#endif
