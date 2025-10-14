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

int main() {
    struct Song* head = NULL;
    struct Song* tail = NULL;
    int n;

    printf("Enter number of songs in the playlist: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Playlist cannot be empty!\n");
        return 0;
    }

    printf("Enter %d song IDs:\n", n);
    for (int i = 0; i < n; i++) {
        int id;
        scanf("%d", &id);
        struct Song* newNode = createNode(id);
        if (head == NULL)
            head = tail = newNode;
        else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    printf("\nOriginal Playlist:\n");
    printPlaylist(head);

    int m, p;
    printf("\nEnter start and end positions to reverse (m n): ");
    scanf("%d %d", &m, &p);

    reversePlaylistSegment(&head, m, p);

    printf("\nModified Playlist (Reversed from position %d to %d):\n", m, p);
    printPlaylist(head);

    return 0;
}
