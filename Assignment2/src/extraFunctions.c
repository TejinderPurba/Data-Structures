/**
 * @file extraFunctions.c
 * @author Tejinder Purba | 0968799 | tpurba@mail.uoguelph.ca
 * @date June 26th 2017
 * @brief File containing extra function definitions and implementations of a hash table
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "HashTableAPI.h"
#include "ExtraFunctions.h"

void parseData (HTable *table, FILE *fp)
{
    fileTable temp;

    if (fp != NULL) {
        fseek(fp, 0, SEEK_SET);
        int c;
        while ((c = fgetc(fp)) !=  EOF) {
            dataTable *store;
            fseek(fp, -1, SEEK_CUR);
            fread(&temp, sizeof(fileTable), 1, fp);

            store = malloc(sizeof(dataTable));
            store->key =  malloc(sizeof(char)*strlen(temp.fileKey)+1);
            store->password = malloc(sizeof(char)*strlen(temp.filePassword)+1);

            strcpy(store->key, temp.fileKey);
            strcpy(store->password, temp.filePassword);

            insertData(table, store->key, (void*)store);
        }
        if (c == EOF) {
        }
    }

    return;
}

void writeToFile (HTable *table, char file[1000])
{

    Node *tempNode = NULL;
    Node *tempDeleteNode = NULL;
    FILE *fp;
    fileTable store;
    dataTable *temp;
    int i = 0;

    if (table == NULL) {
        return;
    }

    remove(file);
    fp = fopen(file, "wb+");
    for (i = 0; i < table->size; ++i) {
        if (table->table[i] != NULL) {
            tempNode = table->table[i];
        }

        while (tempNode != NULL) {
            tempDeleteNode = tempNode;
            tempNode = tempNode->next;
            temp = tempDeleteNode->data;
            strcpy(store.fileKey, temp->key);
            strcpy(store.filePassword, temp->password);
            fwrite(&store, sizeof(fileTable), 1, fp);
        }
    }

    fseek(fp, 0, SEEK_END);
    if ((ftell(fp)) == 0) {
        remove(file);
    }

    fclose(fp);
    return;
}
