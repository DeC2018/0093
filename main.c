#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Helper function to check if a segment is a valid part of an IP address
int isValidSegment(char* s, int start, int end) {
    if (start > end) return 0;
    if (s[start] == '0' && start != end) return 0; // Leading zero check
    int num = 0;
    for (int i = start; i <= end; i++) {
        num = num * 10 + (s[i] - '0');
    }
    return num >= 0 && num <= 255;
}

// Helper function for backtracking
void backtrack(char* s, int start, int segmentCount, char* path, int pathLen, char*** result, int* returnSize) {
    if (segmentCount == 4) {
        if (start == strlen(s)) {
            (*result)[*returnSize] = (char*)malloc((pathLen + 1) * sizeof(char));
            strcpy((*result)[*returnSize], path);
            (*returnSize)++;
        }
        return;
    }

    for (int i = start; i < start + 3 && i < strlen(s); i++) {
        if (isValidSegment(s, start, i)) {
            char temp[20];
            snprintf(temp, sizeof(temp), "%s%s", path, segmentCount > 0 ? "." : "");
            strncat(temp, s + start, i - start + 1);
            backtrack(s, i + 1, segmentCount + 1, temp, strlen(temp), result, returnSize);
        }
    }
}

// Main function to restore IP addresses
char** restoreIpAddresses(char* s, int* returnSize) {
    *returnSize = 0;
    char** result = (char**)malloc(100 * sizeof(char*)); // Allocate memory for results
    char path[20] = ""; // Temporary string to store the current path
    backtrack(s, 0, 0, path, 0, &result, returnSize);
    return result;
}

// Helper function to print the result
void printResult(char** result, int returnSize) {
    printf("[");
    for (int i = 0; i < returnSize; i++) {
        printf("\"%s\"", result[i]);
        if (i + 1 < returnSize) {
            printf(",");
        }
    }
    printf("]\n");
}

// Main function to test the restoreIpAddresses function
int main() {
    // Example 1
    char s1[] = "25525511135";
    int returnSize1;
    printf("Input: s = \"%s\"\n", s1);
    char** result1 = restoreIpAddresses(s1, &returnSize1);
    printf("Output: ");
    printResult(result1, returnSize1);

    // Free allocated memory for Example 1
    for (int i = 0; i < returnSize1; i++) {
        free(result1[i]);
    }
    free(result1);

    // Example 2
    char s2[] = "0000";
    int returnSize2;
    printf("Input: s = \"%s\"\n", s2);
    char** result2 = restoreIpAddresses(s2, &returnSize2);
    printf("Output: ");
    printResult(result2, returnSize2);

    // Free allocated memory for Example 2
    for (int i = 0; i < returnSize2; i++) {
        free(result2[i]);
    }
    free(result2);

    // Example 3
    char s3[] = "101023";
    int returnSize3;
    printf("Input: s = \"%s\"\n", s3);
    char** result3 = restoreIpAddresses(s3, &returnSize3);
    printf("Output: ");
    printResult(result3, returnSize3);

    // Free allocated memory for Example 3
    for (int i = 0; i < returnSize3; i++) {
        free(result3[i]);
    }
    free(result3);

    return 0;
}
