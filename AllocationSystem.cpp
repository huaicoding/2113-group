#include <iostream>
#include <string>
#include "AllocationSystem.h"
using namespace std;

BST_Tree::BST_Tree() : root(NULL){}

Node* BST_Tree::insertNode(Node*& currentNode, int code) {
    if (currentNode == NULL) {
        currentNode = new Node(code, NULL, NULL);
        currentNode->code = code;
        currentNode->left = NULL;
        currentNode->right = NULL;
    }
    if (code > (currentNode->code)) {
        currentNode->right = insertNode(currentNode->right, code);
    }
    else if (code < (currentNode->code)) {
        currentNode->left = insertNode(currentNode->left, code);
    }
    return currentNode;
}

void BST_Tree::insertNode(int code) {
    insertNode(root, code);
}

Node* BST_Tree::searchNode(Node* currentNode, int code) {
    if (currentNode == NULL)
        return NULL;
    if (currentNode->code < code)
        return searchNode(currentNode->right, code);
    else if (currentNode->code > code)
        return searchNode(currentNode->left, code);
    else
        return currentNode;
}

Node* BST_Tree::searchNode(int code) {
    return searchNode(root, code);
}

Node* BST_Tree::delNode(Node*& currentNode, Node* node) {
    if (currentNode == NULL)
        return NULL;
    else if (node->code > currentNode->code) {
        currentNode->right = delNode(currentNode->right, node);
        return currentNode;
    }
    else if (node->code < currentNode->code) {
        currentNode->left = delNode(currentNode->left, node);
        return currentNode;
    }
    else {
        if (currentNode->left && currentNode->right) {
            Node* now = minimum(currentNode->right);
            currentNode->code = now->code;
            currentNode->right = delNode(currentNode->right, now);
        }
        else {
            Node* temp = currentNode;
            if (currentNode->left == NULL)
                currentNode = currentNode->right;
            else if (currentNode->right == NULL)
                currentNode = currentNode->left;
            delete temp;
        }
        return currentNode;
    }
}

void BST_Tree::delNode(Node* node) {
    delNode(root, node);
}

Node* BST_Tree::minimum(Node* currentNode) {
    if (currentNode->left == NULL)
        return currentNode;
    else
        return minimum(currentNode->left);
}

Node* BST_Tree::maximum(Node * currentNode) {
    if (currentNode->right == NULL)
        return currentNode;
    else
        return maximum(currentNode->right);
}
