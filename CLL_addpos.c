#include <stdio.h>
#include <stdlib.h>
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
    newNode->link = newNode;  // The first node points to itself to form a circular structure
    head = newNode;
    ptr = newNode;

    for (int i = 2; i <= n; i++) {
        newNode = malloc(sizeof(struct node));
        if (newNode == NULL) {
            printf("Unable to allocate memory\n");
            break;
        } else {
            printf("Enter the data of node %d:\n", i);
            scanf("%d", &data);
            newNode->data = data;
            newNode->link = head;  // New node points to head to maintain circularity
            ptr->link = newNode;    // Previous node links to the new node
            ptr = newNode;
        }
    }
}

// Function for inserting a node at any position in a circular linked list
void addAtPos(int pos) {
    struct node *ptr = head, *temp;
    int data;

    temp = (struct node *)malloc(sizeof(struct node));
    if (temp == NULL) {
        printf("Unable to allocate memory\n");
        return;
    }

    printf("Enter the data of the node to add at position %d:\n", pos);
    scanf("%d", &data);
    temp->data = data;

    if (pos == 1) {  // Insertion at the beginning
        while (ptr->link != head) {
            ptr = ptr->link;  // Traverse to the last node
        }
        temp->link = head;  // New node points to head
        ptr->link = temp;  // Last node points to the new node
        head = temp;  // Update head to the new node
    } else {  // Insertion at any position other than the beginning
        for (int i = 1; i < pos - 1 && ptr->link != head; i++) {
            ptr = ptr->link;  // Traverse to the node before the desired position
        }
        temp->link = ptr->link;  // New node points to the next node
        ptr->link = temp;  // Current node points to the new node
    }
}

// Function to traverse and print the circular linked list
void traverse(struct node *head) {
    if (head == NULL) {
        printf("The List is empty\n");
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
    int n, pos;
    printf("Enter the number of nodes:\n");
    scanf("%d", &n);

    createList(n);
    traverse(head);

    printf("Enter the position to insert a new node:\n");
    scanf("%d", &pos);
    addAtPos(pos);

    printf("List after adding a node at position %d:\n", pos);
    traverse(head);

    return 0;
}
