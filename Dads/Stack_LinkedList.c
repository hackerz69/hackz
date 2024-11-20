#include <stdio.h>
#include<stdlib.h>
struct node
{
    int data;
    struct node *link;
}*top = NULL;

int isEmpty()
{
    if(top == NULL)
        return 1;
    else
        return 0;
}
void push(int data)
{
    struct node *newNode = malloc(sizeof(struct node));
    if(newNode == NULL)
    {
        printf("Stack Overflow.\n");
        exit(1);
    }
    newNode->data = data;
    newNode->link = NULL;
    newNode->link = top;
    top = newNode;
}
int pop()
{
    struct node *temp;
    temp = top;
    if(isEmpty())
    {
        printf("Stack Underflow.\n");
        exit(1);
    }
    int val = temp->data;
    top = top->link;
    free(temp);
    temp = NULL;
    return val;
}
void print()
{   
    struct node *temp;
    temp = top;
    if(isEmpty())
    {
        printf("Stack Underflow.\n");
        exit(1);
    }
    printf("The elements in the stack are:\n");
    while(temp)
    {
        printf("%d\n", temp->data);
        temp = temp->link;
    }
}
int peek()
{
    if(isEmpty())
    {
        printf("Stack Underflow.\n");
        exit(1);
    }
    return top->data;
}
int main()
{
    int choice, data;
    while(1)
    {
        printf("\n1. Push Data\n");
        printf("2. Pop Data\n");
        printf("3. Print the data at top\n");
        printf("4. Print all the data\n");
        printf("5. Quit\n");
        printf("Enter your choice:");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("Enter the data for the element to be pushed into the stack:");
                scanf("%d", &data);
                push(data);
                break;
            
            case 2:
                data = pop();
                printf("The popped element is: %d\n", data);
                break;

            case 3:
                printf("The topmost element of the stack is:%d\n", peek());
                break;

            case 4:
                print();
                break;

            case 5:
                exit(1);

            default:
                printf("Wrong Choice !\n");
                break;
        }
    }
    return 0;
}