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
};

class AllocationSystem: public AVL_Tree {
public:
	void Initialisation(int code);
	void Allocate(int random);
	void printRules();
	void insurance(string rankst, string ranknd, double bet, double& balance);
private:
	string decrypter(int code);
};
