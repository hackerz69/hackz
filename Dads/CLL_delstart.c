#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *link;
} *head = NULL;

// Function to create a circular linked list
void createList(int n) {
    if (n <= 0) {
        printf("Invalid number of nodes.\n");
        return;
    }

    struct node *newNode, *ptr;
    int data;

    // Create the first node
    newNode = malloc(sizeof(struct node));
    if (newNode == NULL) {
        printf("Unable to allocate memory\n");
        return;
    }
    printf("Enter the data of node 1:\n");
    scanf("%d", &data);
    newNode->data = data;
    newNode->link = newNode;  // First node points to itself
    head = newNode;
    ptr = newNode;

    // Create the remaining nodes
    for (int i = 2; i <= n; i++) {
        newNode = malloc(sizeof(struct node));
        if (newNode == NULL) {
            printf("Unable to allocate memory\n");
            return;
        }
        printf("Enter the data of node %d:\n", i);
        scanf("%d", &data);
        newNode->data = data;
        newNode->link = head;  // New node will point to head
        ptr->link = newNode;   // Previous node will point to the new node
        ptr = newNode;
    }
    // Make the last node point to the head to complete the circular link
    ptr->link = head;
}

// Function to delete a node at the start of a circular linked list
struct node* del_start(struct node *head) {
    if (head == NULL) {
        printf("The list is already empty\n");
        return NULL;
    }

    if (head->link == head) {
        // Only one node in the list
        free(head);
        return NULL;
    }

    struct node *temp = head;
    struct node *ptr = head;
    
    // Traverse to the last node
    while (ptr->link != head) {
        ptr = ptr->link;
    }
    
    // Update the last node's link to the new head
    ptr->link = head->link;
    head = head->link;  // Update head to the next node
    free(temp);
    return head;
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
    int n;
    printf("Enter the number of nodes:\n");
    scanf("%d", &n);

    createList(n);
    printf("Original List:\n");
    traverse(head);

    head = del_start(head);
    printf("List after deleting the node at start:\n");
    traverse(head);

    return 0;
}
