#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// Stack structure
typedef struct {
    char operations[MAX][50]; // Array of strings
    int top;
} Stack;

// Initialize stack
void initStack(Stack* s) {
    s->top = -1;
}

// Check if stack is empty
int isEmpty(Stack* s) {
    return s->top == -1;
}

// Check if stack is full
int isFull(Stack* s) {
    return s->top == MAX - 1;
}

// Push operation to stack
void push(Stack* s, const char* op) {
    if (isFull(s)) {
        printf("Stack overflow. Cannot perform operation.\n");
        return;
    }
    s->top++;
    strcpy(s->operations[s->top], op);
}

// Pop operation from stack
char* pop(Stack* s) {
    if (isEmpty(s)) {
        return NULL;
    }
    return s->operations[s->top--];
}

// Peek top operation
char* peek(Stack* s) {
    if (isEmpty(s)) {
        return NULL;
    }
    return s->operations[s->top];
}

// Clear stack
void clear(Stack* s) {
    s->top = -1;
}

// Perform operation
void performOperation(Stack* undo, Stack* redo, const char* op) {
    push(undo, op);
    clear(redo);
    printf("Performed operation: \"%s\"\n", op);
}

// Undo operation
void undoOperation(Stack* undo, Stack* redo) {
    char* op = pop(undo);
    if (op == NULL) {
        printf("Nothing to undo.\n");
        return;
    }
    push(redo, op);
    char* next = peek(undo);
    if (next)
        printf("Undone. Next Operation that can be undone is = \"%s\"\n", next);
    else
        printf("Undone. No more operations to undo.\n");
}

// Redo operation
void redoOperation(Stack* undo, Stack* redo) {
    char* op = pop(redo);
    if (op == NULL) {
        printf("Nothing to redo.\n");
        return;
    }
    push(undo, op);
    char* next = peek(redo);
    if (next)
        printf("Redo completed. Next Operation that can be redone is = \"%s\"\n", next);
    else
        printf("Redo completed. No more operations to redo.\n");
}

// Main function
int main() {
    Stack undoStack, redoStack;
    initStack(&undoStack);
    initStack(&redoStack);

    performOperation(&undoStack, &redoStack, "op1");
    performOperation(&undoStack, &redoStack, "op2");
    performOperation(&undoStack, &redoStack, "op3");

    undoOperation(&undoStack, &redoStack);
    undoOperation(&undoStack, &redoStack);

    redoOperation(&undoStack, &redoStack);

    performOperation(&undoStack, &redoStack, "op4");

    undoOperation(&undoStack, &redoStack);

    return 0;
}
