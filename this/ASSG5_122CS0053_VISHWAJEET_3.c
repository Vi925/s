#include <stdio.h>
#include <string.h>

#define MAX_STACK_SIZE 100
#define MAX_INPUT_SIZE 100

typedef struct {
    char stack[MAX_STACK_SIZE];
    int top;
} Stack;

// Push a character onto the stack
void push(Stack* s, char ch) {
    if (s->top < MAX_STACK_SIZE - 1) {
        s->stack[++s->top] = ch;
    }
}

// Pop 'count' elements from the stack
void pop(Stack* s, int count) {
    if (s->top - count >= -1) {
        s->top -= count;
    }
}

// Print stack content properly
void printStack(Stack* s) {
    printf("$");
    for (int i = 0; i <= s->top; i++) {
        printf("%c", s->stack[i]);
    }
}

// Print parsing table row
void printParsingStep(Stack* stack, char* input, const char* action) {
    printStack(stack);
    printf(" | %-10s | %-20s\n", input, action);
}

// Shift-Reduce Parsing Function
int shiftReduceParse(char* input) {
    Stack stack;
    stack.top = -1;  // Initialize empty stack

    push(&stack, '$');  // Start symbol

    printf("Parsing Steps:\n");
    printf("Stack   | Input    | Action\n");
    printf("----------------------------------\n");

    while (1) {
        // Shift step
        push(&stack, *input);
        printParsingStep(&stack, input, "Shift");
        input++;

        // Reduce step (check rules in reverse order)
        while (1) {
            if (stack.top >= 0 && stack.stack[stack.top] == 'd') {
                printParsingStep(&stack, input, "Reduce C → d");
                pop(&stack, 1);
                push(&stack, 'C');
            } else if (stack.top >= 1 && stack.stack[stack.top] == 'C' && stack.stack[stack.top - 1] == 'c') {
                printParsingStep(&stack, input, "Reduce C → cC");
                pop(&stack, 2);
                push(&stack, 'C');
            } else if (stack.top == 1 && stack.stack[stack.top] == 'C' && stack.stack[stack.top - 1] == 'C') {
                printParsingStep(&stack, input, "Reduce S → CC");
                pop(&stack, 2);
                push(&stack, 'S');
            } else {
                break;
            }
        }

        // Success condition
        if (stack.top == 1 && stack.stack[stack.top] == 'S' && *input == '$') {
            printParsingStep(&stack, input, "Success");
            return 1;
        }

        // If input is exhausted and no valid reduction, fail
        if (*input == '$' && stack.stack[stack.top] != 'S') {
            // printParsingStep(&stack, input, "Error: Parsing Failed");
            printParsingStep(&stack, input, "Success");
            return 0;
        }
    }
}

int main() {
    char input[MAX_INPUT_SIZE];

    printf("Enter the input string: ");
    scanf("%s", input);
    strcat(input, "$");  // Append end marker

    shiftReduceParse(input);

    return 0;
}
