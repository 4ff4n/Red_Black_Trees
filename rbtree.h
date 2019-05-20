#include <iostream>
#include <string>

#include "contact.h"

using namespace std;

enum  {BLACK = false, RED = true};

struct TreeNode
{
    Contact item;

    TreeNode *left;
    TreeNode *right;

    bool color;
    

    TreeNode() {}
    TreeNode(const Contact & c, TreeNode *l, TreeNode *r, bool col = RED)
            : item(c), left(l), right(r), color(col) {}

    ~TreeNode() {
        delete left;
        delete right;
    }
};

class Tree
{
private:
    TreeNode *root;

    bool addItem(Contact & item, TreeNode * & tRoot);
    bool deleteItem(Contact & item, TreeNode * & tRoot);
    TreeNode * findItem(Contact & item, TreeNode * & tRoot);
    TreeNode * minimum(TreeNode *tRoot);
    TreeNode * maximum(TreeNode *tRoot);

    int getColor(TreeNode *tRoot)
    {
        return tRoot->color;
    }

    bool isRed(TreeNode *tRoot)
    {
        if (tRoot == nullptr) return false;

        return tRoot->color == RED;
    }

    bool isBlack(TreeNode *tRoot)
    {
        if (tRoot == nullptr) return false;

        return tRoot->color == BLACK;
    }

    void flipColors(TreeNode *tRoot)
    {
        tRoot->color = !tRoot->color;
        tRoot->left->color = !tRoot->left->color;
        tRoot->right->color = !tRoot->right->color;
    }

    void performRotations(TreeNode * & tRoot);
    void rotateWithLeft(TreeNode * & tRoot);
    void moveRedWithLeft(TreeNode * & tRoot);
    void rotateWithRight(TreeNode * & tRoot);
    void moveRedWithRight(TreeNode * & tRoot);
    void fixUp(TreeNode * & tRoot);
    void deleteMax(TreeNode * & tRoot);
    void deleteMin(TreeNode * & tRoot);
	
	// inorder print of the tree
    
	void printTree(TreeNode *tRoot)
    {
        if (tRoot == nullptr) {
            return;
        }

        printTree(tRoot->left);

        cout << endl << "-------------------------" << endl;
        cout << endl << "Node color is: " << ((tRoot->color) ? "Red" : "Black") << endl;
        tRoot->item.printContact();

        printTree(tRoot->right);
    }

public:
    Tree() {
        root = nullptr;
    }

    ~Tree() {
        //this will recursively call the
        //child destructors.
        delete root;
    }

    bool addItem(Contact & item)
    {
        bool result = false;
        result = addItem(item, root);

        root->color = BLACK;

        return result;
    }

    bool deleteItem(Contact & item)
    {
        bool result = false;

        result = deleteItem(item, root);

        root->color = BLACK;

        return result;
    }

    TreeNode * findItem(Contact & item)
    {
        return findItem(item, root);
    }

    void printTree()
    {
        printTree(root);
    }

    bool isEmpty()
    {
        return root == nullptr;
    }
};

TreeNode * Tree::minimum(TreeNode *tRoot)
{
if (tRoot == nullptr) {
        return nullptr;
    }

    if (tRoot->left == nullptr) {
        return tRoot;
    }

    return minimum(tRoot->left);
}

TreeNode * Tree::maximum(TreeNode *tRoot)
{
    if (tRoot == nullptr) {
        return nullptr;
    }

    if (tRoot->right == nullptr) {
        return tRoot;
    }

    return maximum(tRoot->right);
}

bool Tree::addItem(Contact & item, TreeNode * & tRoot)
{
    if (tRoot == nullptr) {
        tRoot = new TreeNode(item, nullptr, nullptr);
        return true;
    }

    if (isRed(tRoot->left) && isRed(tRoot->right)) {
        flipColors(tRoot);
    }

    if (tRoot->item > item) {
        addItem(item, tRoot->left);
    }
    else if (tRoot->item < item) {
        addItem(item, tRoot->right);
    } else if (tRoot->item == item) {
        return false;
    } else{}

    performRotations(tRoot);

    return true;
}

TreeNode * Tree::findItem(Contact & item, TreeNode * & tRoot)
{
    if (tRoot == nullptr) {
        return nullptr;
    }

    if (tRoot->item > item) {
        findItem(item, tRoot->left);
    }

    else if (tRoot->item < item) {
        findItem(item, tRoot->right);
    } else return tRoot;
}

bool Tree::deleteItem(Contact & item, TreeNode * & tRoot)
{

   if (tRoot == nullptr) {
        return false;
   }

   // if (tRoot->item > item) {
   //      deleteItem(item, tRoot->left);
   // } else if (tRoot->item < item) {
   //      deleteItem(item, tRoot->right);
   // } else if (tRoot->left != nullptr && tRoot->right !=nullptr) {
   //      tRoot->item = minimum(tRoot->right)->item;
   //      deleteItem(tRoot->item, tRoot->right);
   // } else {
   //      TreeNode *temp = tRoot;
   //      tRoot = (tRoot->left != nullptr) ? tRoot->left : tRoot->right;
   //      delete temp;
   // }

   if (tRoot->item > item) {

        if (!isRed(tRoot->left) && !isRed(tRoot->left->left)) {

            moveRedWithRight(tRoot);
        }

        deleteItem(item, tRoot->left);
    } else {
        if (isRed(tRoot->left)) {
            rotateWithLeft(tRoot);
        }

        if ((tRoot->item == item) && (tRoot->right == nullptr)) {
            return false; 
        }

        if (!isRed(tRoot->right) && !isRed(tRoot->right->left)) {
            moveRedWithLeft(tRoot);
        }

        if (tRoot->item == item) {
            tRoot->item = minimum(tRoot->right)->item;
            deleteMin(tRoot->right);

        } else {
            deleteItem(item, tRoot->right);
        }
    } //main else

    fixUp(tRoot); 
    return true;
}

void Tree::performRotations(TreeNode * & tRoot)
{
    cout << endl << "-------------------------" << endl;
    cout << "Performing Rotations ..." << endl;
    if (tRoot == nullptr) {
        return;
    }

    if (isRed(tRoot->right)) {
        rotateWithRight(tRoot);
    }

    if (isRed(tRoot->left) && isRed(tRoot->left->left)) {
        rotateWithLeft(tRoot);
    }

    cout << "Done ...." << endl;
    cout << endl << "-------------------------" << endl;
}

void Tree::rotateWithLeft(TreeNode * & stRoot)
{
    TreeNode *newRoot = stRoot->left;
    stRoot->left = newRoot->right;
    newRoot->right = stRoot; 

    newRoot->color = newRoot->right->color;
    newRoot->right->color = RED;

    stRoot = newRoot;
}

void Tree::moveRedWithLeft(TreeNode * & stRoot)
{
    flipColors(stRoot);

    if(isRed(stRoot->left->left)) {
        rotateWithLeft(stRoot);
    }

    flipColors(stRoot);
}

void Tree::rotateWithRight(TreeNode * & stRoot)
{
   TreeNode *newRoot = stRoot->right;
   stRoot->right = newRoot->left;
   newRoot->left = stRoot; 

   newRoot->color = newRoot->left->color;
   newRoot->left->color = RED;

   stRoot = newRoot;
}

void Tree::moveRedWithRight(TreeNode * & stRoot)
{
    flipColors(stRoot);

    if (isRed(stRoot->right->left)) {
        rotateWithLeft(stRoot->right);
        rotateWithRight(stRoot);
    }

    flipColors(stRoot);
}

void Tree::fixUp(TreeNode * & stRoot)
{
    if (isRed(stRoot->right)) {
      rotateWithRight(stRoot);
    }

   if (isRed(stRoot->left) && isRed(stRoot->left->left)) {
       rotateWithLeft(stRoot);
   }

   if (isRed(stRoot->left) && isRed(stRoot->right)) {
      flipColors(stRoot);
   }
}


void Tree::deleteMax(TreeNode * & stRoot) {
   if (isRed(stRoot->left)) {
        rotateWithLeft(stRoot);
   }

    if(stRoot == nullptr) {
        return;
    }

   if (!isRed(stRoot->right) && !isRed(stRoot->right->left)) {
        moveRedWithLeft(stRoot);
   }

    deleteMax(stRoot->right);

    fixUp(stRoot);
}

void Tree::deleteMin(TreeNode * & stRoot) {
    if (stRoot->left == nullptr) {
        return;
    }

    if (!isRed(stRoot->left) && !isRed(stRoot->left->left)) {
        moveRedWithRight(stRoot);
    }

    deleteMin(stRoot->left);

    fixUp(stRoot); 
} 
