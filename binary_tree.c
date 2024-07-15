//
// Created by Omer Bar on 12/07/2024.
//
#include <stdbool.h>
#include "binary_tree.h"
#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0


// typedef struct TreeNode {
//     int data;
//     struct TreeNode *left;
//     struct TreeNode *right;
//     omp_lock_t lock;
// } TreeNode;

// Function to create a new binary tree node
TreeNode* createNode(int data) {
    TreeNode* node = (TreeNode*) malloc(sizeof(TreeNode));
    if (node == NULL) {
        printf("failed to malloc createNode");
        exit(1);
    }
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    omp_init_lock(&node->lock);
    return node;
}

// Function to insert a new node into the binary tree (iterative version)
TreeNode* insertNode(TreeNode* root, int data) {
    TreeNode* newNode = createNode(data);
    if (root == NULL) {
        return newNode;
    }
    TreeNode* current = root;
    TreeNode* parent = NULL;
    // lock current
    omp_set_lock(&current->lock);
    while (current != NULL) {
        parent = current;
        if (data < current->data) {
            current = current->left;
        } else if (data > current->data) {
            current = current->right;
        } else {
            // unlock parent
            omp_unset_lock(&current->lock);
            free(newNode);
            return root;
        }
        // if current != null -> lock current
        // else -> break;
        // unlock parent
        if (current != NULL) {
            omp_set_lock(&current->lock);
            omp_unset_lock(&parent->lock);
        } else {
            break;
        }
    }
    if (data < parent->data) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }
    // unlock parent
    omp_unset_lock(&parent->lock);
    return root;
}

// Function to delete a node from the binary tree
TreeNode* deleteNode(TreeNode* root, int data) {
    if (root == NULL) {
        return NULL;
    }

    TreeNode* current = root;
    TreeNode* parent = NULL;

    // Find the node to delete and its parent
    // lock current
    omp_set_lock(&current->lock);
    while (current->data != data) {
        parent = current;
        if (data < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
        // if current != null -> lock current
        // else -> break;
        if (current != NULL) {
            omp_set_lock(&current->lock);
            omp_unset_lock(&parent->lock);
        } else {
            omp_unset_lock(&parent->lock);
            return root;
        }
    }

    // Node to delete found, handle three cases
    if (current->left == NULL || current->right == NULL) {
        // Node has at most one child
        TreeNode* newChild;
        if (current->left == NULL) {
            newChild = current->right;
        } else {
            newChild = current->left;
        }

        // Replace the node with its child
        if (parent == NULL) {
            // The node to delete is the root
            root = newChild;
        } else if (current == parent->left) {
            parent->left = newChild;
        } else {
            parent->right = newChild;
        }
        omp_unset_lock(&current->lock);
        omp_destroy_lock(&current->lock);
        free(current);
    } else {
        // Node has two children, find the in-order successor (smallest in the right subtree)
        TreeNode* minParent = current;
        TreeNode* minNode = current->right;

        // omp_set_lock(&minNode->lock);
        while (minNode->left != NULL) {
            // TreeNode* temp = minNode;
            minParent = minNode;
            minNode = minNode->left;
            // omp_set_lock(&minNode->lock);   
            // omp_unset_lock(&temp->lock);           
        }

        // Replace current node's data with in-order successor's data
        current->data = minNode->data;

        // Delete the in-order successor node
        if (minParent->left == minNode) {
            minParent->left = minNode->right;
        } else {
            minParent->right = minNode->right;
        }
        // omp_unset_lock(&minNode->lock);
        omp_destroy_lock(&minNode->lock);
        free(minNode);
        omp_unset_lock(&current->lock);
    }

    return root;
}

// Function to search for a node in the binary tree
bool searchNode(TreeNode* root, int data) {
    if (root == NULL) {
        return false;
    }
    TreeNode* current = root;
    TreeNode* parent = NULL;
    omp_set_lock(&current->lock);
    while(current != NULL){
        if(current->data == data){
            omp_unset_lock(&current->lock);
            return true;
        }
        parent = current;
        if(data < current->data){
            current = current->left;
        } else{
            current = current->right;
        }
        if(current != NULL){
            omp_set_lock(&current->lock);
            omp_unset_lock(&parent->lock);
        }
    }
    omp_unset_lock(&parent->lock);
    return false;
}

// Function to find the minimum value node in the binary tree
TreeNode* findMin(TreeNode* root) {
    if(root == NULL){
        return NULL;
    }
    TreeNode* current = root;
    TreeNode* parent = NULL;
    // lock root
    omp_set_lock(&current->lock);
    while (current->left != NULL) {
        parent = current;
        current = current->left;
        omp_set_lock(&current->lock);
        omp_unset_lock(&parent->lock);
    }
    // unlock root
    omp_unset_lock(&current->lock);
    return current;
}

// Function to perform an in-order traversal of the binary tree
void inorderTraversal(TreeNode* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        omp_set_lock(&root->lock);
        printf("%d ", root->data);
        omp_unset_lock(&root->lock);
        inorderTraversal(root->right);
    }
}

// Function to perform a pre-order traversal of the binary tree
void preorderTraversal(TreeNode* root) {
    if (root != NULL) {
        omp_set_lock(&root->lock);
        printf("%d ", root->data);
        omp_unset_lock(&root->lock);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

// Function to perform a post-order traversal of the binary tree
void postorderTraversal(TreeNode* root) {
    if (root != NULL) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        omp_set_lock(&root->lock);
        printf("%d ", root->data);
        omp_unset_lock(&root->lock);
    }
}

// Function to free all nodes in the binary tree
void freeTree(TreeNode* root) {
    if (root != NULL) {
        omp_set_lock(&root->lock);
        freeTree(root->left);
        freeTree(root->right);
        omp_unset_lock(&root->lock);
        omp_destroy_lock(&root->lock);
        free(root);
    }
}

