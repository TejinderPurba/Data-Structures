/**
 * @file queueTesting.c
 * @author Tejinder Purba
 * @date June 5th 2017
 * @brief File containing a main for testing of queue functions
 **/

#include <stdio.h>
#include <stdlib.h>
#include "LinkedListAPI.h"
#include "QueueADT.h"
#include "Functions.h"

int main () {

    Queue *test = create(printFunction, deleteFunction, compareFunction);
    Data *data;
    Data *store;
    Data *temp;
    float procTime;
    
    data = malloc(sizeof(Data));
    data->direction = malloc(sizeof(char));
    data->path = malloc(sizeof(char));
    data->time = malloc(sizeof(float));
    data->proc = malloc(sizeof(float));
    data->front = malloc(sizeof(float));
    data->finish = malloc(sizeof(float));
    data->wait = malloc(sizeof(float));
    store = malloc(sizeof(Data));
    store->direction = malloc(sizeof(char));
    store->path = malloc(sizeof(char));
    store->time = malloc(sizeof(float));
    store->proc = malloc(sizeof(float));
    store->front = malloc(sizeof(float));
    store->finish = malloc(sizeof(float));
    store->wait = malloc(sizeof(float));

    *data->direction = 'N';
    *data->path = 'R';
    *data->time = 9;

    enqueue(test, (void*)data);
    data = test->theList->head->data;
    printf("\n\nCreate Queue/Enqueue Expected: N R 9.00  |  Actual: ");
    printf("%c %c %.2f",*data->direction, *data->path, *data->time);
    printf("\n");

    dequeue(test);
    *data->direction = ' ';
    *data->path = ' ';
    *data->time = 0;

    enqueue(test, (void*)data);
    data = test->theList->head->data;
    printf("\nCreate Queue Blank Data Expected:       0.00  |  Actual: ");
    printf("%c %c %.2f",*data->direction, *data->path, *data->time);
    printf("\n");

    *store->direction = 'E';
    *store->path = 'L';
    *store->time = 12;

    enqueue(test, (void*)store);
    data = test->theList->head->data;
    store = test->theList->head->next->data;
    printf("\nEnqueue Expected:     0.00  E L 12.00");
    printf("  |  Actual: ");
    printf("%c %c %.2f  %c %c %.2f ",*data->direction, *data->path, *data->time, *store->direction, *store->path, *store->time);
    printf("\n");

    dequeue(test);
    printf("\nDequeue Expected:     0.00  |  Actual: ");
    printf("%c %c %.2f",*data->direction, *data->path, *data->time);
    printf("\n");

    printf("\nEnqueue/Destroy Expected:  |   Actual: ");
    enqueue(test, (void*)data);
    destroy(test);
    test = create(printFunction, deleteFunction, compareFunction);
    printForward(test->theList);
    printf("\n");

    destroy(test);
    procTime = 5.5;
    test = create(printFunction, deleteFunction, compareFunction);
    northSort(data, store, procTime, test);
    printf("\n(North) Front Time Assignment Expected: 6.50  |  Actual: %.2f\n", *store->front);

    *data->time = 8.5;
    southSort(data, store, procTime, test);
    printf("\n(South) Alternative Front Time Assignment Expected: 8.50  |  Actual: %.2f\n", *store->front);

    *data->time = 2.5;
    eastSort(data, store, procTime, test);
    printf("\n(East) Alternative Front Time Assignment Expected: 6.50  |  Actual: %.2f\n", *store->front);

    *data->time = 5.5;
    westSort(data, store, procTime, test);
    printf("\n(West) Alternative Front Time Assignment Expected: 6.50  |  Actual: %.2f\n", *store->front);

    destroy(test);
    test = create(printFunction, deleteFunction, compareFunction);
    *store->time = 1348456565;
    enqueue(test, (void*)store);
    printf("\nEnqueue large data Expected: 1)  E L 1348456576.00  |  Actual: ");
    printForward(test->theList);

    printf("\nDequeue large data Expected:  |  Actual:  ");
    dequeue(test);
    printForward(test->theList);
    printf("\n\n");

    destroy(test);
    test = create(printFunction, deleteFunction, compareFunction);
    *store->direction = 'N';
    *store->path = 'L';
    *store->front = 3;
    *data->direction = 'S';
    *data->path = 'R';
    *data->front = 3;
    enqueue(test, (void*)store);
    enqueue(test, (void*)data);

    temp = rightOfWay(test, 2);

    printf("Right of Way Expected: S  |  Actual: %c\n", *temp->direction);

    *store->direction = 'N';
    *store->path = 'L';
    *data->direction = 'S';
    *data->path = 'L';
    temp = rightOfWay(test, 2);

    printf("\nRight of Way Expected: N  |  Actual: %c\n", *temp->direction);

    *store->direction = 'E';
    *store->path = 'L';
    *data->direction = 'W';
    *data->path = 'R';
    temp = rightOfWay(test, 2);

    printf("\nRight of Way Expected: W  |  Actual: %c\n", *temp->direction);

    *store->direction = 'E';
    *store->path = 'F';
    *data->direction = 'S';
    *data->path = 'L';
    temp = rightOfWay(test, 2);

    printf("\nRight of Way Expected: E  |  Actual: %c\n\n\n", *temp->direction);

    destroy(test);
    free(data->direction);
    free(data->path);
    free(data->time);
    free(data->proc);
    free(data->wait);
    free(data->finish);
    free(data->front);
    free(data);

    free(store->direction);
    free(store->path);
    free(store->time);
    free(store->proc);
    free(store->wait);
    free(store->finish);
    free(store->front);
    free(store);

    return 0;
}

