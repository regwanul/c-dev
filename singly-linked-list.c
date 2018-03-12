#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>


typedef struct node {
    int data;
    struct node* next;
} Node;


/* 
 * Add node to head of list 
 */
void listPrepend(Node** head, int data) {
    // create new node
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    
    // point new node's next to the old head 
    newNode->next = *head;

    // head is now the new node
    *head = newNode;
}


/*
 * Add node to end of list
 */
void listAppend(Node** head, int data) {
    Node* current = *head;

    if(current == NULL) { 
        // list is empty, create new
        current = (Node*)malloc(sizeof(Node));
        current->data = data;
        
        // point to the old head
        current->next = *head;

        // point to the new node
        *head = current;
    } else {
        // go to the end of the list
        while(current->next != NULL) {
            current = current->next;
        }
        
        // create new node
        current->next = (Node*)malloc(sizeof(Node));
        current->next->data = data;

        current->next->next = NULL;
    }
}


/*
 * Find a node with given specific key
 */
Node* listSearch(Node* head, int key) {
    Node* current = head;

    // traverse through list until key is found
    while(current != NULL) {
        if(current->data == key) {
            return current;
        }

        current = current->next;
    }

    return NULL;

}


/*
 * Delete the first node in a list
 */
int listDeleteFirst(Node** head) {
    assert(*head != NULL);

    // point to next node
    Node* node = (*head)->next;

    int data = (*head)->data;

    // free head pointer
    free(*head);

    // make the next node head
    *head = node;

    return data;
}


/*
 * Delete the last node in a list
 */
int listDeleteLast(Node** head) {
    assert(*head != NULL);
    int data = -1;

    // if only 1 node in the list
    if((*head)->next == NULL) {
        data = (*head)->data;
        free(*head);
        return data;
    }

    // traverse to the end of the list
    Node* current = *head;
    while(current->next->next != NULL) {
        current = current->next;
    }

    data = current->next->data;
    free(current->next);
    current->next = NULL;

    return data;
}


/*
 * Delete node given a specific key
 */
int listDeleteNode(Node** head, int key) {
    assert(*head != NULL);

    Node* current = *head;
    Node* previous = NULL;
    Node* tempNode;

    // traverse through list
    while(current->data != key) {

        // last node, return
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
        free(*head);
        *head = tempNode;
    } else {
        // remove current node
        previous->next = current->next;
        free(current);
    }

    return key;
}


/*
 * Reverse the list
 */
void listReverse(Node** head) {
    assert(*head != NULL);

    Node* current = *head;
    Node* previous = NULL;
    Node* next;

    while(current != NULL) {

        // save next as the current node's next node
        next = current->next;

        // make current's next node point to previous node
        current->next = previous;

        // previous is the new current
        previous = current;

        // next node is the new current
        current = next;
    }

    *head = previous;
}


/*
 * Swap the min and max nodes (first and last?)
 */
void listSwapMinMax(Node** head) {
    assert(*head != NULL);

    // save the head node
    Node* tempNode = *head;

    Node* current = *head;
    Node* previous = NULL;

    // traverse to the last node
    while(current->next != NULL) {
        previous = current;
        current = current->next;
    }

    // make the end node the new head node
    current->next = (*head)->next;
    *head = current;

    // make the saved head node, the new end node
    previous->next = tempNode;
    tempNode->next = NULL;
}


/* 
 * Prints the list
 */
void listPrint(Node* head) {
   Node* current = head;

    while(current != NULL) {
        printf("%d->", current->data);
        current = current->next;
    }

    printf("\n");
}



void main() {
    Node* list1 = NULL;
    int data = -1;

    listPrepend(&list1, 5);
    listPrepend(&list1, 10);
    listPrepend(&list1, 15);
    listPrepend(&list1, 20);
    listPrepend(&list1, 25);

    listPrint(list1);

    printf("%d\n", listSearch(list1, 5)->data);

    data = listDeleteFirst(&list1);
    printf("Removed first node = %d\n", data);
    listPrint(list1);

    data = listDeleteLast(&list1);
    printf("Removed last node = %d\n", data);
    listPrint(list1);

    data = listDeleteNode(&list1, 10);
    printf("Removed node with key = 10: %d\n", data);
    listPrint(list1);


    Node* list2 = NULL;
    listPrepend(&list2, 100);
    listPrepend(&list2, 200);
    listPrepend(&list2, 300);
    listPrepend(&list2, 400);
    listPrepend(&list2, 500);
    
    printf("List 2:\n");
    listPrint(list2);
    listReverse(&list2);
    printf("Reversed List 2:\n");
    listPrint(list2);

    printf("Swapping min and max in List 2:\n");
    listSwapMinMax(&list2);
    listPrint(list2);

    data = listDeleteNode(&list2, 300);
    printf("Removed node with key = 300: %d\n", data);
    listPrint(list2);

    Node* list3 = NULL;
    listPrepend(&list3, 11);
    listPrepend(&list3, 22);
    listPrepend(&list3, 33);
    listPrint(list3);
    listSwapMinMax(&list3);
    listPrint(list3);
}

