#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXNAME 31
#define MAXNUMBER 11

typedef struct node
{
    char name[MAXNAME];
    char phone[MAXNUMBER];
    struct node *next;
} node;

typedef struct node Node;
typedef struct node *NodePointer;

void insertNode(char[], char[], NodePointer *);
void displayList(NodePointer);
void deleteNode(char[], NodePointer *);
void menu(NodePointer *, char *, char *);

int main()
{
    char name[MAXNAME] = {'\0'};
    char phone[MAXNUMBER] = {'\0'};
    NodePointer head = NULL;

    menu(&head, name, phone);

    return 0;
}

void insertNode(char nameV[], char phoneV[], NodePointer *head2)
{
    NodePointer newNode = NULL;
    NodePointer previous = NULL;
    NodePointer current = *head2;

    newNode = malloc(sizeof(Node));

    if (NULL != newNode)
    {
        strcpy(newNode->name, nameV);
        strcpy(newNode->phone, phoneV);
        while (NULL != current && strcmp(nameV, current->name) > 0)
        {
            previous = current;
            current = current->next;
        }
        if (NULL == previous)
        {
            newNode->next = current;
            *head2 = newNode;
        }
        else
        {
            previous->next = newNode;
            newNode->next = current;
        }
    }
}

void displayList(NodePointer current)
{
    if(NULL == current){
      printf("    The linked list is empty!\n\n");
      return;
    }
    while (current->next != NULL)
    {
        printf("    \033[33m%s\033[0m <-> %s\n", current->name, current->phone);
        current = current->next;
    }

    printf("    \033[33m%s\033[0m <-> %s\n", current->name, current->phone);
    printf("\n");
}

void deleteNode(char nameV[], NodePointer *head3)
{
    NodePointer tempNode = NULL;
    NodePointer previous = NULL;
    NodePointer current = *head3;

    if (NULL == current)
    {
        printf("\n    \033[31mCannot delete from empty list!\033[0m\n\n");
        return;
    }

    if (0 == strcmp(nameV, current->name))
    {
        tempNode = current;
        *head3 = current->next;
        printf("\n    \033[31mDeleting \"%s\" . . .\n\n\033[0m", tempNode->name);
        free(tempNode);
    }
    else
    {
        while (NULL != current && 0 != strcmp(nameV, current->name))
        {
            previous = current;
            current = current->next;
        }
        if (NULL != current)
        {
            tempNode = current;
            previous->next = current->next;
            printf("\n    \033[31mDeleting \"%s\" . . .\n\n\033[0m", tempNode->name);
            free(tempNode);
        } else {
          printf("\n    \033[31mNot found contact \"%s\" . . .\n\n\033[0m", nameV);
        }
    }
}

void menu(NodePointer *head, char * name, char * phone) {
  int flag = -1;
  do {

    switch(flag) {
      case -1:
        printf("\e[1;1H\e[2J");
        printf("\n\n    \033[34m╔════════════╗\n");
        printf("    ║ Renrakusen ║\n");
        printf("    ╚════════════╝\033[0m\n\n");
        break;        
      case 0:
        break;
      case 1:
        printf("\e[1;1H\e[2J");
        printf("\n\n    \033[36m╔════════════════════╗\n");
        printf("    ║ LISTA DE CONTACTOS ║\n");
        printf("    ╚════════════════════╝\033[0m\n\n");
        displayList(*head);
        break;
      case 2:
        printf("\e[1;1H\e[2J");
        printf("\n\n    \033[36m╔══════════════════════╗\n");
        printf("    ║ CREAR NUEVO CONTACTO ║\n");
        printf("    ╚══════════════════════╝\033[0m\n\n");
        
        printf("    Enter the name: ");
        scanf("%s", name);  

        printf("    Enter the phone: ");
        scanf("%s", phone);
        
        insertNode(name, phone, head);
        printf("    \033[33m-> CONTACT CREATED\033[0m\n\n");
        break;
      case 3:
        printf("\e[1;1H\e[2J");
        printf("\n\n    \033[36m╔═══════════════════╗\n");
        printf("    ║ ELIMINAR CONTACTO ║\n");
        printf("    ╚═══════════════════╝\033[0m\n\n");
        printf("    Enter the name: ");
        scanf("%s", name);
        deleteNode(name, head);
        break;
      default:
        printf("\e[1;1H\e[2J");
        printf("\n\n    \033[31m╔═══════════════════════════════╗\n");
        printf("    ║ INTRODUCE UNA OPCIÓN CORRECTA ║\n");
        printf("    ╚═══════════════════════════════╝\033[0m\n\n");
        break;
    } 

    printf(" \033[33m 1. \033[0m Ver Contactos \033[33m 2. \033[0m Crear Contacto \033[33m 3. \033[0m Borrar Contacto \033[33m 0. \033[0m Salir del menu\n");
    printf(" \033[35m > \033[0m");
    scanf("%d", &flag);

  } while(flag != 0);
}