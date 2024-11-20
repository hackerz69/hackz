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

    newNode = (struct node*)malloc(sizeof(struct node));
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
        newNode = (struct node*)malloc(sizeof(struct node));
        if (newNode == NULL) {
            printf("Unable to allocate memory\n");
            break;
        } else {
            printf("Enter the data of node %d:\n", i);
            scanf("%d", &data);
            newNode->data = data;
            newNode->link = head;  // Link the new node to head to maintain circularity
            ptr->link = newNode;    // Link the previous node to the new node
            ptr = newNode;
        }
    }
}

// Function to add a node at the end of a circular linked list
void addEnd(struct node *head) {
    struct node *temp, *ptr;
    int data;

    temp = (struct node*)malloc(sizeof(struct node));
    if (temp == NULL) {
        printf("Unable to allocate memory\n");
        return;
    }

    printf("Enter the data of the node to add at the end:\n");
    scanf("%d", &data);
    temp->data = data;
    temp->link = head;  // New node points to head to maintain circularity

    ptr = head;
    while (ptr->link != head) {  // Traverse to the last node
        ptr = ptr->link;
    }
    ptr->link = temp;  // Last node points to the new node
}

// Function to traverse and print the circular linked list
void traverse(struct node *head) {
    if (head == NULL) {
        printf("The list is empty\n");
        return;
    }

    struct node *ptr = head;
    do {
        printf("%d\t", ptr->data);
        ptr = ptr->link;
    } while (ptr != head);  // Continue until we return to head
    printf("\n");
}

int main() {
    int n;
    printf("Enter the number of nodes:\n");
    scanf("%d", &n);

    createList(n);
    traverse(head);

    addEnd(head);
    printf("List after adding a node at the end:\n");
    traverse(head);

    return 0;
}
