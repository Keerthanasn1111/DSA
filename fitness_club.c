#include <stdio.h>
#include <string.h>

#define DAYS 30

// Define structure to store member data
struct Member {
    char name[50];
    int steps[DAYS];
};

// Function to analyze step data
void analyzeSteps(struct Member members[], int n) {
    for (int i = 0; i < n; i++) {
        int count = 0;
        int maxSteps = members[i].steps[0];

        // Count days exceeding 10,000 steps and find max
        for (int j = 0; j < DAYS; j++) {
            if (members[i].steps[j] > 10000)
                count++;
            if (members[i].steps[j] > maxSteps)
                maxSteps = members[i].steps[j];
        }

        // Display results
        printf("\nMember: %s\n", members[i].name);
        printf("Days exceeding 10,000 steps: %d\n", count);
        printf("Maximum steps in a day: %d\n", maxSteps);
    }
}

int main() {
    int n;
    printf("Enter number of members: ");
    scanf("%d", &n);

    struct Member members[n];

    for (int i = 0; i < n; i++) {
        printf("\nEnter name of member %d: ", i + 1);
        scanf("%s", members[i].name);

        printf("Enter step counts for 30 days (separated by space):\n");
        for (int j = 0; j < DAYS; j++) {
            scanf("%d", &members[i].steps[j]);
        }
    }

    printf("\n--- Step Analysis ---\n");
    analyzeSteps(members, n);

    return 0;
}
