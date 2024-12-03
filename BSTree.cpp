#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Node structure for a Binary Search Tree
struct Node {
    int val;
    Node* left;
    Node* right;
};

// Function to create a new Node
Node* createNode(int val) {
    Node* newNode = new Node();
    newNode->val = val;
    newNode->left = newNode->right = nullptr;
    return newNode;
}

// Function to insert a node in the BST
Node* insertNode(Node* root, int val) {
    if (root == nullptr) {
        return createNode(val);
    }
    if (val < root->val) {
        root->left = insertNode(root->left, val);
    }
    else if (val > root->val) {
        root->right = insertNode(root->right, val);
    }
    return root;
}

// Function to calculate the height of the BST
int height(Node* root) {
    if (root == nullptr) {
        return 0;
    }
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return max(leftHeight, rightHeight) + 1;
}

int main() {
    srand(time(0));
    ofstream outFile("bst_heights.txt");

    for (int n = 1; n <= 1000; n += 10) {
        Node* root = nullptr;
        for (int i = 0; i < n; ++i) {
            int val = rand() % 1000; // Random value between 0 and 999
            root = insertNode(root, val);
        }
        int h = height(root);
        outFile << n << " " << h << endl;
    }

    outFile.close();
    return 0;
}