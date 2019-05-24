#ifndef STUDENT_TREE_API_
#define STUDENT_TREE_API_

/*You may add anything to this .h file that you need to add to your tree ADT*/

//YOU MUST LEAVE THESE TYPEDEFS AS IS. 
/**typedef for struct name*/
typedef struct BalancedBinTreeNode TreeNode;

/**typedef for struct name*/
typedef struct BalancedBinTree Tree;




/*complete the struct definitions.  You can change the existing parts if you wish.
*/

/**
*Tree struct for balanced binary AVL tree 
**/
struct BalancedBinTree {
  //define your tree here.  You can change these if you need to but your tree must be abstract.
    TreeNode *root; ///< pointer to generic data that is to be stored in the tree
    int (*compareFP) (void *data1, void *data2); ///< function pointer to a comparison function for the purpose of inserting and deleting elements
    void (*destroyFP) (void *data); ///< function pointer to a function to free a single pointer that is deleted from the tree
    void *(*copyFP)(void *toBeCopy); ///< function pointer to a function that copies pointer data

  };

/**
*Node struct for balanced binary AVL tree 
**/
struct BalancedBinTreeNode{
    void *data; ///< pointer to generic data that is to be stored in the heap
    TreeNode *left; ///< pointer to left tree node of current node. Null if empty.
    TreeNode *right; ///< pointer to right tree node of current node. Null if empty.
    
    //Add additional structure elements here
};

#include "balancedTreeAPI.h"

/**This function rotates the tree nodes that have a right-right shape.
 *@param temp pointer to tree node that is to be rotated.
 **/
TreeNode *rotateRightRight(TreeNode *temp);

/**This function rotates the tree nodes that have a left-left shape.
 *@param temp pointer to tree node that is to be rotated.
 **/
TreeNode *rotateLeftLeft(TreeNode *temp);

/**This function rotates the tree nodes that have a left-right shape.
 *@param temp pointer to tree node that is to be rotated.
 **/
TreeNode *rotateLeftRight(TreeNode *temp);

/**This function rotates the tree nodes that have a right-left shape.
 *@param temp pointer to tree node that is to be rotated.
 **/
TreeNode *rotateRightLeft(TreeNode *temp);

/**This function iterates and deletes each node in the tree.
 *@param toBeDeleted pointer to tree where the nodes are stored.
 *@param temp pointer to tree node that is to be deleted.
 **/
void destroyNodes(Tree *toBeDeleted, TreeNode *temp);

/**This function calculates the height of the tree at a certain node.
 *@param temp pointer to tree node that the height is to be calculated.
 **/
int height (TreeNode *temp);

/**This function balances the tree and calls the node balancer.
 *@param theTree pointer to tree that is to be balanced.
 **/
void balanceTree (Tree *theTree);

/**This function determines the balance factor of the node.
 *@param temp pointer to tree node that is to be calculated.
 **/
int balanceFactor (TreeNode *temp);

/**This function balances individual nodes of the tree.
 *@param temp pointer to tree node that is to be balanced.
 **/
void *balanceNode (TreeNode *temp);

/**This function determines the minimum value node to substitute.
 *@param temp pointer to tree node that the minimum value is to be found.
 **/
TreeNode *minValueNode (TreeNode *temp);

/**This function deletes a specific node in the tree and rearranges.
 *@param theTree pointer to tree that node is to be deleted from.
 *@param temp pointer to tree node that is to be deleted.
 *@param toBeDeleted pointer to data that is to be deleted.
 **/
TreeNode *deleteNode (Tree *theTree, TreeNode *temp, void *toBeDeleted);

/**This function prints the tree in order.
 *@param temp pointer to tree that node is to be printed.
 *@param printNodeFP pointer to print function.
 **/
void inOrder (TreeNode *temp, void (*printNodeFP) (void *data));

/**This function prints the tree pre order.
 *@param temp pointer to tree that node is to be printed.
 *@param printNodeFP pointer to print function.
 **/
void preOrder (TreeNode *temp, void (*printNodeFP) (void *data));

/**This function prints the tree post order.
 *@param temp pointer to tree that node is to be printed.
 *@param printNodeFP pointer to print function.
 **/
void postOrder (TreeNode *temp, void (*printNodeFP) (void *data));


#endif

