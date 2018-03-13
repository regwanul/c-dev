#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


typedef struct stack {
    int top;
    int capacity;
    int *array;
} MaxStack;


/*
 * Create stack of given capacity
 */
MaxStack* maxStackCreate(int capacity) {
    MaxStack* maxStack = (MaxStack*)malloc(sizeof(maxStack));
    maxStack->capacity = capacity;
    maxStack->top = -1;
    maxStack->array = (int*)malloc(maxStack->capacity * 2);
    return maxStack;
}


/*
 * Stack is full when top equald the last index
 */
int maxStackIsFull(MaxStack* maxStack) {
    return maxStack->top == maxStack->capacity - 1;
}


/*
 * Stack is empty when top equals -1
 */
int maxStackIsEmpty(MaxStack* maxStack) {
    return maxStack->top == -1;
}


/*
 * Add item to top of stack
 */
void maxStackPush(MaxStack* maxStack, int item) {
    if(maxStackIsFull(maxStack)) {
        return;
    }

    if(maxStackIsEmpty(maxStack)) {
        maxStack->array[++maxStack->top] = item;
        maxStack->array[++maxStack->top] = item;
    } else {
        maxStack->array[++maxStack->top] = item;
        if(item > maxStack->array[maxStack->top - 1 ]) {
            maxStack->array[++maxStack->top] = item;
        } else {
            maxStack->array[++maxStack->top] = maxStack->array[maxStack->top - 1]; 
        }
    }

    printf("%d pushed to stack\n", item);
}


/*
 * Remove item from top of stack
 */
int maxStackPop(MaxStack* maxStack) {
    if(maxStackIsEmpty(maxStack)) {
        return INT_MIN;
    }

    maxStack->top--;
    return maxStack->array[maxStack->top--];
}


int maxStackGetMax(MaxStack* maxStack) {
    return maxStack->array[maxStack->top];
}


void main() {
    MaxStack* maxStack = maxStackCreate(100);
    maxStackPush(maxStack, 1);
    maxStackPush(maxStack, 12);
    maxStackPush(maxStack, 33);
    maxStackPush(maxStack, 4);
    maxStackPush(maxStack, 7);
    maxStackPush(maxStack, 51);

    printf("%d is max item in the stack\n", maxStackGetMax(maxStack));
    
    printf("%d popped from stack\n", maxStackPop(maxStack));

    printf("%d is max item in the stack\n", maxStackGetMax(maxStack));
}

