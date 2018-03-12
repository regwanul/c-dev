#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <limits.h>

typedef struct node {
    int key;
    struct node *left;
    struct node *right;
} Node;


/*
 * Create a new node
 */
Node* newNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;

    return node;
}


/*
 * Insert node into tree recursively
 */
Node* treeInsert(Node* node, int key) {
    // if node is empty, create new
    if(node == NULL) {
        return newNode(key);
    }

    // otherwise, recur through tree
    if(key < node->key) {
        node->left = treeInsert(node->left, key);
    } else if(key > node->key) {
        node->right = treeInsert(node->right, key);
    }

    // return the unchanged node pointer
    return node;
}


/*
 * Insert node into tree iteratively
 */
void treeInsertIter(Node** node, int key) {
    if(*node == NULL) {
        // create new tree
        *node = newNode(key);
    } else {
        Node* current = *node;
        Node* parent = NULL;
        
        while(current != NULL) {
            if(key < current->key) {
                // go to left subtree
                parent = current;
                current = current->left;

                // if left node is empty, insert here
                if(current == NULL) {
                    current = newNode(key);
                    parent->left = current;
                    return;
                }
            } else if(key > current->key) {
                // go to right subtree
                parent = current;
                current = current->right;

                // if right node is empty, insert here
                if(current == NULL) {
                    current = newNode(key);
                    parent->right = current;
                    return;
                }
            }
        }
    }

    return;
}


/*
 * Delete a node in the tree
 */
Node* treeDeleteNode(Node* root, int key) {
    // base case
    if(root == NULL) {
        return NULL;
    }

    if(key < root->key) {
        // go to left subtree
        root->left = treeDeleteNode(root->left, key);
    } else if(key > root->key) {
        // go to right subtree
        root->right = treeDeleteNode(root->right, key);
    } else {
        // found matching key
        if(root->left == NULL) {
            // only right child exists
            Node* tempNode = root->right;
            free(root);
            return tempNode;
        } else if(root->right == NULL) {
            // only left child exists
            Node* tempNode = root->left;
            free(root);
            return tempNode;
        } else {
            // 2 children exist: get inorder successor
            Node* cursor = root->right;
            Node* parent = NULL;

            while(cursor->left != NULL) {
                parent = cursor;
                cursor = cursor->left;
            }
            root->key = cursor->key;
            if(parent != NULL) {
                parent->left = treeDeleteNode(parent->left, parent->left->key);
            } else {
                root->right = treeDeleteNode(root->right, root->right->key);
            }

        }

    }
    return root;
}


/*
 * Find the minimum value in tree
 */
int treeFindMin(Node* root) {
    Node* current = root;

    // traverse down the left brances of the tree to the last node
    while(current->left != NULL) {
        current = current->left;
    }
    return current->key;
}


/*
 * Find next node (inorder successor) in tree given a key 
 */
int treeFindNext(Node* root, int key) {
    Node* current = root;
    Node* ans = NULL;

    while(current != NULL) {
        if(current->key >= key) {
            ans = current;
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if(ans != NULL) {
        return ans->key;
    }

    return -1;
}


/*
 * Utility function for isBst()
 */
int isBstUtil(Node* root, int min, int max) {
    if(root == NULL) {
        return true;
    }

    if(root->key < min || root->key > max) {
        return false;
    }

    return ( isBstUtil(root->left, min, root->key-1) && 
            isBstUtil(root->right, root->key+1, max) );
}


/*
 * Validate if tree is a BST
 */
int isBst(Node* root) {
    return isBstUtil(root, INT_MIN, INT_MAX);   
}


/*
 * Traverse tree in order
 */
void treeTraverseInOrder(Node* node) {
    if(node != NULL) {
        treeTraverseInOrder(node->left);
        printf("%d->", node->key);
        treeTraverseInOrder(node->right);
    }
}


/*
 * Print the tree
 */
void treePrint(Node* node) {
    if(node == NULL) {
        return;
    }

    printf("%d", node->key);
    if(node->left != NULL) {
        printf("(L:%d)", node->left->key);
    }
    if(node->right != NULL) {
        printf("(R:%d)", node->right->key);
    }
    printf("\n");

    treePrint(node->left);
    treePrint(node->right);
}


void main() {
    Node* root = NULL;
    root = treeInsert(root, 50);
    treeInsert(root, 30);
    treeInsert(root, 20);
    treeInsert(root, 40);
    treeInsert(root, 70);
    treeInsert(root, 60);
    treeInsert(root, 80);

    treePrint(root);

    printf("Removed 20:\n");
    treeDeleteNode(root, 20);
    treePrint(root);
    printf("Removed 30:\n");
    treeDeleteNode(root, 30);
    treePrint(root);
    printf("Removed 50:\n");
    treeDeleteNode(root, 50);
    treePrint(root);

    Node* root2 = NULL;
    treeInsertIter(&root2, 2);
    treeInsertIter(&root2, 1);
    treeInsertIter(&root2, 3);
    treeInsertIter(&root2, 12);
    treeInsertIter(&root2, 9);
    treeInsertIter(&root2, 21);
    treeInsertIter(&root2, 19);
    treeInsertIter(&root2, 25);

    treePrint(root2);

    printf("\n%d\n", treeFindNext(root2, 25));

    Node* fakeBst = newNode(3);
    fakeBst->left = newNode(2);
    fakeBst->right = newNode(5);
    fakeBst->left->left = newNode(1);
    fakeBst->left->right = newNode(4);
    printf("Fake BST:\n");
    treePrint(fakeBst);
    printf("Is BST?: %s\n", isBst(fakeBst) ? "yes" : "no"); 
}
