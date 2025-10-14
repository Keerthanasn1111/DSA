#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Stack structure
typedef struct {
    int data[MAX];
    int top;
} Stack;

// Initialize stack
void initStack(Stack *s) {
    s->top = -1;
}

// Check if stack is empty
int isEmpty(Stack *s) {
    return s->top == -1;
}

// Check if stack is full
int isFull(Stack *s) {
    return s->top == MAX - 1;
}

// Push operation
void push(Stack *s, int value) {
    if (isFull(s)) {
        printf("Stack Overflow\n");
        return;
    }
    s->data[++(s->top)] = value;
}

// Pop operation
int pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack Underflow\n");
        return -1;
    }
    return s->data[(s->top)--];
}

// Clear stack
void clear(Stack *s) {
    s->top = -1;
}

// Perform operation
void performOperation(Stack *undo, Stack *redo, int opCode) {
    push(undo, opCode);
    clear(redo);  // Once a new operation is done, redo history is cleared
    printf("Performed operation: %d\n", opCode);
}

// Undo operation
void undoOperation(Stack *undo, Stack *redo) {
    if (isEmpty(undo)) {
        printf("Nothing to undo\n");
        return;
    }
    int op = pop(undo);
    push(redo, op);
    printf("Undone operation: %d\n", op);
}

// Redo operation
void redoOperation(Stack *undo, Stack *redo) {
    if (isEmpty(redo)) {
        printf("Nothing to redo\n");
        return;
    }
    int op = pop(redo);
    push(undo, op);
    printf("Redone operation: %d\n", op);
}

int main() {
    Stack undoStack, redoStack;
    initStack(&undoStack);
    initStack(&redoStack);

    int choice, opCode;

    while (1) {
        printf("\n--- Undo/Redo Menu ---\n");
        printf("1. Perform Operation\n");
        printf("2. Undo Operation\n");
        printf("3. Redo Operation\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter operation code (integer): ");
                scanf("%d", &opCode);
                performOperation(&undoStack, &redoStack, opCode);
                break;

            case 2:
                undoOperation(&undoStack, &redoStack);
                break;

            case 3:
                redoOperation(&undoStack, &redoStack);
                break;

            case 4:
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}
