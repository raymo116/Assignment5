#pragma once

// Contents

/*
BST();
virtual ~BST();
void insert(int key, T value);
bool contains(int key);
TreeNode<T>* getSuccessor(TreeNode<T>* d);
bool deleteR(int k);

TreeNode<T>* getMin();
TreeNode<T>* getMax();
bool isEmpty();
void printTree();
void searchPrint(int key);
void recPrint(TreeNode<T>* node);
T findKey(int key);
int elements();
int recElements(TreeNode<T>* node);

TreeNode<T>* root;
*/


#include <iostream>
#include <string>

using namespace std;

// Written in ints, should be template

template<class T>
class TreeNode
{
public:
    TreeNode();
    TreeNode(int key,T value);
    virtual ~TreeNode();
    int key;
    T value;
    TreeNode<T>* left;
    TreeNode<T>* right;
};

template<class T>
TreeNode<T>::TreeNode()
{
    left = NULL;
    right = NULL;
}

template<class T>
TreeNode<T>::TreeNode(int k, T v)
{
    left = right = NULL;
    key = k; // Key too
    value = v; // Key too
}

template<class T>
TreeNode<T>::~TreeNode()
{
    delete value;
}

template<class T>
class BST
{
public:
    BST();
    virtual ~BST();
    void insert(int  key, T value);
    bool contains(int key);
    TreeNode<T>* getSuccessor(TreeNode<T>* d);
    bool deleteR(int k);

    TreeNode<T>* getMin();
    TreeNode<T>* getMax();
    bool isEmpty();
    void printTree();

    // Print the contents of the key given the id
    void searchPrint(int key);
    // Recursive print call. Prints and then calls recPrint on its children
    void recPrint(TreeNode<T>* node);
    // Find a key and return the value
    T findKey(int key);
    // Count the elements in the tree
    int elements();
    // recursive count elements. Calls itself on its children
    int recElements(TreeNode<T>* node);

    TreeNode<T>* root;
};

template<class T>
BST<T>::BST() // default constructor
{
    root = NULL;
}

template<class T>
BST<T>::~BST()
{
    // Iterate and deleteR
    // Research how to do this
}

template<class T>
void BST<T>::printTree()
{
    recPrint(root);
}

// Recursive print call. Prints and then calls recPrint on its children
template<class T>
void BST<T>::recPrint(TreeNode<T>* node)
{
    if(node == NULL) return;

    recPrint(node->left);
    node->value->print();
    cout << endl;
    recPrint(node->right);
}

template<class T>
bool BST<T>::isEmpty()
{
    return (root == NULL);
}

// min
// max

template<class T>
void BST<T>::insert(int key, T value)
{
    TreeNode<T>* node = new TreeNode<T>(key, value);

    if(isEmpty()) root = node;
    else
    {
        TreeNode<T>* parent = root;
        TreeNode<T>* current = root;

        while(true)
        {
            parent = current;

            if(key < current->key)
            {
                current = current->left;
                if(current==NULL)
                {
                    parent->left = node;
                    break;
                }
            }
            else
            {
                current = current->right;
                if(current==NULL)
                {
                    parent->right = node;
                    break;
                }
            }
        }
    }
}

template<class T>
bool BST<T>::contains(int key)
{
    if(isEmpty()) return false;

    TreeNode<T>* current = root;
    TreeNode<T>* parent = root;

    while(current->key!=key)
    {
        parent = current;

        current = (key < current->key) ? current->left : current->right;

        if(current == NULL) return false;
    }
    return true;
}

// Print the contents of the key given the id
template<class T>
void BST<T>::searchPrint(int key)
{
    if(contains(key))
    {
        TreeNode<T>* current = root;
        TreeNode<T>* parent = root;

        while(current->key!=key)
        {
            parent = current;

            current = (key < current->key) ? current->left : current->right;
        }
        current->value->print();
    }
    else cout << "ID not found" << endl;
}

template<class T>
bool BST<T>::deleteR(int k)
{
    if(isEmpty()) return false;

    if(!contains(k))
        throw invalid_argument("The tree does not contain that key");

    TreeNode<T>* current = root;
    TreeNode<T>* parent = root;
    bool isLeft = true;

    while(current->key != k)
    {
        parent = current;

        isLeft = (k < current->key);
        current = isLeft?current->left:current->right;
    }

    // at this point we've found our node to be deleted

    // Leaf Node
    if((current->left == NULL) && (current->right == NULL))
    {
        if(current == root)
        {
            root = NULL;
        }
        else if(isLeft) parent->left = NULL;
        else parent->right = NULL;
    }

    // No right child
    else if(current->right == NULL)
    {
        if(current == root) root = current->left;
        else if(isLeft) parent->left = current->left;
        else parent->right = current->left;
    }

    // No left child
    else if(current->left == NULL)
    {
        if(current == root) root = current->right;
        else if(isLeft) parent->left = current->right;
        else parent->right = current->right;
    }

    // If there are two children
    else
    {
        // Find the successor of the note to be deleted
        TreeNode<T>* successor = getSuccessor(current);

        if(current == root) root = successor;
        else if(isLeft) parent -> left = successor;
        else parent->right = successor;

        successor->left = current->left;
    }

    // delete current;

    return true;
}

// One right, all the way left method
template<class T>
TreeNode<T>* BST<T>::getSuccessor(TreeNode<T>* d)
{
    TreeNode<T>* sp = d; // successor's parent
    TreeNode<T>* successor = d;
    TreeNode<T>* current = d->right;

    while(current!=NULL)
    {
        sp = successor;
        successor = current;
        current = current->left;
    }

    // We need to check if successor is a descendent of right child
    if(successor != d->right)
    {
        sp->left = successor->right;
        successor->right = d->right;
    }
}

// Find a key and return the value
template<class T>
T BST<T>::findKey(int k)
{
    TreeNode<T>* current = root;

    while(current!=NULL)
    {
        if(k == current->key)
            return current->value;

        current = (k>current->key)?current->right:current->left;
    }

    throw invalid_argument("There is no item with this ID in the tree");
}

// Count the elements in the tree
template<class T>
int BST<T>::elements()
{
    return recElements(root);
}

// recursive count elements. Calls itself on its children
template<class T>
int BST<T>::recElements(TreeNode<T>* node)
{
    int sum = 0;
    if(node == NULL) return sum;
    sum++;
    sum+=recElements(node->left);
    sum+=recElements(node->right);
    return sum;
}
