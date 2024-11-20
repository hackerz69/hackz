#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
}*root = NULL;

// Function to create a new node and recursively create its children
struct Node* create() {
    int x;
    struct Node* newNode = malloc(sizeof(struct Node));  // Allocate memory for new node
    if (newNode == NULL) {  // Check if malloc was successful
        printf("Memory allocation failed\n");
        exit(1);
    }
    // Get data for the current node
    printf("Enter data of the node (-1 for no node): ");
    scanf("%d", &x);
    if (x == -1) {
        free(newNode);  // Free memory if no node is created
        return NULL;    // Return NULL for no node
    }
    newNode->data = x;  // Set data for the node
    // Recursively create left and right children
    printf("Enter left child of %d\n", x);
    newNode->left = create();  // Recursive call for left child
    printf("Enter right child of %d\n", x);
    newNode->right = create();  // Recursive call for right child
    return newNode;
}

// Function to mirror the binary tree
void mirror(struct Node* node) {
    if (root == NULL) {
        printf("Tree is empty.\n");
        return;
    }
    // Swap left and right children
    struct Node* temp = node->left;
    node->left = node->right;
    node->right = temp;
    // Recursively call mirror on left and right subtrees
    mirror(node->left);
    mirror(node->right);
}

// Function to calculate the height of the tree
int height(struct Node *node) {
    if (root == NULL) {
        printf("Tree is empty.\n");
        return 0;
    }
    int leftHeight = height(node->left);
    int rightHeight = height(node->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

// Function to display the leaf nodes
void displayLeafNodes(struct Node* node) {
   if (root == NULL) {
        printf("Tree is empty.\n");
        return;
    }
    if (node->left == NULL && node->right == NULL) {
        printf("%d ", node->data);
        return;
    }
    displayLeafNodes(node->left);
    displayLeafNodes(node->right);
}

// Function to display the tree level-wise
void displayLevel(struct Node* root) {
   if (root == NULL) {
        printf("Tree is empty.\n");
        return;
    }
    struct Node* queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;
    while (front < rear) {
        struct Node* current = queue[front++];
        printf("%d ", current->data);

        if (current->left != NULL) {
            queue[rear++] = current->left;
        }
        if (current->right != NULL) {
            queue[rear++] = current->right;
        }
    }
}

int main() {
    struct Node* root = NULL;  
    int choice;
    while (1) {
        printf("1. Create Tree\n");
        printf("2. Mirror Tree\n");
        printf("3. Height of Tree\n");
        printf("4. Display Leaf Nodes\n");
        printf("5. Level-wise Display\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                root = create();
                printf("Tree created successfully.\n");
                break;
            case 2:
                mirror(root);
                printf("Tree has been mirrored.\n");
                break;
            case 3:
                printf("Height of tree: %d\n", height(root));
                break;
            case 4:
                printf("Leaf nodes: ");
                displayLeafNodes(root);
                printf("\n");
                break;
            case 5:
                printf("Level-wise display: ");
                displayLevel(root);
                printf("\n");
                break;
            case 6:
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    }
    return 0;
}
