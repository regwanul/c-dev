#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>



typedef struct htItem {
    int key;
    int data;
    struct htItem* next;
} HtItem;


typedef struct htHashTable {
    int size;
    int count;
    HtItem* dummyItem;
    HtItem** items;
} HtHashTable;


int hashCode(HtHashTable* ht, int key) {
    return key % ht->size;
}


HtHashTable* htCreateNew(int size) {
    HtHashTable* ht = (HtHashTable*)malloc(sizeof(HtHashTable));
    ht->size = size;
    ht->count = 0;
    ht->items = (HtItem**)calloc((size_t)ht->size, sizeof(HtItem*));
    
    return ht;
}


void htInsert(HtHashTable* ht, int key, int data) {
    HtItem* item = (HtItem*)malloc(sizeof(HtItem));
    item->key = key;
    item->data = data;

    int hashIndex = hashCode(ht, key);
    HtItem* curItem = ht->items[hashIndex];

    
    if(curItem == NULL) {
        curItem = item;
        curItem->next = NULL;
        ht->items[hashIndex] = curItem;
    } else {
        while(curItem->next != NULL && curItem->next != ht->dummyItem) {
            curItem = curItem->next;
        }
        if(curItem->next != NULL) {
            item->next = curItem->next->next;
        }
        curItem->next = item;
        ht->count++;
    }
}



void htPrint(HtHashTable* ht) {
    HtItem* curItem;

    for(int i = 0; i < ht->size; i++) {
        curItem = ht->items[i];

        if(curItem == NULL) {
            printf("(EMPTY)\n");
            continue;
        }

        while(curItem != NULL) {
            if(curItem != ht->dummyItem) {
                printf("(%d, %d)->", curItem->key, curItem->data);
            } else {
                printf("(EMPTY)->");
            }

            curItem = curItem->next;
        }
        printf("\n");
    }
}


void main() {
    int size = 20;
    HtHashTable* ht = htCreateNew(size);

    htInsert(ht, 1, 10);
    htInsert(ht, 1, 20);
    htInsert(ht, 1, 30);
    htInsert(ht, 1, 40);
    htInsert(ht, 1, 50);

    htPrint(ht);
}
