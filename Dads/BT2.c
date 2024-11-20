#include <stdio.h>
#include <stdlib.h>

// Structure for a node in the binary tree
struct node {
    int data;
    struct node* left;
    struct node* right;
};

// Stack structure
struct Stack {
    int top;
    int capacity;
    struct node** array;
};

// Function to create a new node
struct node* createNode(int data) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a new node in the BST
struct node* insertNode(struct node* root, int data) {
    if (root == NULL) // If the tree is empty, create a new node
        return createNode(data);

    // Otherwise, recur down the tree
    if (data < root->data)
        root->left = insertNode(root->left, data);
    else if (data > root->data)
        root->right = insertNode(root->right, data);

    return root;
}

// Stack Operations
struct Stack* createStack(int capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (struct node**)malloc(stack->capacity * sizeof(struct node*));
    return stack;
}

int isFull(struct Stack* stack) {
    return stack->top == stack->capacity - 1;
}

int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

void push(struct Stack* stack, struct node* node) {
    if (!isFull(stack))
        stack->array[++stack->top] = node;
}

struct node* pop(struct Stack* stack) {
    if (!isEmpty(stack))
        return stack->array[stack->top--];
    return NULL;
}

struct node* peek(struct Stack* stack) {
    if (!isEmpty(stack))
        return stack->array[stack->top];
    return NULL;
}

// Iterative Preorder Traversal using Stack
void iterativePreorder(struct node* root) {
    if (root == NULL) {
        printf("Tree is empty.\n");
        return;
    }

    struct Stack* stack = createStack(100);
    push(stack, root);

    while (!isEmpty(stack)) {
        struct node* current = pop(stack);
        printf("%d\t", current->data);

        if (current->right)
            push(stack, current->right);
        if (current->left)
            push(stack, current->left);
    }
    free(stack);
}

// Iterative Inorder Traversal using Stack
void iterativeInorder(struct node* root) {
    if (root == NULL) {
        printf("Tree is empty.\n");
        return;
    }
    struct Stack* stack = createStack(100);
    struct node* current = root;

    while (current != NULL || !isEmpty(stack)) {
        while (current != NULL) {
            push(stack, current);
            current = current->left;
        }
        current = pop(stack);
        printf("%d\t", current->data);
        current = current->right;
    }
    free(stack);
}

// Iterative Postorder Traversal using Two Stacks
void iterativePostorder(struct node* root) {
    if (root == NULL) {
        printf("Tree is empty.\n");
        return;
    }

    struct Stack* stack1 = createStack(100);
    struct Stack* stack2 = createStack(100);

    push(stack1, root);
    while (!isEmpty(stack1)) {
        struct node* current = pop(stack1);
        push(stack2, current);

        if (current->left)
            push(stack1, current->left);
        if (current->right)
            push(stack1, current->right);
    }

    while (!isEmpty(stack2)) {
        struct node* current = pop(stack2);
        printf("%d\t", current->data);
    }
    free(stack1);
    free(stack2);
}

// Function to find the minimum value node in a subtree
struct node* findMin(struct node* root) {
    while (root->left != NULL)
        root = root->left;
    return root;
}

// Function to delete a node from the BST
struct node* deleteNode(struct node* root, int key) {
    if (root == NULL)
        return NULL;

    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL) {
            struct node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct node* temp = root->left;
            free(root);
            return temp;
        }

        struct node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Main function with menu-driven interface
int main() {
    struct node* root = NULL;
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
        switch (choice) {
            case 1:
                printf("Enter the value to insert: ");
                scanf("%d", &value);
                root = insertNode(root, value);
                printf("Node inserted.\n");
                break;
            case 2:
                printf("Preorder traversal: ");
                iterativePreorder(root);
                printf("\n");
                break;
            case 3:
                printf("Inorder traversal: ");
                iterativeInorder(root);
                printf("\n");
                break;
            case 4:
                printf("Postorder traversal: ");
                iterativePostorder(root);
                printf("\n");
                break;
            case 5:
                if (root == NULL) {
                    printf("Tree is empty. No nodes to delete.\n");
                } else {
                    printf("Enter the value to delete: ");
                    scanf("%d", &value);
                    root = deleteNode(root, value);
                    printf("Node deleted (if found).\n");
                }
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 6);
    return 0;
}
