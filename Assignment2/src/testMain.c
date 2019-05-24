/**
 * @file testMain.c
 * @author Tejinder Purba | 0968799 | tpurba@mail.uoguelph.ca
 * @date June 26th 2017
 * @brief File containing a main for testing of hash table and extra functions
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HashTableAPI.h"
#include "ExtraFunctions.h"

#define SIZE 1000

int hashFunction (size_t tableSize, char *key) {
    unsigned int hash = 0;
    int c;

    while ((c = *key++)) {
        hash = hash + c;
    }

    while (1) {
        if (hash > tableSize) {
            hash = hash - tableSize;
        }
        else {
            break;
        }
    }
    return hash;
}

void destroyData (void *data) {
    free(((dataTable*)data)->key);
    free(((dataTable*)data)->password);
    free((dataTable*)data);
    return;
}

void printData (void *toBePrinted) {
    if (toBePrinted != NULL) {
        dataTable *temp = (dataTable*)toBePrinted;
        printf("%s \n", temp->password);
    }
    return;
}

int main() {

    dataTable *temp = NULL;
    dataTable *store = NULL;
    char *storage;
    int grade = 0;
    int hashValue = 0;
    FILE *fp;
    int size = 0;

    /*
     *Test 1 Goal: To test whether a hash table is created and correctly allocated
     */
    printf("\nTest 1: Creating Table\n ");
    HTable *hash = createTable(0, &hashFunction, &destroyData, &printData);
    if (hash == NULL) {
        printf("       SUCCESS: Hash Table of size 0 not created\n");
        ++grade;
    }
    else {
        printf("       FAIL: Hash Table created\n");
    }

    hash = createTable(SIZE, &hashFunction, &destroyData, &printData);
    if (hash != NULL) {
        printf("        SUCCESS: Hash Table created\n");
        ++grade;
    }
    else {
        printf("        FAIL: Hash Table not created\n");
    }

    /*
     *Test 2 Goal: To test whether data is stored in the hash table at appropriate indexes
     */
    printf("\nTest 2: Inserting Data\n");
    temp = malloc(sizeof(dataTable));
    storage = "Gmail";
    temp->key = malloc(sizeof(char)*strlen(storage)+1);
    strcpy(temp->key, storage);
    storage = "TejinderP";
    temp->password = malloc(sizeof(char)*strlen(storage)+1);
    strcpy(temp->password, storage);
    insertData(hash, temp->key, (void*)temp);
    store = (dataTable*)lookupData(hash, "Gmail");
    printf("        Key: Gmail -- Password: TejinderP");
    if(strcmp(store->password, "TejinderP") == 0) {
        printf(" --> PASS\n");
        ++grade;
    }
    else {
        printf(" --> FAIL\n");
    }

    temp = malloc(sizeof(dataTable));
    storage = "YouTube";
    temp->key = malloc(sizeof(char)*strlen(storage)+1);
    strcpy(temp->key, storage);
    storage = "19980116";
    temp->password = malloc(sizeof(char)*strlen(storage)+1);
    strcpy(temp->password, storage);
    insertData(hash, temp->key, (void*)temp);

    printf("        Key: YouTube -- Password: 19980116");
    store = (dataTable*)lookupData(hash, "YouTube");
    if(strcmp(store->password, "19980116") == 0) {
        printf(" --> PASS\n");
        ++grade;
    }
    else {
        printf(" --> FAIL\n");
    }

    temp = malloc(sizeof(dataTable));
    storage = "01Laptop01";
    temp->key = malloc(sizeof(char)*strlen(storage)+1);
    strcpy(temp->key, storage);
    storage = "Testing123456789";
    temp->password = malloc(sizeof(char)*strlen(storage)+1);
    strcpy(temp->password, storage);
    insertData(hash, temp->key, (void*)temp);

    printf("        Key: 01Laptop01 -- Password: Testing123456789");
    store = (dataTable*)lookupData(hash, "01Laptop01");
    if (strcmp(store->password, "Testing123456789") == 0) {
        printf(" --> PASS\n");
        ++grade;
    }
    else {
        printf(" --> FAIL\n");
    }

    temp = malloc(sizeof(dataTable));
    storage = "YouTube";
    temp->key = malloc(sizeof(char)*strlen(storage)+1);
    strcpy(temp->key, storage);
    storage = "1234Testing1234";
    temp->password = malloc(sizeof(char)*strlen(storage)+1);
    strcpy(temp->password, storage);
    updateData(hash, temp->key, (void*)temp);

    printf("        Key: YouTube -- Password: 1234Testing1234");
    store = (dataTable*)lookupData(hash, "YouTube");
    if (strcmp(store->password, "1234Testing1234") == 0) {
        printf(" --> PASS\n");
        ++grade;
    }
    else {
        printf(" --> FAIL\n");
    }

    if ((grade - 2) == 4) {
        printf("        SUCCESS: All tests passed successfully\n");
    }
    else {
        printf("        FAIL: %d/4 tests failed\n", (grade - 1));
    }

    /*
     *Test 3 Goal: To test whether data can be retrieved from the hash table
     */
    printf("\nTest 3: Retrieving Data\n");
    store = (dataTable*)lookupData(hash, "YouTube");
    printf("        Key: YouTube -- Expected: 1234Testing1234 -- Actual: ");
    if (strcmp(store->password, "1234Testing1234") == 0) {
        hash->printData((void*)store);
        printf(" --> PASS\n");
        ++grade;
    }
    else {
        hash->printData((void*)store);
        printf(" --> FAIL\n");
    }

    store = (dataTable*)lookupData(hash, "Computer");
    printf("        Key: Computer -- Expected: NULL -- Actual: ");
    if (store == NULL) {
        printf("NULL");
        printf(" --> PASS\n");
        ++grade;
    }
    else {
        hash->printData((void*)store);
        printf(" --> FAIL\n");
    }

    store = (dataTable*)lookupData(hash, "Gmail");
    printf("        Key: Gmail -- Expected: TejinderP -- Actual: ");
    if (strcmp(store->password, "TejinderP") == 0) {
        hash->printData((void*)store);
        printf(" --> PASS\n");
        ++grade;
    }
    else {
        hash->printData((void*)store);
        printf(" --> FAIL\n");
    }

    if ((grade - 6) == 3) {
        printf("        SUCCESS: All tests passed successfully\n");
    }
    else {
        printf("        FAIL: %d/3 tests failed\n", (grade - 6));
    }

    /*
     *Test 4 Goal: To test whether data is correctly removed from the hash table
     */
    printf("\nTest 4: Removing Data\n");
    removeData(hash, "YouTube");
    store = (dataTable*)lookupData(hash, "YouTube");
    printf("        Key: Youtube -- Expected: NULL -- Actual: ");
    if (store == NULL) {
        printf("NULL --> PASS\n");
        ++grade;
    }
    else {
        printf("--> FAIL");
    }

    removeData(hash, "01Laptop01");
    store = (dataTable*)lookupData(hash, "YouTube");
    printf("        Key: 01Laptop01 -- Expected: NULL -- Actual: ");
    if (store == NULL) {
        printf("NULL --> PASS\n");
        ++grade;
    }
    else {
        printf("--> FAIL");
    }

    removeData(hash, "Computer");
    store = (dataTable*)lookupData(hash, "Computer");
    printf("        Key: Computer -- Expected: NULL -- Actual: ");
    if (store == NULL) {
        printf("NULL --> PASS\n");
        ++grade;
    }
    else {
        printf("--> FAIL");
    }

    if ((grade - 9) == 3) {
        printf("        SUCCESS: All tests passed successfully\n");
    }
    else {
        printf("        FAIL: %d/3 tests failed\n", (grade - 9));
    }

    /*
     *Test 5 Goal: To test whether the hash table is correctly destroyed of all data
     */
    printf("\nTest 5: Destroying Table\n");
    destroyTable(hash);
    hash = NULL;

    if (hash == NULL) {
        printf("        SUCCESS: Hash Table destroyed successfully\n");
        ++grade;
    }
    else {
        printf("        FAIL: Hash Table not destroyed\n");
    }

    destroyTable(hash);
    if (hash == NULL) {
        printf("        SUCCESS: NULL Hash Table destroyed successfully\n");
        ++grade;
    }
    else {
        printf("        FAIL: Hash Table not destroyed\n");
    }

    /*
     *Test 6 Goal: To test whether the hash table is written to a file correctly
     */
    printf("\nTest 6: Write Hash Table To File\n");
    hash =  createTable(SIZE, &hashFunction, &destroyData, &printData);
    printf("        Write empty hash to file -- Expected: 0  -- Actual: ");
    writeToFile(hash, "TESTING123456");
    fp = fopen("TESTING123456", "ab");
    size = ftell(fp);
    fclose(fp);

    if (size == 0) {
        printf("0  --> PASS");
        ++grade;
    }
    else {
        printf("%d --> FAIL", size);
    }

    temp = malloc(sizeof(dataTable));
    storage = "Gmail";
    temp->key = malloc(sizeof(char)*strlen(storage)+1);
    strcpy(temp->key, storage);
    storage = "TejinderP";
    temp->password = malloc(sizeof(char)*strlen(storage)+1);
    strcpy(temp->password, storage);
    insertData(hash, temp->key, (void*)temp);

    temp = malloc(sizeof(dataTable));
    storage = "YouTube";
    temp->key = malloc(sizeof(char)*strlen(storage)+1);
    strcpy(temp->key, storage);
    storage = "19980116";
    temp->password = malloc(sizeof(char)*strlen(storage)+1);
    strcpy(temp->password, storage);
    insertData(hash, temp->key, (void*)temp);

    temp = malloc(sizeof(dataTable));
    storage = "01Laptop01";
    temp->key = malloc(sizeof(char)*strlen(storage)+1);
    strcpy(temp->key, storage);
    storage = "Testing123456789";
    temp->password = malloc(sizeof(char)*strlen(storage)+1);
    strcpy(temp->password, storage);
    insertData(hash, temp->key, (void*)temp);

    writeToFile(hash, "TESTING123456");
    fp = fopen("TESTING123456", "ab");
    size = ftell(fp);
    fclose(fp);

    printf("\n        Write hash of size 6000 to file -- Expected: 6000 -- Actual: ");
    if (size == 6000) {
        printf("%d --> PASS\n", size);
        ++grade;
    }
    else {
        printf("%d --> FAIL\n", size);
    }

    if ((grade - 14) == 2) {
        printf("        SUCCESS: All tests passed successfully\n");
    }
    else {
        printf("        FAIL: %d/2 tests failed\n", (grade - 14));
    }

    /*
     *Test 7 Goal: To test whether data is parsed from a file to a hash table correctly
     */
    printf("\nTest 7: Parse Data File\n");
    destroyTable(hash);
    hash = createTable(SIZE, &hashFunction, &destroyData, &printData);

    fp = fopen("TESTING123456", "ab+");
    parseData(hash, fp);

    store = (dataTable*)lookupData(hash, "YouTube");
    printf("        Key: YouTube -- Expected: 19980116 -- Actual: ");
    if (strcmp(store->password, "19980116") == 0) {
        hash->printData((void*)store);
        printf(" --> PASS\n");
        ++grade;
    }
    else {
        hash->printData((void*)store);
        printf(" --> FAIL\n");
    }

    store = (dataTable*)lookupData(hash, "Gmail");
    printf("        Key: Gmail -- Expected: TejinderP -- Actual: ");
    if (strcmp(store->password, "TejinderP") == 0) {
        hash->printData((void*)store);
        printf(" --> PASS\n");
        ++grade;
    }
    else {
        hash->printData((void*)store);
        printf(" --> FAIL\n");
    }

    if ((grade - 16) == 2) {
        printf("        SUCCESS: All tests passed successfully\n");
    }
    else {
        printf("        FAIL: %d/2 tests failed\n", (grade - 16));
    }

    /*
     *Test 8 Goal: To test whether the hash function values are throughly spread
     */
    printf("\nTest 8: Hash Function Value Spread\n");
    hashValue = hashFunction(10, "Gmail");
    printf("        Table Size: 10 -- Key: Gmail -- Index: %d\n", hashValue);
    hashValue = hashFunction(10, "YouTube");
    printf("        Table Size: 10 -- Key: YouTube -- Index: %d\n", hashValue);
    hashValue = hashFunction(10, "01010101010101");
    printf("        Table Size: 10 -- Key: 01010101010101 -- Index: %d\n", hashValue);
    hashValue = hashFunction(100, "Phone");
    printf("        Table Size: 100 -- Key: Phone -- Index: %d\n", hashValue);
    hashValue = hashFunction(100, "LAPTOP");
    printf("        Table Size: 100 -- Key: LAPTOP -- Index: %d\n", hashValue);
    hashValue = hashFunction(100, "comp123uter");
    printf("        Table Size: 100 -- Key: comp123uter -- Index: %d\n", hashValue);
    hashValue = hashFunction(1000, "123123");
    printf("        Table Size: 1000 -- Key: 123123 -- Index: %d\n", hashValue);
    hashValue = hashFunction(1000, "WeBcAM");
    printf("        Table Size: 1000 -- Key: WeBcAM -- Index: %d\n", hashValue);
    hashValue = hashFunction(1000, "DRiNK");
    printf("        Table Size: 1000 -- Key: DRiNK -- Index: %d\n", hashValue);
    hashValue = hashFunction(100, "Test");
    printf("        Table Size: 1000 -- Key: Test -- Index: %d\n", hashValue);
    hashValue = hashFunction(100, "Tesu");
    printf("        Table Size: 1000 -- Key: Tesu -- Index: %d\n", hashValue);

    
    remove("TESTING123456");
    printf("\nFINAL GRADE: %d/18\n\n", grade);

    return 0;
}
