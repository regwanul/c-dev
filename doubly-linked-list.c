#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>


typedef struct node {
    int data;
    struct node *prev;
    struct node *next;
} node_t;


void listAddToFront(node_t **head, node_t **tail, int data) {
    node_t *newNode = malloc(sizeof(node_t));
    newNode->data = data;

    if(*head == NULL) {
        *tail = newNode;
    } else {
        (*head)->prev = newNode;
    }

    newNode->next = *head; 
    *head = newNode;
}


void listAddToEnd(node_t **head, node_t **tail, int data) {
    node_t *newNode = malloc(sizeof(node_t));
    newNode->data = data;

    if((*tail) == NULL) {
        *head = newNode;
    } else {
        (*tail)->next = newNode;
        newNode->prev = *tail;
    }

    *tail = newNode;
}


int listRemoveFromFront(node_t **head, node_t **tail) {
    assert(*head != NULL);
    
    node_t *nextNode = (*head)->next;
    int dataReturn = -1;

    if((*head)->next = NULL) {
        *tail = NULL;
    } else {
        nextNode->prev = NULL;
    }

    dataReturn = (*head)->data;
    free(*head);
    *head = nextNode;

    return dataReturn;
}


int listRemoveFromEnd(node_t **head, node_t **tail) {
    assert(*tail != NULL);

    node_t *prevNode = (*tail)->prev;
    int dataReturn = -1;

    if((*tail)->prev == NULL) {
        *head = NULL;
    } else {
        prevNode->next = NULL;
    }

    dataReturn = (*tail)->data;
    free(*tail);
    *tail = prevNode;

    return dataReturn;
}


void listPrintForward(node_t *head) {
    assert(head != NULL);

    node_t *current = head;

    while(current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}


void listPrintBackward(node_t *tail) {
    assert(tail != NULL);

    node_t *current = tail;

    while(current != NULL) {
        printf("%d ", current->data);
        current = current->prev;
    }
    printf("\n");
}


int main() {
    node_t *head = NULL;
    node_t *tail = NULL;

    listAddToFront(&head, &tail, 5);    
    listAddToFront(&head, &tail, 10);    
    listAddToFront(&head, &tail, 15);    
    listAddToFront(&head, &tail, 20);    
    listAddToFront(&head, &tail, 25);    

    listPrintForward(head);

    listAddToEnd(&head, &tail, 11);    
    listAddToEnd(&head, &tail, 22);    
    listAddToEnd(&head, &tail, 33);    
    listAddToEnd(&head, &tail, 44);    
    listAddToEnd(&head, &tail, 55);    

    listPrintForward(head);

    int data = -1;
    data = listRemoveFromFront(&head, &tail);
    printf("Removed first node\n");
    listPrintForward(head);


    data = listRemoveFromEnd(&head, &tail);
    printf("Removed last node\n");
    listPrintForward(head);
}

