#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
{
    int id;
    char name[100];
    struct Node *next;
    struct Node *bf;
};

typedef struct Node node;

int isEmpty ( node *head )
{
    return head == NULL;
}

node *printList ( node *head )
{
   if ( isEmpty( head ) ) 
   {
      puts( "List is empty.\n" );
   } // end if
   else {
      puts( "\nThe list is:" );

      while ( head->next!= NULL ) {
         printf( "id: %d\nUsername: %s \n----------\n", head->id, head->name );
         head = head->next;  
      }

      printf( "id: %d\nUsername: %s\n",head->id, head->name );
       
   }
}

node *printReverseList ( node *head )
{
   if ( isEmpty( head ) ) {
      puts( "List is empty.\n" );
   }
   else {
      puts( "\nThe Reversed list is:" );
      while ( head->next!= NULL ) 
      {
         head = head->next;  
      }
      while ( head->bf!= NULL ) 
      {
         printf( "id: %d\nUsername: %s \n----------\n", head->id, head->name );
         head = head->bf;  
      }
      printf( "id: %d\nUsername: %s\n",head->id, head->name );
   }
}

void instructions()
{
   puts( "Enter your choice:\n"
      "   1 to insert an element into the list.\n"
      "   2 to delete an element from the list.\n"
      "   3 to end." );
}

node *createNode ( int id, char *name )
{
    node *result = malloc(sizeof(node));
    result->id = id;
    strcpy(result->name, name);
    result->next = NULL;
    result->bf = NULL;
    return result;
}

void insert (node **head, node* new_node)
{
    node *tmp;

    if (*head == NULL) *head = new_node;
    else if ((*head)->id > new_node->id)
    {
        new_node->next = *head;
        new_node->next->bf = new_node;
        *head = new_node;
    }
    else 
    {
        tmp = *head;
        while (tmp->next != NULL && tmp->next->id < new_node->id) tmp = tmp->next;

        new_node->next = tmp->next;
        tmp->next = new_node;
        new_node->bf = tmp;
        if( new_node->next != NULL ) new_node->next->bf = new_node;
    }
}

void removeNode ( node **head, node *node_to_remove)
{
    if(*head == node_to_remove)
    {
        node *tmp = *head;
        *head = (*head)->next;
        if ((*head) != NULL) (*head)->bf = NULL;
        free(tmp);
        return;
    }
    else
    {
        node *tmp = node_to_remove;
        node_to_remove->bf->next = node_to_remove->next;
        if(node_to_remove->next != NULL) node_to_remove->next->bf = node_to_remove->bf;
        free(tmp);
    }
    return;
}

node *findNode ( node *head, int id)
{
    node *tmp = head;
    while (tmp != NULL)
    {
        if (tmp->id == id) return tmp;
        tmp = tmp->next;
    }
    return NULL;
}

int main (void)
{
    node *head = NULL;

    unsigned int choice;
    int item;
    char name[50];

    instructions();
    printf( "%s", "? " );
    scanf( "%u", &choice );
    while ( choice != 3 ) 
    {
        switch ( choice )
          {
            case 1:
            printf( "%s", "Enter a ID: " );
            scanf( "%d", &item );
            printf( "%s", "Enter a Name: " );
            scanf( " %s", name );
            insert( &head , createNode(item, name) );
            printList( head );
            printReverseList( head );
            break;
            case 2: 
            if ( !isEmpty( head ) ) {
                printf( "%s", "Enter number to be deleted: " );
                scanf( "%d", &item );
                if ( findNode(head, item) ) 
                { 
                    removeNode( &head, findNode(head, item));
                    printf( "%d deleted.\n", item );
                    printList( head );
                    printReverseList( head );
                } 
                else {
                    printf( "%d not found.\n\n", item );
                }
            } 
            else {
                puts( "List is empty.\n" );
            } 

            break;
            default:
            puts( "Invalid choice.\n" );
            instructions();
            break;
        }

    printf( "%s", "? " );
    scanf( "%u", &choice );
   } 

    return 1;
}