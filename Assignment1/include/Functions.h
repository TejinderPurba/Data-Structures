/**
 * @file Functions.h
 * @author Tejinder Purba
 * @date June 5th 2017
 * @brief File containing the custom functions for handling data types
 */

#ifndef _FUNCTIONS_
#define _FUNCTIONS_

#include <stdio.h>
#include <stdlib.h>
#include "LinkedListAPI.h"

/**Function to print the data in the node passed.
*@post The data witin the passed node will be printed.
*@param one variable to hold the node pointer that is passed.
**/
void printFunction(void *one);

/**Function to swap heads and delete nodes that are passed.
*@post The next node will be chosen as the head and current one
*will be free'd.
*@param one variable to hold the node pointer that is passed.
**/
void deleteFunction(void *one);

/**Function to compare the data from two void pointers.
*@return The difference between void pointer one and void
*pointer two.
*@param one variable to hold the node pointer that is passed.
*@param two variable to hold the second node pointer that is passed.
**/
float compareFunction(const void *one, const void *two);

/**Determines the value for the time the car travelling north reaches the front of the queue. 
*@pre 'Queue' type must exist and be used in order to keep track of the linked list.
*@param first pointer to data struct containing current car info.
*@param data pointer to data struct to store newly calculated car values.
*@param procTimeN float value which keeps track of process time of previous car.
*@param test queue pointer that points to the head of the queue in which to store data in.
**/
void northSort(Data *first, Data *data, float procTimeN, Queue *test);

/**Determines the value for the time the car travelling south reaches the front of the queue. 
*@pre 'Queue' type must exist and be used in order to keep track of the linked list.
*@param first pointer to data struct containing current car info.
*@param data pointer to data struct to store newly calculated car values.
*@param procTimeS float value which keeps track of process time of previous car.
*@param test queue pointer that points to the head of the queue in which to store data in.
**/
void southSort(Data *first, Data *data, float procTimeS, Queue *test);

/**Determines the value for the time the car travelling east reaches the front of the queue. 
*@pre 'Queue' type must exist and be used in order to keep track of the linked list.
*@param first pointer to data struct containing current car info.
*@param data pointer to data struct to store newly calculated car values.
*@param procTimeE float value which keeps track of process time of previous car.
*@param test queue pointer that points to the head of the queue in which to store data in.
**/
void eastSort(Data *first, Data *data, float procTimeE, Queue *test);

/**Determines the value for the time the car travelling south reaches the front of the queue. 
*@pre 'Queue' type must exist and be used in order to keep track of the linked list.
*@param first pointer to data struct containing current car info.
*@param data pointer to data struct to store newly calculated car values.
*@param procTimeW float value which keeps track of process time of previous car.
*@param test queue pointer that points to the head of the queue in which to store data in.
**/
void westSort(Data *first, Data *data, float procTimeW, Queue *test);

/**Determines the value for the time the car travelling south reaches the front of the queue. 
*@return pointer to the data struct.
*@pre 'Queue' type must exist and be used in order to keep track of the linked list.
*@param queue pointer to queue containing current heads of each queue.
*@param amount of cars waiting at the front of the intersection.
**/
Data *rightOfWay(Queue *queue, int amount);




#endif

