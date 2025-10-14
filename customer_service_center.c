#include <stdio.h>
#include <stdlib.h>

#define MAX 5  // Maximum size of the circular queue

// Circular Queue structure
typedef struct {
    int arr[MAX];
    int front;
    int rear;
} CircularQueue;

// Initialize the queue
void initQueue(CircularQueue* q) {
    q->front = -1;
    q->rear = -1;
}

// Check if queue is empty
int isEmpty(CircularQueue* q) {
    return q->front == -1;
}

// Check if queue is full
int isFull(CircularQueue* q) {
    return ((q->rear + 1) % MAX) == q->front;
}

// Add a new call (enqueue)
void addCall(CircularQueue* q, int customerID) {
    if (isFull(q)) {
        printf("Queue Overflow! Cannot add customer ID %d\n", customerID);
        return;
    }
    if (isEmpty(q)) {
        q->front = q->rear = 0;
    } else {
        q->rear = (q->rear + 1) % MAX;
    }
    q->arr[q->rear] = customerID;
    printf("Added customer ID %d to the queue.\n", customerID);
}

// Remove a call (dequeue)
void removeCall(CircularQueue* q) {
    if (isEmpty(q)) {
        printf("Queue Underflow! No calls to remove.\n");
        return;
    }
    int customerID = q->arr[q->front];
    if (q->front == q->rear) {  // Only one element
        q->front = q->rear = -1;
    } else {
        q->front = (q->front + 1) % MAX;
    }
    printf("Removed customer ID %d from the queue.\n", customerID);
}

// Display queue
void displayQueue(CircularQueue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Current Queue: ");
    int i = q->front;
    while (1) {
        printf("%d ", q->arr[i]);
        if (i == q->rear)
            break;
        i = (i + 1) % MAX;
    }
    printf("\n");
}

int main() {
    CircularQueue queue;
    initQueue(&queue);

    int choice, customerID;

    while (1) {
        printf("\n--- Customer Service Queue Menu ---\n");
        printf("1. Add New Call\n");
        printf("2. Remove Call (Agent free)\n");
        printf("3. Display Queue\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter customer ID to add: ");
                scanf("%d", &customerID);
                addCall(&queue, customerID);
                break;
            case 2:
                removeCall(&queue);
                break;
            case 3:
                displayQueue(&queue);
                break;
            case 4:
                printf("Exiting program...\n");
                exit(0);
            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}
