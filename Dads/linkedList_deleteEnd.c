#include<stdio.h>
#include<stdlib.h>

struct node 
{
    int data;
    struct node *link;
}*head;
struct node *del_end(struct node *head)
{
    if(head==NULL)
    {
        printf("list is already empty");
    }
    else if(head->link == NULL)
    {
        free(head);
        head = NULL;
    }
    else
    {
        struct node *temp = head, *temp2 = head;
        while(temp->link != NULL)
        {
            temp2 = temp;
            temp = temp->link;
        }
        temp2->link = NULL;
        free(temp);
        temp = NULL;
    }
    return head;
}
void createList(int n)
{
    struct node *newNode, *ptr;
    int data;
    newNode = (struct node*)malloc(sizeof(struct node));
    if(newNode==NULL)
    {
        printf("Unable to allocate memory");
    }
    else
    {
        printf("Enter the data of node1: ");
        scanf("%d", &data);
        newNode -> data = data;
        newNode -> link = NULL;
        head = newNode; // address of the new node gets stored in the 'head' 
        ptr = newNode; // address of the new node gets stored in the 'ptr'

        for(int i=2; i<=n; i++)
        {
            newNode = (struct node*)malloc(sizeof(struct node));
            if(newNode == NULL)
            {
                printf("Unable to allocate memory");
                break;
            }
            else
            {
                printf("Enter the data of node%d: ",i);
                scanf("%d", &data);
                newNode ->data = data;
                newNode ->link = NULL;
                // storing the address of the new node into the link part of previous node
                ptr -> link = newNode; // linking the previous node with the new node 
                ptr = ptr->link; // moving forward to the next node for next operation
            }
        }
    }
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
    printf("Enter the no. of nodes: \n");
    scanf("%d", &n);
    createList(n);
    traverse(head);
    head = del_end(head);
    printf("List after deleting the node from end\n");
    traverse(head);
    return 0;
}