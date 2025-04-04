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

// Pop the top element from the stack
void pop(Stack* s, int count) {
    if (s->top - count >= -1) {
        s->top -= count;
    }
}

// Print parsing steps in the requested format
void printParsingStep(const char* action) {
    printf("%s\n", action);
}

// Shift-Reduce Parsing Function
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
                printParsingStep("Reduce F → id");
                pop(&stack, 1);
                push(&stack, "F");
            } else if (stack.top >= 0 && strcmp(stack.stack[stack.top], "F") == 0) {
                printParsingStep("Reduce T → F");
                pop(&stack, 1);
                push(&stack, "T");
            } else if (stack.top >= 2 && strcmp(stack.stack[stack.top], "T") == 0 &&
                       strcmp(stack.stack[stack.top - 1], "*") == 0 &&
                       strcmp(stack.stack[stack.top - 2], "T") == 0) {
                printParsingStep("Reduce T → T * F");
                pop(&stack, 3);
                push(&stack, "T");
            } else if (stack.top >= 2 && strcmp(stack.stack[stack.top], "T") == 0 &&
                       strcmp(stack.stack[stack.top - 1], "+") == 0 &&
                       strcmp(stack.stack[stack.top - 2], "E") == 0) {
                printParsingStep("Reduce E → E + T");
                pop(&stack, 3);
                push(&stack, "E");
            } else {
                break;
            }
        }

        // Success condition
        if (stack.top == 1 && strcmp(stack.stack[stack.top], "E") == 0 && inputIndex == tokenCount) {
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
