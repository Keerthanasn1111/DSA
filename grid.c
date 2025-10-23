#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROWS 100
#define MAX_COLS 100

int main() {
    int m, n;
    char grid[MAX_ROWS][MAX_COLS];
    char word[101];
    int lenw;
    int found = 0;

    // Read m and n with prompts
    printf("Enter number of rows: ");
    if (scanf("%d", &m) != 1) {
        fprintf(stderr, "Error reading number of rows\n");
        return 1;
    }
    printf("Enter number of columns: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Error reading number of columns\n");
        return 1;
    }

    // Read the grid with prompt: m strings (can be entered space-separated on one line)
    printf("Enter the grid rows (space-separated on one line): ");
    for (int i = 0; i < m; i++) {
        if (scanf("%s", grid[i]) != 1) {
            fprintf(stderr, "Error reading grid row %d\n", i + 1);
            return 1;
        }
        if (strlen(grid[i]) != n) {
            fprintf(stderr, "Invalid grid row length for row %d (expected %d characters)\n", i + 1, n);
            return 1;
        }
    }

    // Display the grid in grid format
    printf("Grid:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%c ", grid[i][j]);
        }
        printf("\n");
    }

    // Read the word with prompt
    printf("Enter the target word: ");
    if (scanf("%s", word) != 1) {
        fprintf(stderr, "Error reading target word\n");
        return 1;
    }
    lenw = strlen(word);

    // Horizontal search (left to right)
    for (int i = 0; i < m; i++) {
        for (int j = 0; j <= n - lenw; j++) {
            int match = 1;
            for (int k = 0; k < lenw; k++) {
                if (grid[i][j + k] != word[k]) {
                    match = 0;
                    break;
                }
            }
            if (match) {
                printf("Start: (%d, %d) End: (%d, %d)\n", i, j, i, j + lenw - 1);
                found = 1;
            }
        }
    }

    // Vertical search (top to bottom)
    for (int j = 0; j < n; j++) {
        for (int i = 0; i <= m - lenw; i++) {
            int match = 1;
            for (int k = 0; k < lenw; k++) {
                if (grid[i + k][j] != word[k]) {
                    match = 0;
                    break;
                }
            }
            if (match) {
                printf("Start: (%d, %d) End: (%d, %d)\n", i, j, i + lenw - 1, j);
                found = 1;
            }
        }
    }

    if (!found) {
        printf("Word not found\n");
    }

    return 0;
}
