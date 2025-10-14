#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// Define structure for a tree node
struct Node {
    char ch;
    int freq;
    struct Node *left, *right;
};

// Queue structure for level order insertion and traversal
struct Queue {
    struct Node* data[MAX];
    int front, rear;
};

// Initialize queue
void initQueue(struct Queue* q) {
    q->front = q->rear = -1;
}

// Check if queue is empty
int isEmpty(struct Queue* q) {
    return q->front == -1;
}

// Enqueue
void enqueue(struct Queue* q, struct Node* node) {
    if (q->rear == MAX - 1) return;
    if (isEmpty(q)) q->front = 0;
    q->data[++q->rear] = node;
}

// Dequeue
struct Node* dequeue(struct Queue* q) {
    if (isEmpty(q)) return NULL;
    struct Node* temp = q->data[q->front];
    if (q->front == q->rear)
        q->front = q->rear = -1;
    else
        q->front++;
    return temp;
}

// Create a new node
struct Node* createNode(char ch) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->ch = ch;
    newNode->freq = 1;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to find if character exists in tree
struct Node* findChar(struct Node* root, char ch) {
    if (root == NULL) return NULL;

    struct Queue q;
    initQueue(&q);
    enqueue(&q, root);

    while (!isEmpty(&q)) {
        struct Node* temp = dequeue(&q);
        if (temp->ch == ch)
            return temp;
        if (temp->left) enqueue(&q, temp->left);
        if (temp->right) enqueue(&q, temp->right);
    }
    return NULL;
}

// Function to insert character level-wise
struct Node* insertLevelOrder(struct Node* root, char ch) {
    if (root == NULL)
        return createNode(ch);

    // Check if character already exists
    struct Node* found = findChar(root, ch);
    if (found != NULL) {
        found->freq++;
        return root;
    }

    // Else insert new character at first available position (level-wise)
    struct Queue q;
    initQueue(&q);
    enqueue(&q, root);

    while (!isEmpty(&q)) {
        struct Node* temp = dequeue(&q);

        if (temp->left == NULL) {
            temp->left = createNode(ch);
            break;
        } else {
            enqueue(&q, temp->left);
        }

        if (temp->right == NULL) {
            temp->right = createNode(ch);
            break;
        } else {
            enqueue(&q, temp->right);
        }
    }

    return root;
}

// Function to build binary tree from input string
struct Node* buildTree(char str[]) {
    struct Node* root = NULL;
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] != ' ')  // Ignore spaces
            root = insertLevelOrder(root, str[i]);
    }
    return root;
}

// Function for level order traversal
void levelOrderTraversal(struct Node* root) {
    if (root == NULL) {
        printf("Tree is empty.\n");
        return;
    }

    struct Queue q;
    initQueue(&q);
    enqueue(&q, root);

    printf("\nCharacter Frequency Table:\n");
    printf("---------------------------\n");

    while (!isEmpty(&q)) {
        struct Node* temp = dequeue(&q);
        printf("%c : %d\n", temp->ch, temp->freq);
        if (temp->left) enqueue(&q, temp->left);
        if (temp->right) enqueue(&q, temp->right);
    }
}

int main() {
    char str[100];
    printf("Enter the input string: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';  // Remove newline

    struct Node* root = buildTree(str);

    levelOrderTraversal(root);

    return 0;
}
