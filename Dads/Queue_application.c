#include <stdio.h>
#include <stdlib.h>
#define MAX_ORDERS 100

struct Queue {
    int orderNumbers[MAX_ORDERS];
    int front;
    int rear;
};

void initializeQueue(struct Queue *q) {
    q->front = -1;
    q->rear = -1;
}
int isFull(struct Queue *q) {
    return (q->rear == MAX_ORDERS - 1);
}
int isEmpty(struct Queue *q) {
    return (q->front == -1);
}
void enqueue(struct Queue *q, int orderNumber) {
    if (isFull(q)) {
        printf("Kitchen is busy. Please wait for your order.\n");
        return;
    }
    if (isEmpty(q)) {
        q->front = 0;
    }
    q->rear++;
    q->orderNumbers[q->rear] = orderNumber;
    printf("Order %d added to the queue.\n", orderNumber);
}
int dequeue(struct Queue *q) {
    if (isEmpty(q)) {
        printf("No pending orders.\n");
        return -1;
    }
    int orderNumber = q->orderNumbers[q->front];
    if (q->front == q->rear) {
        q->front = -1;
        q->rear = -1;
    } else {
        q->front++;
    }
    printf("Order %d is ready!\n", orderNumber);
    return orderNumber;
}

void display(struct Queue *q) {
    if (isEmpty(q)) {
        printf("No guests in the hotel.\n");
    } else {
        printf("Current guests in the hotel:\n");
        for (int i = q->front; i <= q->rear; i++) {
            printf("Order %d\n", q->orderNumbers[i]);
        }
    }
}

int main() {
    struct Queue kitchen;
    initializeQueue(&kitchen);

    int choice, orderNumber;

    while (1) {
        printf("\nHotel Orders Queue Menu:\n");
        printf("1. Place a new order\n");
        printf("2. Serve the next order\n");
        printf("3. Display pending orders\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter order number: ");
                scanf("%d", &orderNumber);
                enqueue(&kitchen, orderNumber);
                break;
            case 2:
                dequeue(&kitchen);
                break;
            case 3:
                display(&kitchen);
                break;
            case 4:
                printf("Exiting. Bon appétit!\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
