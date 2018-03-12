#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>


typedef struct node {
    int data;
    struct node* prev;
    struct node* next;
} Node;


/*
 * Add new node to head of list
 */
void listPrepend(Node** head, Node** tail, int data) {
    Node* newNode = malloc(sizeof(Node));
    newNode->data = data;

    // list is empty, create new
    if(*head == NULL) {
        newNode->prev = NULL;
        newNode->next = NULL;
        *head = newNode;
        *tail = newNode;

        return;
    }

    // point new node's next to current head
    newNode->next = *head;

    // point current head's previous to new node
    (*head)->prev = newNode;

    // make new node the current tail
    *head = newNode;
}


/*
 * Add new node to tail of list
 */
void listAppend(Node** head, Node** tail, int data) {
    Node* newNode = malloc(sizeof(Node));
    newNode->data = data;

    if(*tail == NULL) {
        newNode->prev = NULL;
        newNode->next = NULL;
        *tail = newNode;
        *head = newNode;
        
        return;
    }

    // point new node's previous to current tail
    newNode->prev = *tail;

    // point current tail's next to new node
    (*tail)->next = newNode;

    // make new node the current tail
    *tail = newNode;
}


/*
 * Print the list from head to tail
 */
void listPrintForward(Node* head) {
    assert(head != NULL);

    Node* current = head;

    while(current != NULL) {
        printf("%d<->", current->data);
        current = current->next;
    }
    printf("\n");
}


/*
 * Delete first node in list
 */
int listDeleteFirst(Node** head, Node** tail) {
    assert(*head != NULL);
    Node* tempNode = (*head)->next;

    // if only one node
    if((*head)->next == NULL) {
        *tail = NULL;
    } else {
        tempNode->prev = NULL;
    }

    int data = (*head)->data;
    free(*head);
    *head = tempNode;
    return data;
}


int listDeleteLast(Node** head, Node** tail) {
    assert(*tail != NULL);
    Node* tempNode = (*tail)->prev;

    // if only one node
    if((*tail)->prev == NULL) {
        *head = NULL;
    } else {
        tempNode->next = NULL;
    }

    int data = (*tail)->data;
    free(*tail);
    *tail = tempNode;
    return data;
}


/*
 * Delete node with matching key
 */
int listDeleteNode(Node** head, Node** tail, int key) {
    assert(*head != NULL);

    Node* current = *head;
    Node* previous = NULL;
    Node* tempNode;

    // traverse through list 
    while(current->data != key) {
        // reached last node, return
        if(current->next == NULL) {
            return -1;
        } else {
            // go to next node
            previous = current;
            current = current->next;
        }
    }

    // matching key found
    if(current == *head) {
        // point head to next node
        tempNode = (*head)->next;
        tempNode->prev = NULL;
        free(*head);
        *head = tempNode;
    } else if(current == *tail) {
        // point tail to previous node
        tempNode = (*tail)->prev;
        tempNode->next = NULL;
        free(*tail);
        *tail = tempNode;
    } else {
        // remove current node
        current->prev->next = current->next;
        current->next->prev = current->prev;
        free(current);
    }
    
    return key;
}


// reverse


// swap min max


/*
 * Print the list from tail to head
 */
void listPrintBackward(Node* tail) {
    assert(tail != NULL);

    Node* current = tail;

    while(current != NULL) {
       printf("%d<->", current->data); 
       current = current->prev;
    }
    printf("\n");
}


void main() {
    Node* list1Head = NULL;
    Node* list1Tail = NULL;

    listPrepend(&list1Head, &list1Tail, 5);
    listPrepend(&list1Head, &list1Tail, 10);
    listPrepend(&list1Head, &list1Tail, 15);
    listPrepend(&list1Head, &list1Tail, 20);
    listPrepend(&list1Head, &list1Tail, 25);

    listPrintForward(list1Head);

    int data = -1;
    data = listDeleteFirst(&list1Head, &list1Tail);
    printf("Removed first node\n");
    listPrintForward(list1Head);

    data = listDeleteNode(&list1Head, &list1Tail, 20);
    printf("Removed node with key = 20: %d\n", data);
    listPrintForward(list1Head);

    Node* list2Head = NULL;
    Node* list2Tail = NULL;

    listAppend(&list2Head, &list2Tail, 100);
    listAppend(&list2Head, &list2Tail, 200);
    listAppend(&list2Head, &list2Tail, 300);
    listAppend(&list2Head, &list2Tail, 400);
    listAppend(&list2Head, &list2Tail, 500);

    listPrintBackward(list2Tail);

    data = listDeleteLast(&list2Head, &list2Tail);
    printf("Removed last node\n");
    listPrintBackward(list2Tail);

    data = listDeleteNode(&list2Head, &list2Tail, 300);
    printf("Removed node with key = 300: %d\n", data);
    listPrintBackward(list2Tail);


}
