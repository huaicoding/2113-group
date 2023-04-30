#include <iostream>
using namespace std;

class Node{
  public:
  int code;
  Node* left;
  Node* right;
};

class BST_Tree{
private:
    Node* root;
	  Node* insertNode(AVL_Node*& tree, int code);
	  Node* searchNode(AVL_Node* tree, int code);
	  Node* delNode(AVL_Node*& tree, AVL_Node* code);
    Node* maximum(AVL_Node* tree);
		Node* minimum(AVL_Node* tree);
  public:
		void insertNode(int code);
		void delNode(AVL_Node* node);
		AVL_Node* searchNode(int code);
};

class AllocationSystem: public AVL_Tree {
	public:
		void Initialisation(int code);
		void Allocate(int random);
		void printRules();
		void insurance(string rankst, string ranknd, double bet, double& balance);
		string decrypter(int code);
};
