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
void del_pos(struct node* head, int pos)
{
    int p = pos;
    struct node *ptr = head, *ptr2;
    while(p>1)
    {
        ptr = ptr->next;
        p--;
    }
    ptr2 = ptr->prev;
    ptr2->next = ptr->next;
    ptr->next->prev = ptr2;
    free(ptr);
    ptr = NULL;
}
int main()
{
    int n, pos;
    printf("Enter the no. of nodes:\n");
    scanf("%d", &n);
    createList(n);
    traverse(head);
    printf("Enter a position to delete the node:");
    scanf("%d", &pos);
    del_pos(head,pos);
    printf("The list after deleting the node at end:\n");
    traverse(head);
    return 0;
}