#include "AVLTree.h"
using namespace std;

/*-----------------GETTERS-----------------*/
// source I found out about the max() function from: https://www.geeksforgeeks.org/stdmax-in-cpp/
int AVLTree::getHeight(Node* node)
{
    if (node == nullptr) return 0;
    else return 1 + max(getHeight(node->left), getHeight(node->right));
}

int AVLTree::getBalanceFactor(Node* node)
{
    if (node == nullptr) return 0;
    // calculates left height - right height
    else return getHeight(node->left) - getHeight(node->right);
}

Node* AVLTree::inorderSuccessor(Node* node)
{
    while(node->left != nullptr) node = node->left;
    return node;
}

/*-----------------TREE BALANCING AND ROTATIONS-----------------*/
// used pseudocode from  "The AVL Tree Rotations Tutorial" by John Hargrove
Node* AVLTree::rotateTree(Node* node)
{
    // if tree is right heavy; left rotation or right-left rotation
    if (getBalanceFactor(node) < -1 )
    {
        // if node right child is left heavy
        if(getBalanceFactor(node->right) > 0) return rightLeftRotation(node);
            // if node's right child is left heavy
        else return leftRotation(node);
    }
        // if tree is left-heavy; right rotation or left-right rotation
    else if(getBalanceFactor(node) > 1)
    {
        // if node's left child is right heavy
        if (getBalanceFactor(node->left) < 0) return leftRightRotation(node);
            // if node left child is left heavy
        else return rightRotation(node);
    }
    return node;
}

// from stepik m5
Node* AVLTree::rightRotation(Node* node)
{
    Node* leftChild = node->left;
    node->left = leftChild->right;
    leftChild->right = node;
    return leftChild;
}

// from stepik m5
Node* AVLTree::leftRotation(Node* node)
{
    Node* rightChild = node->right;
    node->right = rightChild->left;
    // rotation
    rightChild->left = node;
    return rightChild;
}

// from stepik m5
Node* AVLTree::leftRightRotation(Node* node)
{
    node->left = leftRotation(node->left);
    return rightRotation(node);
}

// from stepik m5
Node* AVLTree::rightLeftRotation(Node* node)
{
    node->right = rightRotation(node->right);
    return leftRotation(node);
}

/*-----------------HELPER FUNCTIONS-----------------*/
Node* AVLTree::insertHelper(Node* node, string name, string ufid)
{
    if (node == nullptr)
    {
        cout << "successful" << endl;
        return new Node(name, ufid);
    }
    else if(ufid < node->ufid) node->left = insertHelper(node->left, name, ufid);
    else if (ufid > node->ufid) node->right = insertHelper(node->right, name, ufid);
    else cout << "unsuccessful" << endl; // maybe this works instead of return 0?

    // check
    node = rotateTree(node);
    node->height = getHeight(node);
    return node;
}

void AVLTree::searchIDHelper(Node* node, string ufid)
{
    // if empty return
    if (node == nullptr)
    {
        cout << "unsuccessful" << endl;
        return;
    }
    // look for node w/ ID
    else if(ufid > node->ufid) searchIDHelper(node->right, ufid);
    else if(ufid < node->ufid) searchIDHelper(node->left, ufid);
    // if found, print name associated w/ ID
    else cout << node->name << endl;
}

void AVLTree::searchNAMEHelper(Node* node, string name, vector<string>& specifiedNameIDs)
{
    // if empty return
    if(node == nullptr) return;
    // if name is found, append vector
    if(name == node->name) specifiedNameIDs.push_back(node->ufid);
    // we want to traverse through the whole tree to find any duplicates
    searchNAMEHelper(node->left, name,specifiedNameIDs);
    searchNAMEHelper(node->right, name, specifiedNameIDs);
}

Node* AVLTree::removeIDHelper(Node* node, string ufid) {
    // bool makes more sense to me here
    bool found = false;
    // if empty, return
    if (node == nullptr) {
        cout << "unsuccessful" << endl;
        return node;
    }
    // the node is in right subtree
    if (ufid > node->ufid) node->right = removeIDHelper(node->right, ufid);
        // the node is in left subtree
    else if (ufid < node->ufid) node->left = removeIDHelper(node->left, ufid);
    // node to be deleted
    else {
        found = true;
        // if node has no children
//        if (node->left == nullptr && node->right == nullptr) {
//            delete node;
//            node = nullptr;
//            cout << "successful" << endl;
//            return node;
//        }
        // 1 child
        if (node->right == nullptr)
        {
            Node *tempNode = node->left;
            delete node;
            cout << "successful" << endl;
            return tempNode;
        }
        else if (node->left == nullptr)
        {
            Node *tempNode = node->right;
            delete node;
            cout << "successful" << endl;
            return tempNode;
        // 2 children
        }
        else
        {
            Node *tempNode = inorderSuccessor(node->right);
            node->ufid = tempNode->ufid;
            node->name = tempNode->name;
            node->right = removeIDHelper(node->right, tempNode->ufid);
        }
    }
    // update height
    if (found) node->height = getHeight(node);
    // rotate tree
    rotateTree(node);
    return node;
}


void AVLTree::removeInOrderHelper(Node* node, vector<string>& ufids)
{
    // if empty, return
    if (node == nullptr){
        //cout << "unsuccessful" << endl;
        return;
    }
    removeInOrderHelper(node->left, ufids);
    ufids.push_back(node->ufid);
    removeInOrderHelper(node->right, ufids);
}

void AVLTree::inOrderHelper(Node* node, bool& isFirst)
{
    // if empty, return
    if (node == nullptr) return;
    // print out comma after each name is printed.
    // this is so that we can eliminate the trailing comma at the end.
    inOrderHelper(node->left, isFirst);
    if(!isFirst) cout << ", ";
    cout << node->name;
    // bool to keep track of whether we are at first node
    isFirst = false;
    inOrderHelper(node->right, isFirst);
}

void AVLTree::preOrderHelper(Node* node, bool& isFirst)
{
    // if empty, return
    if (node == nullptr) return;
    // print out comma after each name is printed.
    // this is so that we can eliminate the trailing comma at the end.
    if(!isFirst) cout << ", ";
    cout << node->name;
    // bool to keep track of whether we are at first node
    isFirst = false;
    preOrderHelper(node->left, isFirst);
    preOrderHelper(node->right, isFirst);
}

void AVLTree::postOrderHelper(Node* node, bool& isFirst)
{
    // if empty, return
    if (node == nullptr) return;

    postOrderHelper(node->left, isFirst);
    postOrderHelper(node->right, isFirst);
    // print out comma after each name is printed.
    // this is so that we can eliminate the trailing comma at the end.
    if(!isFirst) cout << ", ";
    cout << node->name;
    // bool to keep track of whether we are at first node
    isFirst = false;
}


/*-----------------PUBLIC FUNC. IMPLEMENTATION -----------------*/

void AVLTree::insertNameID(string name, string ufid)
{
    this->root = insertHelper(this->root, name, ufid);
}

void AVLTree::removeID(string ufid)
{
    this->root = removeIDHelper(this->root, ufid);
}

void AVLTree::searchID(string ufid)
{
    searchIDHelper(this->root, ufid);
}

void AVLTree::searchName(string name)
{
    vector<string> specifiedNameIDs;
    searchNAMEHelper(this->root, name, specifiedNameIDs);
    // if no name is found, command exec. unsuccessful
    if (specifiedNameIDs.empty()) cout << "unsuccessful" << endl;
    else{
        // print id found
        for(string names : specifiedNameIDs)
            cout << names << endl;
    }
}

    void AVLTree::printInOrder()
{
    bool isFirst = true;
    inOrderHelper(this->root, isFirst);
}
void AVLTree::printPreOrder()
{
    bool isFirst = true;
    preOrderHelper(this->root, isFirst);
}

void AVLTree::printPostOrder()
{
    bool isFirst = true;
    postOrderHelper(this->root, isFirst);
}

void AVLTree::printLevelCount()
{
    cout << getHeight(this->root) << endl;
}

void AVLTree::removeInOrder(int n)
{
    vector<string> ufids;
    removeInOrderHelper(this->root, ufids);
    // if n is a valid node location
    if (n <= ufids.size()) removeID(ufids[n]);
    // if n is NOT a valid node location
    else cout << "unsuccessful" << endl;
}


string AVLTree::nameCheck(string name)
{
    for(char c : name)
    {
        if(!isalpha(c) && !isspace(c)) return "ERROR";
    }
    return name;
}

string AVLTree::idCheck(string ufid)
{
    if(ufid.size() != 8) return "ERROR";
    for(char c : ufid)
    {
        if (!isdigit(c)) return "ERROR";
    }
    return ufid;
}

bool AVLTree::isDigit(string n)
{
    for (char c : n) if (!isdigit(c)) return false;
    return true;

}