#include<stdio.h>
#include<stdlib.h>

struct node {
    int data;
    struct node *link;
} *head = NULL;

// Function to delete the last node of a circular linked list
struct node *del_end(struct node *head) {
    if (head == NULL) {
        printf("List is already empty\n");
    } else if (head->link == head) {
        free(head);
        head = NULL;
    } else {
        struct node *temp = head, *temp2 = NULL;
        while (temp->link != head) {
            temp2 = temp;
            temp = temp->link;
        }
        temp2->link = head;  // Link the second last node to head
        free(temp);
        temp = NULL;
    }
    return head;
}

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

    printf("Enter the data of node 1: ");
    scanf("%d", &data);
    newNode->data = data;
    newNode->link = newNode;  // Point to itself (circular)
    head = newNode;
    ptr = newNode;

    for (int i = 2; i <= n; i++) {
        newNode = (struct node*)malloc(sizeof(struct node));
        if (newNode == NULL) {
            printf("Unable to allocate memory\n");
            break;
        } else {
            printf("Enter the data of node %d: ", i);
            scanf("%d", &data);
            newNode->data = data;
            newNode->link = head;  // Link the new node to the head
            ptr->link = newNode;
            ptr = newNode;
        }
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
    int n;
    printf("Enter the number of nodes: \n");
    scanf("%d", &n);

    createList(n);
    traverse(head);

    head = del_end(head);
    printf("List after deleting the node from end:\n");
    traverse(head);

    return 0;
}
