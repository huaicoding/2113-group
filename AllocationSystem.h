#include <iostream>
using namespace std;

class Node {
public:
    int code;
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
public:
    BST_Tree();
    void insertNode(int code);
    void delNode(Node* node);
    Node* searchNode(int code);
};

class AllocationSystem : public BST_Tree {
public:
    void Initialisation(int code);
    void Allocate(int random);
    void printRules();
    void insurance(string rankst, string ranknd, double bet, double& balance);
private:
    string decrypter(int code);
};
