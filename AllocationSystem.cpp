#include <iostream>
#include <string>
#include "AllocationSystem.h"
using namespace std;

Node* BST_Tree::Insert(Node* &currentNode, int key) {
    if (currentNode == NULL) {
        ;
        currentNode->key = key;
        currentNode->left = NULL;
        currentNode->right = NULL;
    }
    if (key > (currentNode->key)) {
        // Case 2: If the tree rooted at currentNode is not empty and if the given key is greater than currentNode -> key
        // To be implemented
        currentNode->right = Insert(currentNode->right, key);
    }
    else if (key < (currentNode->key)) {
        // Case 3: If the tree rooted at currentNode is not empty and if the given key is smaller than currentNode -> key
        // To be implemented
        currentNode->left = Insert(currentNode->left, key);
    }
    return currentNode;
}

void Print(treeNode* currentNode) {
    if (currentNode == NULL) {
        return;
    }
    Print(currentNode->left);
    printf("%d ", currentNode->key);
    Print(currentNode->right);
}

treeNode* FindMin(treeNode* currentNode) {
    // To be implemented
    if (currentNode->left == NULL)
        return currentNode;
    else
        return FindMin(currentNode->left);
}

treeNode* FindMax(treeNode* currentNode) {
    // To be implemented
    if (currentNode->right == NULL)
        return currentNode;
    else
        return FindMax(currentNode->right);
}

treeNode* Find(treeNode* currentNode, int key) {
    // To be implemented
    if (currentNode == NULL)
        return NULL;
    if (currentNode->key < key)
        return Find(currentNode->right, key);
    else if (currentNode->key > key)
        return Find(currentNode->left, key);
    else
        return currentNode;
}
