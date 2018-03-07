#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>


typedef struct node {
    int data;
    struct node *next;
} node_t;


void listPrepend(node_t **head, int data){
    node_t *newNode = malloc(sizeof(node_t));

    newNode->data = data;
    newNode->next = *head;
    *head = newNode;
}


void listAppend(node_t *head, int data) {
    node_t *current = head;
    while(current->next != NULL) {
        current = current->next;
    }

    current->next = malloc(sizeof(node_t));
    current->next->data = data;
    current->next->next = NULL;
}


int listRemoveFirst(node_t **head) {
    assert(*head != NULL);

    int dataReturn = 0;
    node_t *nextNode = NULL;

    nextNode = (*head)->next;
    dataReturn = (*head)->data;
    free(*head);
    *head = nextNode;

    return dataReturn;
}


int listRemoveLast(node_t *head) {
    int dataReturn = 0;

    // if there is only 1 item in the list, remove it
    if(head->next == NULL) {
        dataReturn = head->data;
        free(head);
        return dataReturn;
    }
    
    // get to the second last node in the list
    node_t *current = head;
    while(current->next->next != NULL) {
        current = current->next;
    }

    // now current points to second last node, so remove current->next
    dataReturn = current->next->data;
    free(current->next);
    current->next=NULL;
    return dataReturn;
}


int listRemoveByData(node_t **head, int data) {
    node_t *previous, *current;

    assert(*head != NULL);

    if((*head)->data == data) {
        return listRemoveFirst(head);
    }

    previous = current = (*head)->next;
    while(current) {
        if(current->data == data) {
            previous->next = current->next;
            free(current);
            return data;
        }

        previous = current;
        current = current->next;
    }
    
    // will only reach here if data was not found 
    return -1;
}


void listPrint(node_t *head) {
    node_t *current = head;

    while(current != NULL) {
        printf("%d\n", current->data);
        current = current->next;
    }
}

int main() {
    node_t *head = NULL;
    head = malloc(sizeof(node_t));
    assert(head != NULL);
    head->data = 2;
    
    int data = -1;

    listAppend(head, 5); 
    listAppend(head, 10); 
    listAppend(head, 15); 
    listAppend(head, 20); 
    listAppend(head, 25); 

    //listPrepend(&head, 5);
    //listPrepend(&head, 10);
    //listPrepend(&head, 15);
    //listPrepend(&head, 20);
    //listPrepend(&head, 25);

    listPrint(head);

    data = listRemoveFirst(&head);
    printf("Removed first node = %d\n", data);
    listPrint(head);

    data = listRemoveLast(head);
    printf("Removed last node = %d\n", data);
    listPrint(head);

    data = listRemoveByData(&head, 10);
    printf("Remove node with data = %d\n", data);
    listPrint(head);
}

