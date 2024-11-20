#include<stdio.h>
#include<stdlib.h>
struct node 
{
    int data;
    struct node *link;
}*head, *ptr;
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
// function for inserting node at end
void addend(struct node *head)
{
    struct node *ptr, *temp;
    ptr = head;
    int data;
    temp = (struct node *)malloc(sizeof(struct node));
    printf("enter the data of node to add at end:\n");
    scanf("%d", &data);
    temp->data = data;
    temp->link = NULL;
    while(ptr->link != NULL)
    {
        ptr = ptr->link;
    }
    ptr->link = temp;
    ptr = temp;

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
    addend(head);
    printf("List after adding a node at end:\n");
    traverse(head);
    return 0;
}