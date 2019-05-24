/**
 * @file extraFunctions.h
 * @author Tejinder Purba | 0968799 | tpurba@mail.uoguelph.ca
 * @date July 19th 2017
 * @brief File containing the function definitions of an array heap
 **/

#ifndef _HEAPTYPES_
#define _HEAPTYPES_
#define MIN_HEAP 0 ///< min heap definer
#define MAX_HEAP 1 ///< max heap definer
#define HEAP_TYPE unsigned char ///< type for heap

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

#include "priorityQueue.h"


/**Function to swap elements until heap property is satisfied starting at root node.
 *@param heap Pointer to a heap to be heapified.
 *@param newNode point to node to start heapifying.
 **/
void heapifyDown (Heap * heap, Node * newNode);

/**Function to swap elements until heap property is satisfied starting at last node.
 *@param heap Pointer to a heap to be heapified.
 *@param newNode point to node to start heapifying.
 **/
void heapifyUp (Heap * heap, Node * newNode);

/**Parses data from a file into queue.
*@pre Queue type must exist and have data allocated to it. File must exist.
*@param temp Queue pointer to the priority queue.
*@param store Queue pointer to the storage priority queue.
*@param fp file pointer pointing to file where data is stored.
**/
void parseData (Queue * temp, Queue * store, FILE * fp);

/**Deletes a specific node from the heap.
*@param temp Queue pointer to the priority queue.
*@param client char pointer for the name of client to delete.
**/
int removePatient (Queue * temp, char client[100]);

/**Displays the overview of the simulatiojn.
*@param temp Queue pointer to the priority queue.
*@param store Queue pointer to the storage priority queue.
*@param currPatient integer to current patient being processed.
*@param totalPatients integer to total amount of patients in simulation.
*@param rows integer for total number of rows in terminal.
*@param cols integer for total number of columns in terminal.
*@param counter integer for clock of the simulation.
*@param patient integer for if there are patients in queue to be added.
*@param prevCounter integer to previous location of clock at last process time.
**/
int progress(Queue * temp, Queue * store, int currPatient, int totalPatients, int rows, int cols, int counter, int patient, int prevCounter);

/**Adds patient to the priority queue.
*@pre Queue type must exist and have data allocated to it. File must exist.
*@param temp Queue pointer to the priority queue
*@param clientName string for the patient name.
*@param sympCode string for the symptom code of the patient.
*@param priority float value for the priority rating of the patient.
*@param waitTime integer value for time spent waiting for next patient.
**/
void addPatient (Queue *temp, char clientName[100], char sympCode[100], float priority, int waitTime);

/**Writes specific patient data to report file.
*@param temp Queue pointer to the priority queue.
*@param store Queue pointer to the storage priority queue.
*@param size integer value for total amount of patients in queue.
*@param counter integer value for the clock amount in the simulation.
**/
void writeToFile (Queue *temp, Queue *store, int size, float counter);


#endif
