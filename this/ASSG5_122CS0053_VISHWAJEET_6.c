// Implementation: Parser Error Recovery (Panic Mode - C Implementation) 
 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100
#define MAX_INPUT_SIZE 100

// Panic Mode Recovery - Skip invalid tokens until a valid token is found
int panicModeRecovery(char inputTokens[][MAX_INPUT_SIZE], int* inputIndex, int tokenCount) {
    printf("Error Recovery: Skipping '%s'\n", inputTokens[*inputIndex]);

    (*inputIndex)++;  // Skip current erroneous token

    // Synchronizing tokens: valid starting points for expressions (id, ()
    while (*inputIndex < tokenCount &&
           strcmp(inputTokens[*inputIndex], "id") != 0 &&
           strcmp(inputTokens[*inputIndex], "(") != 0) {
        printf("Error Recovery: Skipping '%s'\n", inputTokens[*inputIndex]);
        (*inputIndex)++;
    }

    return *inputIndex < tokenCount; // Return true if found a valid recovery point
}

// LL(1) / LR(1) Parsing with Error Recovery
int parseExpression(char inputTokens[][MAX_INPUT_SIZE], int tokenCount) {
    int inputIndex = 0;
    int errorOccurred = 0;

    while (inputIndex < tokenCount) {
        // Error Detection: Check for misplaced operators
        if ((strcmp(inputTokens[inputIndex], "+") == 0 || strcmp(inputTokens[inputIndex], "*") == 0) &&
            (inputIndex == 0 || strcmp(inputTokens[inputIndex - 1], "+") == 0 ||
             strcmp(inputTokens[inputIndex - 1], "*") == 0)) {
            printf("Syntax Error at position %d: Unexpected token '%s'\n", inputIndex + 1, inputTokens[inputIndex]);
            errorOccurred = 1;
            if (!panicModeRecovery(inputTokens, &inputIndex, tokenCount)) {
                return 0;
            }
            continue;  // Resume parsing after error recovery
        }
        inputIndex++;
    }

    if (errorOccurred)
        printf("Valid Parsing Resumed\n");

    return 1;
}

// Tokenize input string
void tokenizeInput(char* input, char tokens[][MAX_INPUT_SIZE], int* tokenCount) {
    char* token = strtok(input, " ");
    while (token) {
        strcpy(tokens[*tokenCount], token);
        (*tokenCount)++;
        token = strtok(NULL, " ");
    }
}

int main() {
    char input[MAX_INPUT_SIZE];
    char tokens[MAX_INPUT_SIZE][MAX_INPUT_SIZE];
    int tokenCount = 0;

    fgets(input, MAX_INPUT_SIZE, stdin);
    input[strcspn(input, "\n")] = 0; // Remove newline

    tokenizeInput(input, tokens, &tokenCount);

    parseExpression(tokens, tokenCount);

    return 0;
}
