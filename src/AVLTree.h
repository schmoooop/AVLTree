#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// AVL Tree Node struct
struct Node
{
    string name;
    string ufid;
    Node* left;
    Node* right;
    int height;


    Node(string name, string ufid){
        this->name = name;
        this->ufid = ufid;
        this->height = 0;
        this->left = nullptr;
        this->right = nullptr;
    }
};

class AVLTree
{
private:
    Node* root = nullptr;
    // getters
    int getHeight(Node* node);
    int getBalanceFactor(Node* node);
    Node* inorderSuccessor(Node* node);
    // rotations/balancing
    Node* rotateTree(Node* node);
    Node* rightRotation(Node* node);
    Node* leftRotation(Node* node);
    Node* leftRightRotation(Node* node);
    Node* rightLeftRotation(Node* node);
    // helpers
    Node* insertHelper(Node* node, string name, string ufid);
    void searchIDHelper(Node* node, string ufid);
    void searchNAMEHelper(Node* node, string name, vector<string>& specifiedNameIDs);
    void inOrderHelper(Node* node, bool& isFirst);
    Node* removeIDHelper(Node* node, string ufid);
    void removeInOrderHelper(Node* node, vector<string>& ufids);
    void preOrderHelper(Node* node, bool& isFirst);
    void postOrderHelper(Node* node, bool& isFirst);
public:
    // required functions
    void insertNameID(string name, string ufid);
    void removeID(string ufid);
    void searchID(string ufid);
    void searchName(string name);
    void printInOrder();
    void printPreOrder();
    void printPostOrder();
    void printLevelCount();
    void removeInOrder(int n);
    // functions used in main
    string nameCheck(string name);
    string idCheck(string ufid);
    bool isDigit(string n);
};
