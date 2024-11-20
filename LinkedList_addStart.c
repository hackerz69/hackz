#include<stdio.h>
#include<stdlib.h>
struct node 
{
    int data;
    struct node *link;
}*head;
// function to create a linked list
createList(int n)
{
    struct node *newNode, *ptr; 
    int data;
    newNode = malloc(sizeof(struct node));
    if(newNode == NULL)
    {
        printf("Unable to allocate memory\n");
    }
    else
    {
        printf("Enter the data of node1:\n");
        scanf("%d", &data);
        newNode->data = data;
        newNode->link = NULL;
        head = newNode;
        ptr = newNode;

        for(int i=2; i<=n; i++)
        {
            struct node * newNode = malloc(sizeof(struct node));
            if(newNode == NULL)
            {
                printf("Unable to allocate memory");
                break;
            }
            else
            {
                printf("Enter the data of node%d: \n", i);
                scanf("%d", &data);
                newNode->data = data;
                newNode->link = NULL;
                ptr->link = newNode;
                ptr = ptr->link;
            }

        }
    }
}
// function for inserting node at start
struct node *addAtstart(struct node *head)
{
    int data;
    printf("enter the data to the node to add at start:\n");
    scanf("%d", &data);
    struct node *ptr = malloc(sizeof(struct node));
    ptr->data = data;
    ptr->link = NULL;
    ptr->link = head;
    head = ptr;
    return head;
}
void traverse(struct node *head)
{
    if(head==NULL)
    {
        printf("The List is empty");
    }
    struct node *ptr = head;
    while(ptr!=NULL)
    {
        printf("%d\t", ptr->data);
        ptr = ptr->link;
    }
    printf("\n");
}
int main()
{
    int n;
    printf("Enter the no. of nodes:\n");
    scanf("%d", &n);
    createList(n);
    traverse(head);
    head = addAtstart(head);
    printf("Linked list after adding a node at start:\n");
    traverse(head);
    return 0;
}