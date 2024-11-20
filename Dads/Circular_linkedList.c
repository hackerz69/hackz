#include<stdio.h>
#include<stdlib.h>

struct node {
    int data;
    struct node *link;
} *head;

void createList(int n) {
    struct node *newNode, *ptr;
    int data;
    for (int i = 1; i <= n; i++) {
        newNode = (struct node*)malloc(sizeof(struct node));
        if (newNode == NULL) {
            printf("Unable to allocate memory.\n");
            break;
        }

        printf("Enter the data of node %d: ", i);
        scanf("%d", &data);

        newNode->data = data;

        if (head == NULL) {
            head = newNode;  // First node becomes head
            newNode->link = head;  // Pointing to itself to form a circular link
            ptr = head;
        } else {
            ptr->link = newNode;  // Linking the previous node with the new node
            ptr = newNode;
            ptr->link = head;  // Last node points back to the head
        }
    }
}

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
    printf("Enter the number of nodes: ");
    scanf("%d", &n);
    createList(n);
    traverse(head);
    return 0;
}
