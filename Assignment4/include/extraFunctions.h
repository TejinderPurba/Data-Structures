/**
 * @file extraFunctions.h
 * @author Tejinder Purba | 0968799 | tpurba@mail.uoguelph.ca
 * @date August 6th 2017
 * @brief File containing extra functions that communicate with the simulation.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "balancedTreeAPI.h"
#include "tree.h"

/**
*Data struct to store in Balanced Binary AVL Tree
**/
typedef struct Data{
	char *productID; ///< ID of the product to be stored
	char *productName; ///< name of the product to be stored
	char *publisher; ///< publisher of the product to be stored
	char *genre; ///< genre of the product to be stored 
	char *taxable; ///< whether product is taxable
	char *price; ///< price of the product to be stored
	float *quantity; ///< quantity of the product to be stored
}Data;

/**Function to split string into tokens, handles consecutive delimiters.
 *@param string char string that is to be split into tokens.
 *@param delim constant character that is to be used as the token delimiter.
 **/
char *parser(char *string, char const *delim);

/**Function to parse data from either a csv file or binary file as long as the format
 * is the same.
 *@param theTree pointer to Tree variable that data is to be stored in.
 *@param fp file pointer to file that data is to be read from.
 **/
void parseData(Tree *theTree, FILE *fp);

/**Function to cancel an invoice and return data to inventory.
 *@param inventory Tree pointer to return data back to.
 *@param invoiceType tree pointer to recover data from.
 *@param temp node pointer to traverse through invoice tree.
 **/
void returnData (Tree *inventory, Tree *invoiceType, TreeNode *temp);

/**Function to update persistent binary file data.
 *@param inventory tree pointer to inventory that is to be stored.
 **/
void updateBinaryInventory(Tree *inventory);

/**Function to recursively traverse through inventory to store binary file data.
 *@param temp treenode pointer to current node to store.
 *@param fp file pointer to binary file to store data in.
 **/
void updateHelp(TreeNode *temp, FILE *fp);

/**Function to check if search term is within product name.
 *@param string string that contains text to look for key in.
 *@param lookFor string that contains phrase to look for in text.
 **/
int match(char string[], char lookFor[]);

/**Function to search for search phrase in every product.
 *@param inventory tree pointer to product name sorted inventory.
 *@param inventoryID tree pointer to product id sorted inventory.
 *@param text string for phrase to be searching in each product name.
 *@param temp treeNode pointer to temp node to compare with.
 **/
void *searchFunction(Tree *inventory, Tree *inventoryID, char text[], TreeNode *temp);

/**Function to recursively traverse through inventory to compare strings.
 *@param inventory tree pointer to inventory to sort through.
 *@param text string for phrase to be searching in each product name.
 *@param temp treeNode pointer to temp node to compare with.
 *@param count integer pointer to keep track of any positive search results.
 **/
void searchHelper(Tree *inventory, char text[], TreeNode *temp, int *count);
