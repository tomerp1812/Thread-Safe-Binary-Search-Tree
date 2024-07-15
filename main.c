#include "binary_tree.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>


// Example usage
int main() {
    TreeNode *root = createNode(22);
    /* Insert random values */
    #pragma omp parallel for
    for (int i = 1; i < 4; i++) {
        root = insertNode(root, 10*i);
        root = insertNode(root, 10*i -1);
    }

    printf("In-order traversal: ");
    inorderTraversal(root);
    printf("Pre-order traversal: ");
    preorderTraversal(root);
    printf("Post-order traversal: ");
    postorderTraversal(root);
    printf("\n");

    #pragma omp parallel for
    for (int i = 2; i < 3; i++) {
        root = deleteNode(root, 10*i );
    }

    printf("In-order traversal: ");
    inorderTraversal(root);


    TreeNode *minNode = findMin(root);
    if (minNode != NULL) {
        printf("Minimum value: %d\n", minNode->data);
    } else {
        printf("Tree is empty.\n");
    }

    bool find = searchNode(root, 40);
    printf("Find 40: %s\n", find ? "true" : "false");


    // Free memory allocated for the tree
    freeTree(root);

    return 0;
}