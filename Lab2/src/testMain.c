/**
 * @file testMain.c
 * @author Tejinder Purba | 0968799 | tpurba@mail.uoguelph.ca
 * @date June 19th 2017
 * @brief File containing a main for testing of hash table functions
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HashTableAPI.h"

#define SIZE 50

typedef struct hashData
{
    int studNum;
    char *name;
    long phoneNum;
} dataTable;

int hashFunction (size_t tableSize, int key) {
    return (key + tableSize) % tableSize;
}

void destroyData (void *data) {
    free(((dataTable*)data)->name);
    free((dataTable*)data);
    return;
}

void printData (void *toBePrinted) {
    if (toBePrinted != NULL) {
        dataTable *temp = (dataTable*)toBePrinted;
        printf("%s  %d  %ld\n", temp->name, temp->studNum, temp->phoneNum);
    }
    return;
}

int main() {

    HTable *hash = createTable(SIZE, &hashFunction, &destroyData, &printData);

    dataTable *temp = NULL;
    dataTable *store = NULL;
    char *storage;

    temp = malloc(sizeof(dataTable));
    temp->studNum = 968799;
    temp->phoneNum = 9054541503;
    storage = "Tejinder Purba";
    temp->name = malloc(sizeof(char)*strlen(storage)+1);
    strcpy(temp->name, storage);
    insertData(hash, temp->studNum, (void*)temp);

    printf("\nFirst Insertion Test - Expected: Tejinder Purba  968799  9054541503 \n                      Actual:  ");
    store = (dataTable*)lookupData(hash, 968799);
    if(store != NULL)
    {
        hash->printData((void*)store);
    }

    temp = malloc(sizeof(dataTable));
    temp->studNum = 8585;
    temp->phoneNum = 905905905;
    storage = "Adam James";
    temp->name = malloc(sizeof(char)*strlen(storage)+1);
    strcpy(temp->name, storage);
    insertData(hash, temp->studNum, (void*)temp);

    printf("\nSecond Insertion Test - Expected: Adam James  8585  905905905 \n                        Actual:  ");
    store = (dataTable*)lookupData(hash, 8585);
    if (store != NULL)
    {
        hash->printData((void*)store);
    }

    temp = malloc(sizeof(dataTable));
    temp->studNum = 8585;
    temp->phoneNum = 4169059055;
    storage = "Rick Jones";
    temp->name = malloc(sizeof(char)*strlen(storage)+1);
    strcpy(temp->name, storage);
    insertData(hash, temp->studNum, (void*)temp);

    printf("\nSame Key Insertion Test - Expected: Rick Jones  8585  4169059055 \n                          Actual:  ");
    store = (dataTable*)lookupData(hash, 8585);
    if (store != NULL)
    {
        hash->printData((void*)store);
    }

    temp = malloc(sizeof(dataTable));
    temp->studNum = 658578;
    temp->phoneNum = 65;
    storage = "Harry";
    temp->name = malloc(sizeof(char)*strlen(storage)+1);
    strcpy(temp->name, storage);
    insertData(hash, temp->studNum, (void*)temp);

    printf("\nThird Insertion Test - Expected: Harry  658578  65 \n                        Actual:  ");
    store = (dataTable*)lookupData(hash, 658578);
    if (store != NULL)
    {
        hash->printData((void*)store);
    }

    removeData(hash, 8585);
    store = (dataTable*)lookupData(hash, 8585);
    printf("\nDeletion Test - Expected: Deleted! \n                Actual:  ");
    if (store == NULL)
    {
        printf("Deleted! \n");
    }

    removeData(hash, 79);
    store = (dataTable*)lookupData(hash, 79);
    printf("\nInvalid Key Deletion Test - Expected: NULL  \n                            Actual: ");
    if (store == NULL) {
        printf("NULL\n");
    }

    destroyTable(hash);
    hash = createTable(SIZE,&hashFunction,&destroyData,&printData);
    printf("\nDestroy Table Test - Expected: Deleted! Deleted! Deleted! \n                     Actual: ");
    store = (dataTable*)lookupData(hash, 968799);
    if(store == NULL)
    {
        printf("Deleted! ");
    }
    store = (dataTable*)lookupData(hash, 8585);
    if(store == NULL)
    {
        printf("Deleted! ");
    }
    store = (dataTable*)lookupData(hash, 49);
    if(store == NULL)
    {
        printf("Deleted! \n");
    }

    destroyTable(hash);
    printf("\nDestroy NULL Table Test - Expected:  \n                          Actual:  \n");

    hash = createTable(0,&hashFunction,&destroyData,&printData);
    printf("\nSize 0 Table Test - Expected: NULL \n                    Actual: ");
    if (hash == NULL) {
        printf("NULL\n\n");
    }

    return 0;
}
