# Thread-Safe-Binary-Search-Tree
A robust and efficient thread-safe binary search tree implemented in C, ensuring safe concurrent operations using pthreads

This project is a robust and efficient binary search tree (BST) implemented in C, designed to support safe concurrent operations. The thread safety is achieved using OpenMP locks, ensuring that multiple threads can perform insertions, deletions, and searches without causing data races or inconsistencies.

## Features
- Thread Safety: Utilizes OpenMP locks to ensure safe concurrent access and modifications.
- Basic Operations: Supports standard BST operations such as insertion, deletion, and search.
- Traversal Methods: Implements in-order, pre-order, and post-order traversal methods.
- Utility Functions: Includes functions to find the minimum value node and to free all nodes in the tree.
- Testing: A comprehensive main function is provided to test the BST operations and demonstrate their functionality.
- Thread Efficiency: Uses OpenMP locks only in necessary sections, rather than naively locking the entire tree, to ensure the code is truly parallel and efficient.

## Files
- binary_tree.h: Header file containing the definitions of the tree node structure and function prototypes.
- binary_tree.c: Implementation file with the definitions of the BST operations and utility functions.
- main.c: Example usage and testing of the binary search tree operations.
- Makefile: File to compile the project.

## Usage
Clone the repository to your preferred path:
```bash
git clone https://github.com/tomerp1812/Thread-Safe-Binary-Search-Tree.git
cd Thread-Safe-Binary-Search-Tree
```
Compilation
To compile the project, use the provided Makefile:
```bash
make
```

Run the compiled executable:
```bash
./binary_search_tree
```
