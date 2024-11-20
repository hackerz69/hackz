#include <stdio.h>
#include <stdlib.h>
struct node 
{
    int data;
    struct node *prev;
    struct node *next;
}*head;

void createList(int n)
{
    struct node *newNode, *ptr;
    int data;
    newNode = malloc(sizeof(struct node));
    if (newNode == NULL)
        printf("Unable to allocate memory");
    else
    {
        printf("Enter data for node1:");
        scanf("%d", &data);
        newNode->data = data;
        newNode->next = NULL;
        newNode->prev = NULL;
        head = newNode;
        ptr = newNode;
    }
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
                newNode ->next = NULL;
                newNode ->prev = ptr;
                
                ptr->next = newNode; 
                ptr = ptr->next; 
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
        ptr = ptr->next;
    }
    printf("\n");
}
void add_end(struct node* head)
{
    int data;
    printf("Enter data for the node to add at end:");
    scanf("%d", &data);
    struct node *ptr = head;
    struct node *newNode = malloc(sizeof(struct node));
    newNode-> data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    while(ptr->next != NULL)
    {
        ptr = ptr->next;
    }
    ptr->next = newNode;
    newNode->prev = ptr;
}
int main()
{
    int n;
    printf("Enter the no. of nodes:\n");
    scanf("%d", &n);
    createList(n);
    traverse(head);
    add_end(head);
    printf("The list after adding a node at end:\n");
    traverse(head);
    return 0;
}