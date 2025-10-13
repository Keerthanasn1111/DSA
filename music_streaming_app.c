#include <stdio.h>
#include <stdlib.h>

struct Song {
    int songID;
    struct Song* next;
};

// Function to create a new song node
struct Song* createNode(int id) {
    struct Song* newNode = (struct Song*)malloc(sizeof(struct Song));
    newNode->songID = id;
    newNode->next = NULL;
    return newNode;
}

// Function to print the playlist
void printPlaylist(struct Song* head) {
    while (head != NULL) {
        printf("%d -> ", head->songID);
        head = head->next;
    }
    printf("NULL\n");
}

// Function to reverse a segment from m to n
void reversePlaylistSegment(struct Song** head, int m, int n) {
    if (m >= n || *head == NULL) return;

    struct Song *prev = NULL, *curr = *head;
    int pos = 1;

    // Step 1: Reach the m-th node
    while (pos < m && curr != NULL) {
        prev = curr;
        curr = curr->next;
        pos++;
    }

    struct Song* beforeStart = prev;
    struct Song* segmentStart = curr;

    // Step 2: Reverse from m to n
    struct Song* next = NULL;
    prev = NULL;
    while (pos <= n && curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
        pos++;
    }

    // Step 3: Reconnect the reversed segment
    if (beforeStart != NULL)
        beforeStart->next = prev;
    else
        *head = prev;

    segmentStart->next = curr;
}

// Main function to test the reversal
int main() {
   
    int ids[] = {101, 102, 103, 104, 105, 106, 107};
    struct Song* head = NULL;
    struct Song* tail = NULL;

    for (int i = 0; i < 7; i++) {
        struct Song* newNode = createNode(ids[i]);
        if (head == NULL)
            head = tail = newNode;
        else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    printf("Original Playlist:\n");
    printPlaylist(head);

    int m = 3, n = 5;
    reversePlaylistSegment(&head, m, n);

    printf("\nModified Playlist (Reversed from position %d to %d):\n", m, n);
    printPlaylist(head);

    return 0;
}
