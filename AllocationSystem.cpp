#include <iostream>
#include <string>
#include "AllocationSystem.h"
using namespace std;

BST_Tree::BST_Tree() : root(NULL){}

Node* BST_Tree::insertNode(Node*& currentNode, int code) {
    if (currentNode == NULL) {
        currentNode = new Node(code, NULL, NULL);
    }
    if (code > (currentNode->code)) {
        currentNode->right = insertNode(currentNode->right, code);
        if (height(currentNode->right) - height(currentNode->left) == 2) {
            if (code < currentNode->right->code)
                currentNode = RL_Rotation(currentNode);
            else
                currentNode = RR_Rotation(currentNode);
        }
    }
    else if (code < (currentNode->code)) {
        currentNode->left = insertNode(currentNode->left, code);
        if (height(currentNode->left) - height(currentNode->right) == 2) {
            if (code < currentNode->left->code)
                currentNode = LL_Rotation(currentNode);
            else
                currentNode = LR_Rotation(currentNode);
        }
    }
    currentNode->height = max(height(currentNode->left), height(currentNode->right)) + 1;
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

void BST_Tree::print(Node* currentNode) {
    if (currentNode == NULL) {
        return;
    }
    print(currentNode->left);
    cout<<currentNode->code<<' ';
    print(currentNode->right);
}

void BST_Tree::print() {
    print(root);
}

int BST_Tree::height(Node* tree) {
    if (tree != NULL)
        return tree->height;
    return 0;
}

int BST_Tree::max(int h1, int h2) {
    return h1 > h2 ? h1 : h2;
}

Node* BST_Tree::LL_Rotation(Node* k2) {
    Node* k1;
    k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->left), height(k1->right)) + 1;
    return k1;
}

Node* BST_Tree::RR_Rotation(Node* k1) {
    Node* k2;
    k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1->height = max(height(k1->left), height(k1->right)) + 1;
    k2->height = max(height(k2->left), height(k2->right)) + 1;
    return k2;
}

Node* BST_Tree::LR_Rotation(Node* k3) {
    k3->left = RR_Rotation(k3->left);
    return LL_Rotation(k3);
}

Node* BST_Tree::RL_Rotation(Node* k1) {
    k1->right = LL_Rotation(k1->left);
    return LL_Rotation(k1);
}

void AllocationSystem::Initalisation(){
    
    int min = 1;
    int max = 208;
    for (int min; min <= max; min++){
        
}

void AllocateSystem::Allocate(int random){
}

