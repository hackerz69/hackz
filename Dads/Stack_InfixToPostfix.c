#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define MAX 100

char stack[MAX];
char infix[MAX];
char postfix[MAX];
int top = -1;

void push(char symbol)
{
    if(top == MAX - 1)
    {
        printf("Stack Overflow.\n");
        return;
    }
    top++;
    stack[top] = symbol;
}
char pop()
{
    char c;
    if(top == -1)
    {
        printf("Stack Underflow\n");
        exit(1);
    }
    c = stack[top];
    top--;
    return c;
}
int isEmpty()
{
    if(top == -1)
        return 1;
    else
        return 0;
}
int precedence(char symbol)
{
    switch(symbol)
    {
        // higher value has higher precendence
        case '^' :
            return 3;
        
        case '/' :
        case '*' :
            return 2;
        
        case '+' :
        case '-' :
            return 1;

        default :
            return 0;
    }
}

void inTopos()
{
    int i, j=0;
    char symbol, next;
    for(i=0; i<strlen(infix); i++)
    {
        symbol = infix[i];
        switch(symbol)
        {
            case '(' :
                push(symbol);
                break;

            case ')' :
                while((next=pop()) != '(')
                    postfix[j++] = next;
                break;

// applying the same conditions for all these cases
            case '+' :
            case '-' :
            case '*' :
            case '/' :
            case '^' :
                while(!isEmpty() && precedence(stack[top]) >= precedence(symbol))
                    postfix[j++] = pop();
                push(symbol);
                break;

            default : //storing the operands
                postfix[j++] = symbol;
        }
    }
    while(!isEmpty())
        postfix[j++] = pop();
    postfix[j] = '\0';
}

void print()
{
    int i=0;
    printf("The postfix expression is: ");
    while(postfix[i])
        printf("%c", postfix[i++]);
    printf("\n");
}
int main()
{
    printf("Enter the infix expression without spaces: ");
    gets(infix);// storing the expression

    inTopos();
    print();
    return 0;
}