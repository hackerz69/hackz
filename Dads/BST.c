#include<stdio.h>
#include<stdlib.h>

struct node
{
    int data;
    struct node *left, *right;
};

// Function to create a new node
struct node *createNode(int data)
{
    struct node *newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a new node in the BST
struct node* insertNode(struct node* root, int data)
{
    if (root == NULL) // If the tree is empty, create a new node
        return createNode(data);

    // Otherwise, recur down the tree
    if (data < root->data)
        root->left = insertNode(root->left, data);
    else if (data > root->data)
        root->right = insertNode(root->right, data);

    return root;
}
// Function to find the minimum value node in a subtree
struct node* findMin(struct node* root)
{
    while (root->left != NULL)
        root = root->left;
    return root;
}

// Function to delete a node from the BST
struct node* deleteNode(struct node* root, int key)
{
    if (root == NULL)
        return NULL;

    // Traverse the tree to find the node to be deleted
    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else {
        // Node found, handle its deletion
        if (root->left == NULL) {
            struct node *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct node *temp = root->left;
            free(root);
            return temp;
        }

        // Node with two children: Get the inorder successor (smallest in the right subtree)
        struct node *temp = findMin(root->right);

        // Copy the inorder successor's data to this node
        root->data = temp->data;

        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Function for preorder traversal
void preorder(struct node *root)
{
    if (root == NULL)
        return;
    printf("%d\t", root->data);
    preorder(root->left);
    preorder(root->right);
}

// Function for inorder traversal
void inorder(struct node *root)
{
    if (root == NULL)
        return;
    inorder(root->left);
    printf("%d\t", root->data);
    inorder(root->right);
}

// Function for postorder traversal
void postorder(struct node *root)
{
    if (root == NULL)
        return;
    postorder(root->left);
    postorder(root->right);
    printf("%d\t", root->data);
}

// Main function with menu-driven interface
int main()
{
    struct node *root = NULL;
    int choice, value;
    do {
        printf("1. Insert Node\n");
        printf("2. Preorder Traversal\n");
        printf("3. Inorder Traversal\n");
        printf("4. Postorder Traversal\n");
        printf("5. Delete a Node\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch(choice)
        {
            case 1:
                printf("Enter the value to insert: ");
                scanf("%d", &value);
                root = insertNode(root, value);
                printf("Node inserted.\n");
                break;
            case 2:
                if (root == NULL)
                    printf("Tree is empty.\n");
                else {
                    printf("Preorder traversal: ");
                    preorder(root);
                    printf("\n");
                }
                break;
            case 3:
                if (root == NULL)
                    printf("Tree is empty.\n");
                else {
                    printf("Inorder traversal: ");
                    inorder(root);
                    printf("\n");
                }
                break;
            case 4:
                if (root == NULL)
                    printf("Tree is empty.\n");
                else {
                    printf("Postorder traversal: ");
                    postorder(root);
                    printf("\n");
                }
                break;
            case 5:
                printf("Enter the value to delete: ");
                scanf("%d", &value);
                root = deleteNode(root, value);
                printf("Node deleted (if found).\n");
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 6);
    return 0;
}

