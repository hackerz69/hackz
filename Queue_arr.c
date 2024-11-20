#include<stdio.h>
#include<stdlib.h>
#define N 5
int queue[N];
int front = -1;
int back = -1;

void enqueue(int x)
{
    if(back == N-1)
        printf("Overflow! Cannot insert element: %d\n", x);
    else if(front==-1 && back==-1)
    {
        front = 0; back = 0;
        queue[back] = x;
    }
    else
    {
        back++;
        queue[back] = x;
    }
}
void dequeue()
{
    if(front==-1 && back==-1)
        printf("Underflow!\n");
    else if(front == back)
    {
        front = -1; back = -1;
    }
    else
    {
        printf("Dequeued element: %d\n", queue[front]);
        front++;
    }
}
void peek()
{
    if(front==-1 && back==-1)
        printf("Queue is Empty.\n");
    else
        printf("%d\n", queue[front]);
}
void display()
{
    if(front==-1 && back==-1)
        printf("Queue is empty!\n");
    else
    {
        for(int i=front; i<=back; i++)
            printf("%d\t", queue[i]);
        printf("\n");
    }
}
int main()
{
    display();
    enqueue(2);
    enqueue(5);
    enqueue(3);
    display();
    dequeue();
    display();
    enqueue(9);
    enqueue(7);
    enqueue(8);
    display();
    return 0;
}