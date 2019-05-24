/**
 * @file priorityQueueBase.c
 * @author Tejinder Purba | 0968799 | tpurba@mail.uoguelph.ca
 * @date July 19th 2017
 * @brief File containing the base main for the simulation of a priority queue minor emergency clinic
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "extraFunctions.h"
#include "heap.h"
#include "priorityQueue.h"

void destroyDataFP(void *data) {
    PQNode *temp = data;

    free(temp->clientNum);
    free(temp->sympCode);
    free(temp->priorityNum);
    free(temp->procTime);
    free(temp->waitTime);
    free(temp->finishTime);
    free(temp);
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

    const PQNode *temp = first;
    const PQNode *temp2 = second;

    return *(float*)temp->priorityNum - *(float*)temp2->priorityNum;
}

int main(int argc, char* argv[]) {

    Queue *patients = create(100, MIN_HEAP, destroyDataFP, printNodeFP, compareFP);
    Queue *storage = create(100, MIN_HEAP, destroyDataFP, printNodeFP, compareFP);
    FILE *fp;
    int patientSize;
    int i = 0;

    if (argc > 1) {
        char *fileName = argv[1];
        fp = fopen(fileName,"r");
    }
    else {
        fp = NULL;
    }

    if (fp == NULL) {
        printf("\nError, file cannot be opened. Exiting...\n\n");
        destroy(patients);
        destroy(storage);
        return 0;
    }

    parseData(patients, storage, fp);
    patientSize = patients->theHeap->size;
    fclose(fp);

    printf("\nSimulation ready. %d/%d patients loaded.\n\n", patients->theHeap->size, patients->theHeap->size);

    fp = fopen("report.txt", "w+");
    if (fp == NULL) {
        printf("\nError, file cannot be opened. Exiting...\n\n");
        destroy(patients);
        destroy(storage);
        return 0;
    }
    printf("Order of patients (First To Last):\n\n");
    fprintf(fp, "Order of patients (First To Last):\n\n");
    for (i = 0; i < patientSize; ++i) {
        starvation(patients);
        PQNode *temp = patients->theHeap->heap[0]->data;
        printf("%s %.1f %s\n", temp->clientNum, *temp->priorityNum, temp->sympCode);
        fprintf(fp, "%s %.1f %s\n", temp->clientNum, *temp->priorityNum, temp->sympCode);
        removeMax(patients);
    }

    fclose(fp);

    printf("\nCompleted.\n\n");

    destroy(patients);
    destroy(storage);
    return 0;
}
