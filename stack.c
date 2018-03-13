#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


typedef struct stack {
    int top;
    int capacity;
    int *array;
} Stack;


/*
 * Create stack of given capacity
 */
Stack* stackCreate(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity);
    return stack;
}


/*
 * Stack is full when top equald the last index
 */
int stackIsFull(Stack* stack) {
    return stack->top == stack->capacity - 1;
}


/*
 * Stack is empty when top equals -1
 */
int stackIsEmpty(Stack* stack) {
    return stack->top == -1;
}


/*
 * Add item to top of stack
 */
void stackPush(Stack* stack, int item) {
    if(stackIsFull(stack)) {
        return;
    }

    stack->array[++stack->top] = item;
    printf("%d pushed to stack\n", item);
}


/*
 * Remove item from top of stack
 */
int stackPop(Stack* stack) {
    if(stackIsEmpty(stack)) {
        return INT_MIN;
    }

    return stack->array[stack->top--];
}


void main() {
    Stack* stack = stackCreate(100);
    stackPush(stack, 10);
    stackPush(stack, 20);
    stackPush(stack, 30);

    printf("%d popped from stack\n", stackPop(stack));
}

