#include<stdio.h>
#include<stdlib.h>

struct node {
    int data;
    struct node *link;
} *head = NULL;

// Function to create a circular linked list
void createList(int n) {
    struct node *newNode, *ptr;
    int data;

    if (n <= 0) {
        printf("Invalid number of nodes.\n");
        return;
    }

    newNode = malloc(sizeof(struct node));
    if (newNode == NULL) {
        printf("Unable to allocate memory\n");
        return;
    }

    printf("Enter the data of node 1:\n");
    scanf("%d", &data);
    newNode->data = data;
    newNode->link = newNode;  // Circular link
    head = newNode;
    ptr = newNode;

    for (int i = 2; i <= n; i++) {
        newNode = malloc(sizeof(struct node));
        if (newNode == NULL) {
            printf("Unable to allocate memory\n");
            break;
        }

        printf("Enter the data of node %d: \n", i);
        scanf("%d", &data);
        newNode->data = data;
        newNode->link = head;  // Link to head to maintain circularity
        ptr->link = newNode;
        ptr = newNode;
    }
}

// Function for inserting a node at the start of a circular linked list
struct node *addAtStart(struct node *head) {
    int data;
    printf("Enter the data of the node to add at start:\n");
    scanf("%d", &data);

    struct node *ptr = malloc(sizeof(struct node));
    if (ptr == NULL) {
        printf("Unable to allocate memory\n");
        return head;
    }

    ptr->data = data;
    ptr->link = head;

    if (head == NULL) {
        ptr->link = ptr;  // If the list was empty, point to itself
        head = ptr;
    } else {
        struct node *temp = head;
        while (temp->link != head) {
            temp = temp->link;
        }
        temp->link = ptr;
        head = ptr;
    }

    return head;
}

// Function to traverse and print the circular linked list
void traverse(struct node *head) {
    if (head == NULL) {
        printf("The list is empty.\n");
        return;
    }

    struct node *ptr = head;
    do {
        printf("%d\t", ptr->data);
        ptr = ptr->link;
    } while (ptr != head);
    printf("\n");
}

int main() {
    int n;
    printf("Enter the number of nodes:\n");
    scanf("%d", &n);

    createList(n);
    traverse(head);

    head = addAtStart(head);
    printf("Circular linked list after adding a node at start:\n");
    traverse(head);

    return 0;
}
