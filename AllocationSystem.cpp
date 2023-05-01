#include <iostream>
#include <string>
#include "AllocationSystem.h"
using namespace std;

Node* BST_Tree::insertNode(Node* &currentNode, int key) {
    if (currentNode == NULL) {
        currentNode = new Node(code, NULL, NULL);
        currentNode->key = key;
        currentNode->left = NULL;
        currentNode->right = NULL;
    }
    if (key > (currentNode->key)) {
        currentNode->right = Insert(currentNode->right, key);
    }
    else if (key < (currentNode->key)) {
        currentNode->left = Insert(currentNode->left, key);
    }
    return currentNode;
}

Node* BST_Tree::searchNode(Node* currentNode, int key) {
    if (currentNode == NULL)
        return NULL;
    if (currentNode->key < key)
        return Find(currentNode->right, key);
    else if (currentNode->key > key)
        return Find(currentNode->left, key);
    else
        return currentNode;
}

Node* BST_Tree::delNode(Node* &currentNode, Node* node){
    if (currentNode == NULL)
        return NULL;
    else if (node->code > currentNode->code){
        currentNode->right = delNode(currentNode->right, node);
        return currentNode;
    }
    else if (node->code < currentNode->code){
        currentNode->left = delNode(currentNode->left, node);
        return currentNode;
    }
    else{
        if (currentNode->left && currentNode->right){
            Node* now = new Node(minimum(currentNode->right));
            currentNode->code = new->code;
            currentNode->right = delNode(currentNode->right, now); 
        }
        else{
            Node* temp = currentNode;
            if (currentNode->left == NULL)
                currentNode = currentNode->right;
            else if (currentNode->right == NULL)
                currentNode = currentNode->left;
            delete temp;
        }
        return currentNode;
}

Node* BST_Tree::minimum(Node* currentNode) {
    if (currentNode->left == NULL)
        return currentNode;
    else
        return FindMin(currentNode->left);
}

Node* BST_Tree::maximum(Node* currentNode) {
    if (currentNode->right == NULL)
        return currentNode;
    else
        return FindMax(currentNode->right);
}

