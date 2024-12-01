#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int comp(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    FILE *file;
    char stre[1000];
    char ex[15000] = "";
    file = fopen("input", "r");
    if (file == NULL) {
        printf("File can't be opened");
        return EXIT_FAILURE;
    }

    while (fgets(stre, sizeof(stre), file) != NULL) {
        if (strlen(ex) + strlen(stre) >= sizeof(ex) - 1) {
            printf("Input exceeds buffer size\n");
            fclose(file);
            return EXIT_FAILURE;
        }
        strcat(ex, stre);
    }
    fclose(file);

    int list1[1000];
    int list2[1000];
    int count = 0;

    char *line = strtok(ex, "\n");  // Tokenize by newline
    while (line != NULL && count < 1000) {
        int num1, num2;
        if (sscanf(line, "%d %d", &num1, &num2) == 2) {
            list1[count] = num1;
            list2[count] = num2;
            count++;
        }
        line = strtok(NULL, "\n"); 
    }

    // Sort arrays from lowest to highest
    qsort(list1, count, sizeof(int), comp);
    qsort(list2, count, sizeof(int), comp);

    long totaldiff = 0;
    for (int i = 0; i < count; i++) {
        totaldiff += abs(list1[i] - list2[i]);
    }

    printf("\nTotal Difference: %ld\n", totaldiff);

    // Part 2

    int temp = 0;
    long sim_score = 0;

    for (int i = 0; i < count; i++) {
        temp = 0;
        for (int k = 0; k < count; k++) {
            if (list1[i] == list2[k]) {
                temp++;
            }
        }
        sim_score += list1[i] * temp;
    }

    printf("\nSimiliarity Score: %ld\n", sim_score);

    return 0;
}
