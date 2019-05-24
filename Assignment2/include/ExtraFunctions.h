/**
 * @file ExtraFunctions.h
 * @author Tejinder Purba | 0968799 | tpurba@mail.uoguelph.ca
 * @date June 26th 2017
 * @brief File containing extra function definitions of a hash table
 **/

#ifndef _EXTRA_FUNCTIONS_
#define _EXTRA_FUNCTIONS_

#include <stdio.h>
#include <stdlib.h>

/**
*Struct to store data for nodes. 
**/
typedef struct hashData
{
    char *key; ///< pointer to character data that represents a key in the data
    char *password; ///< pointer to character daya that represents a password in the data
}dataTable;

/**
*Struct to store data in files. 
**/
typedef struct fileData
{
    char fileKey[1000]; ///< character data that represents a key in the data
    char filePassword[1000]; ///< character data that represents a password in the data
}fileTable;

/**Parses data from a file into hashtable.
*@pre hashTable type must exist and have data allocated to it. File must exist.
*@param table hashTable pointer to the hash table.
*@param fp file pointer pointing to file where data is stored.
**/
void parseData (HTable *table, FILE *fp);

/**Write hashtable data to file.
*@pre hashTable type must exist and have data allocated to it. File must exist.
*@param table hashTable pointer to the hash table.
*@param file name of file to store hashtable data in.
**/
void writeToFile (HTable *table, char file[1000]);





#endif
