#include <iostream>
using namespace std;

class Node {
public:
    int code;
    int height;
    Node* left;
    Node* right;
    Node(int code, Node* left, Node* right) : code(code), left(left), right(right) {}
};

class BST_Tree {
private:
    Node* root;
    Node* insertNode(Node*& currentNode, int code);
    Node* searchNode(Node* currentNode, int code);
    Node* delNode(Node*& currentNode, Node* code);
    Node* maximum(Node* currentNode);
    Node* minimum(Node* currentNode);
    int height(Node* currentNode);
    int max(int h1, int h2);
    Node* LL_Rotation(Node* k2);
    Node* RR_Rotation(Node* k1);
    Node* LR_Rotation(Node* k3);
    Node* RL_Rotation(Node* k1);
    void print(Node* currentNode);
public:
    BST_Tree();
    void insertNode(int code);
    void delNode(Node* node);
    Node* searchNode(int code);
    void destroy(BST_Tree* currentNode);
    void print();
};

class AllocationSystem : public BST_Tree {
public:
    BST_Tree* Initialisation();
    string Allocate(int min, int& max, BST_Tree*& root);
    int Remained_cards();
private:
    string decrypter(int code);
    int random_generator(int min, int max);
    int count = 0;
};
