#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

#define INITIAL_ARRAY_SIZE 8

int* items;
int maxSize = 0;
int size = 0;

int arraylistSize() {
    return size;
}


void arraylistEnsureExtraCapacity() {
    if(items == NULL) {
        printf("Creating new arraylist\n");

        maxSize = INITIAL_ARRAY_SIZE;
        items = malloc(maxSize * sizeof(int));
    }

    if(size == maxSize) {
        printf("Resizing arraylist\n");

        int* copy = malloc(maxSize * 2 * sizeof(int));

        for(int i = 0; i < size; i++) {
            copy[i] = items[i];
        }

        // printf("items addr=%p, copy addr=%p\n", items, copy);
        
        free(items);
        items = copy;
        maxSize = maxSize * 2;
        
        // printf("items addr=%p, copy addr=%p\n", items, copy);

    }
}


void arraylistSet(int index, int item) {
    assert(index < 0 || index >= size);
    
    items[index] = item;
}


void arraylistAppend(int item) {
    arraylistEnsureExtraCapacity();
    items[size] = item;
    size++;
}


int arraylistGet(int index) {
    assert(index < 0 || index >= size);

    return items[index];

}


void arraylistPrint(){
    printf("Printing array, size = %d, max size = %d:\n", \
    size, maxSize);

    for(int i = 0; i < size; i++) {
        printf("%d ", items[i]);
    }
    printf("\n");
}


void main() {
    int num;

    printf("Add integer to array:\n");

    while(scanf("%d", &num) == 1) {
        arraylistAppend(num);

        arraylistPrint();

        printf("Add another integer to array:\n");
    }

}

