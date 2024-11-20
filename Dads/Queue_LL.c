#include<stdio.h>
#include<stdlib.h>
struct node
{
    int data;
    struct node *link;
}*head=NULL;
struct node *tail = NULL;

void enqueue(int x)
{
    struct node *newNode = malloc(sizeof(struct node));
    newNode->data = x;
    newNode->link = NULL;
    if(head==NULL && tail==NULL)
    {
        head = newNode; 
        tail = newNode;
    }
    else
    {
        tail->link = newNode;
        tail = newNode;
    }
}
void dequeue()
{
    struct node *ptr;
    ptr = head;
    if(head==NULL && tail==NULL)
        printf("The Queue is Empty!\n");
    else
    {
        printf("Dequeued element: %d\n", ptr->data);
        head = head->link;
        free(ptr);
        ptr = NULL;
    }
}
void display()
{
    struct node *ptr;
    if(head==NULL && tail==NULL)
        printf("Queue is empty!\n");
    else
    {
        ptr = head;
        while(ptr!=NULL)
        {
            printf("%d\t", ptr->data);
            ptr = ptr->link;
        }
        printf("\n");
    }
}
void peek()
{
    if(head==NULL && tail==NULL)
        printf("The Queue is Empty.\n");
    else
        printf("First Element is: %d\n", head->data);
}

int main()
{   
    enqueue(5);
    enqueue(0);
    enqueue(-2);
    display();
    enqueue(7);
    display();
    dequeue();
    peek();
    display();
    return 0;
}