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
// Function to delete a node at a specific position in a circular linked list
void del_pos(struct node **head, int pos) {
    if (*head == NULL) {
        printf("The list is already empty\n");
        return;
    }
    struct node *current = *head;
    struct node *previous = NULL;
    if (pos == 1) {
        // Delete the head node
        if (current->link == *head) {
            // Only one node in the list
            free(*head);
            *head = NULL;
        } else {
            // More than one node
            while (current->link != *head) {
                current = current->link;
            }
            struct node *temp = *head;
            *head = (*head)->link;
            current->link = *head;
            free(temp);
        }
        return;
    }
    // Traverse to the node before the position to delete
    for (int i = 1; current != NULL && i < pos; i++) {
        previous = current;
        current = current->link;
        if (current == *head) {
            printf("Position out of bounds\n");
            return;
        }
    }
    if (current == *head) {
        printf("Position out of bounds\n");
        return;
    }
    // Delete the node
    previous->link = current->link;
    free(current);
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
    int pos;
    printf("Enter the position to delete:\n");
    scanf("%d", &pos);
    del_pos(&head, pos);
    printf("List after deleting the node at position %d:\n", pos);
    traverse(head);
    return 0;
}
