#include <stdio.h>

#define MAX_MEMBERS 10
#define DAYS 30

struct Member {
    char name[50];
    int steps[DAYS];
};

void analyzeSteps(struct Member members[], int n) {
    for (int i = 0; i < n; i++) {
        int count = 0, max = members[i].steps[0];

        for (int j = 0; j < DAYS; j++) {
            if (members[i].steps[j] > 10000)
                count++;
            if (members[i].steps[j] > max)
                max = members[i].steps[j];
        }

        printf("\nMember: %s\n", members[i].name);
        printf("Days > 10,000 steps: %d\n", count);
        printf("Max steps in month: %d\n", max);
    }
}

int main() {
    struct Member members[MAX_MEMBERS];
    int n;

    printf("Enter number of members: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("\nEnter name of member %d: ", i + 1);
        scanf(" %[^\n]", members[i].name); // Reads full name including spaces

        printf("Enter 30 daily step counts:\n");
        for (int j = 0; j < DAYS; j++) {
            printf("Day %d: ", j + 1);
            scanf("%d", &members[i].steps[j]);
        }
    }

    analyzeSteps(members, n);
    return 0;
}

