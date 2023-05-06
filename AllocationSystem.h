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

class BST_Tree { //Build the container of cards based on a Binary Search Tree 
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
public:
    BST_Tree();
    void insertNode(int code);
    void delNode(Node* node);
    Node* searchNode(int code);
    void destroy(BST_Tree* currentNode);
};

class AllocationSystem : public BST_Tree { 
public:
    BST_Tree* Initialisation(); //Used to generate the container of cards
    string Allocate(int min, int& max, BST_Tree*& root); //Allocate the cards randomly, destroy the node in the tree.
    int Remained_cards(); //If more than 120 cards allocated, the allocation system will shuffle the cards. This function is used to count the number of remaining cards.
private:
    string decrypter(int code); //The information of card is stored in the binary search tree as integers. This function is used to decrypte the numerical code into suit and rank
    int random_generator(int min, int max); //Generate a random code.
    int count = 0; // Number of allocated cards
};
