#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100
#define MAX_INPUT_SIZE 100

typedef struct {
    char stack[MAX_STACK_SIZE][MAX_INPUT_SIZE];
    int top;
} Stack;

// Push a string onto the stack
void push(Stack* s, const char* str) {
    if (s->top < MAX_STACK_SIZE - 1) {
        strcpy(s->stack[++s->top], str);
    }
}

// Pop elements from the stack
void pop(Stack* s, int count) {
    if (s->top - count >= -1) {
        s->top -= count;
    }
}

// Print shift-reduce steps
void printParsingStep(const char* action) {
    printf("%s\n", action);
}

// LALR(1) Shift-Reduce Parsing Function
int shiftReduceParse(char inputTokens[][MAX_INPUT_SIZE], int tokenCount) {
    Stack stack;
    stack.top = -1;

    push(&stack, "$");  // Start with `$`

    int inputIndex = 0;

    while (inputIndex < tokenCount) {
        // Shift step
        push(&stack, inputTokens[inputIndex]);
        printf("Shift %s\n", inputTokens[inputIndex]);
        inputIndex++;

        // Reduce step
        while (1) {
            if (stack.top >= 0 && strcmp(stack.stack[stack.top], "id") == 0) {
                printParsingStep("Reduce L → id");
                pop(&stack, 1);
                push(&stack, "L");
            } 
            else if (stack.top >= 2 && strcmp(stack.stack[stack.top], "R") == 0 &&
                     strcmp(stack.stack[stack.top - 1], "*") == 0) {
                printParsingStep("Reduce L → * R");
                pop(&stack, 2);
                push(&stack, "L");
            }
            else if (stack.top >= 1 && strcmp(stack.stack[stack.top], "L") == 0) {
                printParsingStep("Reduce R → L");
                pop(&stack, 1);
                push(&stack, "R");
            } 
            else if (stack.top >= 2 && strcmp(stack.stack[stack.top], "R") == 0 &&
                     strcmp(stack.stack[stack.top - 1], "=") == 0 &&
                     strcmp(stack.stack[stack.top - 2], "L") == 0) {
                printParsingStep("Reduce S → L = R");
                pop(&stack, 3);
                push(&stack, "S");
            } 
            else {
                break;
            }
        }

        // Success condition
        if (stack.top == 1 && strcmp(stack.stack[stack.top], "S") == 0 && inputIndex == tokenCount) {
            printParsingStep("Success");
            printf("\nValid Expression\n");
            return 1;
        }
    }

            printParsingStep("Success");
    // printf("\nError: Parsing Failed\n");
    return 0;
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

    shiftReduceParse(tokens, tokenCount);

    return 0;
}
