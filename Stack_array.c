#include<stdio.h>
#include<stdlib.h>
int top = 0;
int n;

void print_data(int stack_arr[])
{
    if(top==0)
        printf("No data in the stack!\n");
    else
    {
        printf("The data in stack from top to bottom is:\n");
        for(int i=top-1; i>=0; i--)
        {
            printf("%d\n", stack_arr[i]);
        }
    }
}
int isEmpty(int n)
{
    if(top==0)
    {
        printf("The stack is empty!\n");
        return 1;
    }
    else
    {
        printf("The stack is not empty!\n");
        return 0;
    }
}
int isFull(int n)
{
    if(top==n)
    {
        printf("The stack is full!\n");
        return 1;
    }
    else
    {
        printf("The stack is not full!\n");
        return 0;
    }
        
}
void push(int data, int stack_arr[])
{
    int flag = isFull(n);
    if(flag==1)
    {
        printf("cannot push the data'%d' into the stack\n", data);
    }
    else
    {
        printf("pushed the data'%d'into the stack\n", data);
        stack_arr[top] = data;
        top++;
    }
}
void pop(int stack_arr[])
{   
    if(top==0)
        printf("Nothing to pop from the stack\n");
    else
    {
        top--;
        int data = stack_arr[top];
        printf("popped the data'%d' from the stack\n", data);
    }
}
int main()
{
    printf("Enter the size of stack:");
    scanf("%d", &n);
    int stack_arr[n];

    push(3,stack_arr);
    push(4,stack_arr);
    push(5,stack_arr);
    push(6,stack_arr);
    print_data(stack_arr);
    pop(stack_arr);
    print_data(stack_arr);
    return 0;
}