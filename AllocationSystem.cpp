#include <iostream>
#include <string>
#include "time.h"
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
    if (currentNode == NULL || node == NULL)
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

int BST_Tree::height(Node* currentNode) {
    if (currentNode != NULL)
        return currentNode->height;
    else
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

BST_Tree* AllocationSystem::Initialisation() {
    int max = 208;
    int min = 1;
    BST_Tree* root = new BST_Tree();
    for (min; min <= max; min++)
        root->insertNode(min);
    return root;
}

string AllocationSystem::Allocate(int min, int &max, BST_Tree* root) {
    int target = random_generator(min, max);
    Node* item = root->searchNode(target);
    root->delNode(item);
    string card = decrypter(target);
    max--; 
    return card;
}

string AllocationSystem::decrypter(int code) { // code [1, 208]
    string card;
    char suit[4] = { 'C', 'H', 'S', 'D' };
    string rank[13] = { "K", "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q" };
    if (code % 13 != 0) {
        int s = (code / 13 + 1) % 4;
        card = suit[s];
        int r = code % 13;
        card = card + rank[r];
    }
    else {
        int s = (code / 13) % 4;
        card = suit[s];
        int r = code % 13;
        card = card + rank[r];
    }
    return card;
}

int AllocationSystem::random_generator(int min, int max) {
    srand((unsigned)time(NULL));
    int range = max - min + 1;
    return rand() % range + min;
}
