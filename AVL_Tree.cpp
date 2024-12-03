#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

// Template class representing a node in the AVL tree
template <typename T>
class AVLNode {
public:
    T val;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(T k) : val(k), left(nullptr), right(nullptr), height(1) {}
};

// Template class representing the AVL tree
template <typename T>
class AVLTree {
private:
    AVLNode<T>* root;

    int height(AVLNode<T>* node) {
        if (node == nullptr)
            return 0;
        return node->height;
    }

    int balanceFactor(AVLNode<T>* node) {
        if (node == nullptr)
            return 0;
        return height(node->left) - height(node->right);
    }

    AVLNode<T>* rightRotate(AVLNode<T>* b) {
        AVLNode<T>* a = b->left;
        AVLNode<T>* a_tail = a->right;

        a->right = b;
        b->left = a_tail;

        b->height = max(height(b->left), height(b->right)) + 1;
        a->height = max(height(a->left), height(a->right)) + 1;

        return a;
    }

    AVLNode<T>* leftRotate(AVLNode<T>* a) {
        AVLNode<T>* b = a->right;
        AVLNode<T>* b_tail = b->left;

        b->left = a;
        a->right = b_tail;

        a->height = max(height(a->left), height(a->right)) + 1;
        b->height = max(height(b->left), height(b->right)) + 1;

        return b;
    }

    AVLNode<T>* insert(AVLNode<T>* node, T val) {
        if (node == nullptr)
            return new AVLNode<T>(val);

        if (val < node->val)
            node->left = insert(node->left, val);
        else if (val > node->val)
            node->right = insert(node->right, val);
        else
            return node;

        node->height = 1 + max(height(node->left), height(node->right));

        int balance = balanceFactor(node);

        if (balance > 1 && val < node->left->val)
            return rightRotate(node);

        if (balance < -1 && val > node->right->val)
            return leftRotate(node);

        if (balance > 1 && val > node->left->val) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && val < node->right->val) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(T val) { root = insert(root, val); }

    AVLNode<T>* getRoot() { return root; }
};

// Function to get the height of the AVL tree
template <typename T>
int getAVLTreeHeight(AVLNode<T>* root) {
    if (root == nullptr)
        return 0;
    return root->height;
}

int main() {
    AVLTree<int> avlTree;
    int max_keys = 100;
    vector<int> heights;

    for (int i = 1; i <= max_keys; ++i) {
        avlTree.insert(i);
        heights.push_back(getAVLTreeHeight(avlTree.getRoot()));
    }

    // Save heights to a file
    ofstream outFile("avl_heights.txt");
    for (int height : heights) {
        outFile << height << endl;
    }
    outFile.close();

    return 0;
}