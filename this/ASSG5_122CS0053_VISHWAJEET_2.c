// Implementation: Predictive Parser (LL(1) Simulation - C Implementation) 
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 100
#define MAX_INPUT_SIZE 100

typedef struct {
    char stack[MAX_STACK_SIZE][MAX_INPUT_SIZE];
    int top;
} Stack;

void push(Stack* s, const char* str) {
    if (s->top < MAX_STACK_SIZE - 1) {
        strcpy(s->stack[++s->top], str);
    }
}

void pop(Stack* s) {
    if (s->top >= 0) {
        s->top--;
    }
}

char* top(Stack* s) {
    return s->stack[s->top];
}

void printParsingStep(Stack* stack, char* input, char* action) {
    // Print the stack content
    printf(" %-18s | %-16s | %-18s \n", top(stack), input, action);
}

void predictiveParsing(char* input) {
    Stack stack;
    stack.top = -1;

    push(&stack, "$");  // End marker
    push(&stack, "E");  // Start Symbol

    // printf("+------------------+----------------+--------------------+\n");
    printf("   Stack            | Input          | Action             \n");
    printf(" +------------------+----------------+--------------------+\n");

    while (stack.top >= 0) {
        char* topSymbol = top(&stack);
        char* nextInput = input;

        if (strcmp(topSymbol, "$") == 0 && strcmp(nextInput, "$") == 0) {
            printf("Success: Input is valid.\n");
            break;
        }

        // Terminal Matching
        if ((strcmp(topSymbol, "id") == 0 && strncmp(nextInput, "id", 2) == 0) ||
            (strlen(topSymbol) == 1 && topSymbol[0] == nextInput[0])) {
            printParsingStep(&stack, input, "Match");
            pop(&stack);
            input += (strcmp(topSymbol, "id") == 0) ? 2 : 1;  // Advance input pointer
        }
        // Non-Terminal Expansion
        else {
            pop(&stack);
            if (strcmp(topSymbol, "E") == 0) {
                printParsingStep(&stack, input, "Expand E → T E'");
                push(&stack, "E'");
                push(&stack, "T");
            } else if (strcmp(topSymbol, "E'") == 0) {
                if (nextInput[0] == '+') {
                    printParsingStep(&stack, input, "Expand E' → + T E'");
                    push(&stack, "E'");
                    push(&stack, "T");
                    push(&stack, "+");
                } else {
                    printParsingStep(&stack, input, "Reduce E' → ε");
                }
            } else if (strcmp(topSymbol, "T") == 0) {
                printParsingStep(&stack, input, "Expand T → F T'");
                push(&stack, "T'");
                push(&stack, "F");
            } else if (strcmp(topSymbol, "T'") == 0) {
                if (nextInput[0] == '*') {
                    printParsingStep(&stack, input, "Expand T' → * F T'");
                    push(&stack, "T'");
                    push(&stack, "F");
                    push(&stack, "*");
                } else {
                    printParsingStep(&stack, input, "Reduce T' → ε");
                }
            } else if (strcmp(topSymbol, "F") == 0) {
                if (strncmp(nextInput, "id", 2) == 0) {
                    printParsingStep(&stack, input, "Expand F → id");
                    push(&stack, "id");
                } else if (nextInput[0] == '(') {
                    printParsingStep(&stack, input, "Expand F → (E)");
                    push(&stack, ")");
                    push(&stack, "E");
                    push(&stack, "(");
                } else {
                    printParsingStep(&stack, input, "Error: Unexpected token");
                    return;
                }
            } else {
                printParsingStep(&stack, input, "Error: Parsing Failed");
                return;
            }
        }
    }

    // printf("+------------------+----------------+--------------------+\n");
}

int main() {
    char input[MAX_INPUT_SIZE];

    printf("Enter the arithmetic expression: ");
    scanf("%s", input);
    strcat(input, "$");  // End marker for parsing

    predictiveParsing(input);

    return 0;
}
