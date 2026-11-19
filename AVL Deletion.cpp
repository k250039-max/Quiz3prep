#include <iostream>
using namespace std;

// Define the structure for an AVL tree node
struct AVLNode {
    int key;
    AVLNode* left;
    AVLNode* right;
    int height;
    AVLNode(int k) : key(k), left(NULL), right(NULL), height(1) {}
};

// Function to get the height of a node (handles NULL nodes)
int getHeight(AVLNode* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// Function to update the height of a node
void updateHeight(AVLNode* node) {
    if (node != NULL) {
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    }
}

// Function to perform a right rotation (RR case)
AVLNode* rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

// Function to perform a left rotation (LL case)
AVLNode* leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

// Function to delete a node with a given key from the AVL tree
AVLNode* deleteNode(AVLNode* root, int key) {
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        // Node with one child or no child
        if (root->left == NULL) {
            AVLNode* temp = root->right;
            delete root;
            root = temp;
        } else if (root->right == NULL) {
            AVLNode* temp = root->left;
            delete root;
            root = temp;
        } else {
            // Node with two children, find the in-order successor
            AVLNode* temp = root->right;
            while (temp->left != NULL)
                temp = temp->left;
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (root == NULL)
        return root;

    // Update the height of the current node
    updateHeight(root);

    // Check the balance factor
    int balance = getHeight(root->left) - getHeight(root->right);

    // Perform rotations to rebalance the tree
    if (balance > 1) {
        if (key < root->left->key) // LL case
            return rightRotate(root);
        else { // LR case
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    }
    if (balance < -1) {
        if (key > root->right->key) // RR case
            return leftRotate(root);
        else { // RL case
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }

    return root;
}

// Function to perform an in-order traversal
void inOrderTraversal(AVLNode* root) {
    if (root == NULL)
        return;
    inOrderTraversal(root->left);
    cout << root->key << " ";
    inOrderTraversal(root->right);
}

int main() {
    AVLNode* root = new AVLNode(50);
    root->left = new AVLNode(30);
    root->right = new AVLNode(70);
    root->left->left = new AVLNode(20);
    root->left->right = new AVLNode(40);

    cout << "In-order traversal before deletion: ";
    inOrderTraversal(root);
    cout << endl;

    int keyToDelete = 30;
    root = deleteNode(root, keyToDelete);

    cout << "In-order traversal after deleting " << keyToDelete << ": ";
    inOrderTraversal(root);
    cout << endl;

    return 0;
}