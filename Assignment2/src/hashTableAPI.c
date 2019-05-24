/**
 * @file hashTableAPI.c
 * @author Tejinder Purba | 0968799 | tpurba@mail.uoguelph.ca
 * @date June 26th 2017
 * @brief File containing the function definitions and implementations of a hash table
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HashTableAPI.h"

HTable *createTable(size_t size, int (*hashFunction)(size_t tableSize, char *key),void (*destroyData)(void *data),void (*printData)(void *toBePrinted))
{
    HTable *newTable;
    int i = 0;

    newTable = malloc(sizeof(HTable));
    if (size > 1) {
        newTable->table = malloc(size*sizeof(Node));
    }
    else if (size == 1) {
        newTable->table = malloc(sizeof(Node));
    }
    else {
        free(newTable);
        return NULL;
    }

    if (newTable != NULL) {
        newTable->size = size;
        newTable->destroyData = destroyData;
        newTable->hashFunction = hashFunction;
        newTable->printData = printData;
    }

    for (i = 0; i < size; ++i) {
        newTable->table[i] = NULL;
    }

    return newTable;
}

Node *createNode(char *key, void *data)
{
    Node *newNode;
    newNode = malloc(sizeof(Node));

    newNode->next = NULL;
    newNode->key = key;
    newNode->data = data;

    return newNode;
}

void destroyTable(HTable *hashTable)
{
    Node *tempNode = NULL;
    Node *tempDeleteNode = NULL;
    void (*deleteFunc)(void *data);
    int i = 0;

    if (hashTable == NULL) {
        return;
    }

    deleteFunc = hashTable->destroyData;
    for (i = 0; i < hashTable->size; ++i) {
        if (hashTable->table[i] != NULL) {
            tempNode = hashTable->table[i];
        }

        while (tempNode != NULL) {
            tempDeleteNode = tempNode;
            tempNode = tempNode->next;
            deleteFunc(tempDeleteNode->data);
            free(tempDeleteNode);
        }
    }

    free(hashTable->table);
    free(hashTable);

    return;
}

void insertData(HTable *hashTable, char *key, void *data)
{
    Node *newNode;
    Node *tempNode;
    int (*hashFunc)(size_t tableSize, char *key);
    if (hashTable != NULL) {
        int index = 0;
        newNode = createNode(key, data);
        hashFunc = hashTable->hashFunction;
        if (hashTable->size > 0) {
            index = hashFunc(hashTable->size, key);
        }

        if (hashTable->table[index] != NULL) {
            tempNode = hashTable->table[index];
            while (tempNode != NULL) {
                if (tempNode->next == NULL) {
                    tempNode->next = newNode;
                    newNode->next = NULL;
                }
                tempNode = tempNode->next;
            }
        }

        else {
            hashTable->table[index] = newNode;
        }
    }

    return;
}

void updateData(HTable *hashTable, char *key, void *data)
{
    Node *newNode;
    Node *tempNode;
    int (*hashFunc)(size_t tableSize, char *key);
    if (hashTable != NULL) {
        void (*deleteFunc)(void *data);
        int index = 0;
        newNode = createNode(key, data);
        hashFunc = hashTable->hashFunction;
        deleteFunc = hashTable->destroyData;
        if (hashTable->size > 0) {
            index = hashFunc(hashTable->size, key);
        }

        if (hashTable->table[index] != NULL) {
            if (strcmp(hashTable->table[index]->key, key) == 0) {
                newNode->next = hashTable->table[index]->next;
                deleteFunc(hashTable->table[index]->data);
                free(hashTable->table[index]);
                hashTable->table[index] = newNode;
            }
            else {
                Node *tempDeleteNode = NULL;
                tempNode = hashTable->table[index];
                while (tempNode != NULL) {
                    if (strcmp(tempNode->key, key) == 0) {
                        newNode->next = tempNode->next;
                        tempDeleteNode->next = newNode;
                        deleteFunc(tempNode->data);
                        free(tempNode);
                        break;
                    }
                    tempDeleteNode = tempNode;
                    tempNode = tempNode->next;
                }
            }
        }
    }
    return;
}

void removeData(HTable *hashTable, char *key)
{
    Node *node;
    int (*hashFunc)(size_t tableSize, char *key);

    if (hashTable != NULL) {
        int index = 0;
        hashFunc = hashTable->hashFunction;
        if (hashTable->size > 0) {
            index = hashFunc(hashTable->size, key);
        }

        if (hashTable->table[index] != NULL) {
            Node *prev = NULL;
            node = hashTable->table[index];

            while (strcmp(node->key, key) > 0 || strcmp(node->key, key) < 0) {
                prev = node;
                if (node->next == NULL) {
                    break;
                }
                node = node->next;
            }
            if (strcmp(node->key, key) == 0) {
                void (*deleteFunc)(void *data);
                deleteFunc = hashTable->destroyData;
                if (prev == NULL) {
                    hashTable->table[index] = node->next;
                    deleteFunc(node->data);
                    free(node);
                    if (hashTable->table[index] == NULL) {
                        free(hashTable->table[index]);
                    }
                }
                else {
                    prev->next = node->next;
                    deleteFunc(node->data);
                    free(node);
                }
            }
        }
    }

    return;
}

void *lookupData(HTable *hashTable, char *key)
{
    Node *tempNode = NULL;
    int (*hashFunc)(size_t tableSize, char *key);

    if (hashTable != NULL) {
        int index = 0;
        hashFunc = hashTable->hashFunction;
        if (hashTable->size > 0) {
            index = hashFunc(hashTable->size, key);
        }

        if (hashTable->table[index] == NULL) {
            return NULL;
        }
        tempNode = hashTable->table[index];
        while (tempNode != NULL) {
            if (strcmp(tempNode->key, key) == 0) {
                return tempNode->data;
            }
            tempNode = tempNode->next;
        }
    }
    return NULL;
}


