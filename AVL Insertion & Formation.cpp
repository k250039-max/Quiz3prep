#include <iostream>
using namespace std;

// Structure to represent a node in the AVL tree
struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
};

// Function to get the height of a node
int getHeight(Node* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// Function to calculate the balance factor of a node
int getBalance(Node* node) {
    if (node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// Function to create a new node
Node* createNode(int key) {
    Node* node = new Node();
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // New node is initially added as a leaf node
    return node;
}

// Function to perform a right rotation
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Perform the rotation
    x->right = y;
    y->left = T2;

    // Update the heights of the rotated nodes after rotation

    // For node x, update its height by taking the maximum height of its left and right subtrees,
    // then add 1 to account for the current node itself.
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    // For node y, do the same as for node x, calculate the maximum height of its left and right subtrees,
    // and add 1 to account for the current node itself.
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return x; // Return the new root after rotation
}

// Function to perform a left rotation
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Perform the rotation
    y->left = x;
    x->right = T2;

    // Update the heights of the rotated nodes after rotation

    // For node x, update its height by taking the maximum height of its left and right subtrees,
    // then add 1 to account for the current node itself.
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    // For node y, do the same as for node x, calculate the maximum height of its left and right subtrees,
    // and add 1 to account for the current node itself.
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y; // Return the new root after rotation
}

// Function to insert a key into the AVL tree
Node* insert(Node* root, int key) {
    if (root == NULL)
        return createNode(key);

    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    else
        return root; // Duplicate keys are not allowed

    // Update the height of the current node
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    int balance = getBalance(root);

    // Left Heavy (LL or LR)
    if (balance > 1 && key < root->left->key) {
        return rightRotate(root);
    }

    // Right Heavy (RR or RL)
    if (balance < -1 && key > root->right->key) {
        return leftRotate(root);
    }

    // Left Right Heavy (LR)
    if (balance > 1 && key > root->left->key) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Left Heavy (RL)
    if (balance < -1 && key < root->right->key) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root; // Return the updated root after insertion and rotations
}

// Function to print the AVL tree in-order
void inOrderTraversal(Node* root) {
    if (root == NULL)
        return;

    inOrderTraversal(root->left);
    cout << root->key << " ";
    inOrderTraversal(root->right);
}

int main() {
    Node* root = NULL;

    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

	cout << "In-Order Traversal of the AVL tree: ";
	inOrderTraversal(root);
	cout << endl;
	int x=getBalance(root);
	cout<<x;
cout << endl;
int y=getHeight(root);
cout<<y;
    return 0;
}
