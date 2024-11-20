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
struct node *del_start(struct node* head)
{
    head = head->next;
    free(head->prev);
    head->prev = NULL;
    return head;
}
int main()
{
    int n;
    printf("Enter the no. of nodes:\n");
    scanf("%d", &n);
    createList(n);
    traverse(head);
    head = del_start(head);
    printf("The list after deleting the node at start:\n");
    traverse(head);
    return 0;
}