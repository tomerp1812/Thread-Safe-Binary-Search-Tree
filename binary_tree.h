

#ifndef BINARY_TREE_H
#define BINARY_TREE_H
#include <stdbool.h>
#include <omp.h>
// Definition of a binary tree node
typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
    omp_lock_t lock;
} TreeNode;
// Function to create a new binary tree node
TreeNode* createNode(int data);
// Function to insert a new node into the binary tree
TreeNode* insertNode(TreeNode* root, int data);
// Function to delete a node from the binary tree
TreeNode* deleteNode(TreeNode* root, int data);
// Function to search for a node in the binary tree
bool searchNode(TreeNode* root, int data);
// Function to find the minimum value node in the binary tree
TreeNode* findMin(TreeNode* root);
// Function to perform an in-order traversal of the binary tree
void inorderTraversal(TreeNode* root);
// Function to perform a pre-order traversal of the binary tree
void preorderTraversal(TreeNode* root);
// Function to perform a post-order traversal of the binary tree
void postorderTraversal(TreeNode* root);
// Function to free all nodes in the binary tree
void freeTree(TreeNode* root);
#endif // BINARY_TREE_H