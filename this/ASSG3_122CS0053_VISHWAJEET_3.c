#include <stdio.h>
#include <string.h>

#define MAX 100

// Global Variables
char stack[MAX][MAX];  // Stack for parsing
int top = -1;          // Stack pointer
char input[MAX];       // Input string
char tokens[MAX][MAX]; // Tokenized input
int token_index = 0;   // Token index

// Function Prototypes
void push(char *symbol);
void pop(int count);
void tokenize_input();
void shift_reduce_parser();

// Push function
void push(char *symbol)
{
    strcpy(stack[++top], symbol);
}

// Pop function
void pop(int count)
{
    for (int i = 0; i < count; i++)
        if (top >= 0)
            top--;
}

// Tokenize input string
void tokenize_input()
{
    char *token = strtok(input, " ");
    while (token != NULL)
    {
        strcpy(tokens[token_index++], token);
        token = strtok(NULL, " ");
    }
}

// Shift-Reduce Parser
void shift_reduce_parser()
{
    printf("Parsing Actions:\n");

    for (int i = 0; i < token_index; i++)
    {
        printf("Shift %s\n", tokens[i]);
        push(tokens[i]);

        // Reduce F -> id immediately after each id shift
        if (strcmp(stack[top], "id") == 0)
        {
            printf("Reduce F -> id\n");
            strcpy(stack[top], "F");
        }

        // Reduce T -> F only after shifting * and id
        if (top >= 2 && strcmp(stack[top - 1], "*") == 0 &&
            strcmp(stack[top], "F") == 0)
        {
            continue; // Delay reduction of T -> F
        }

        // Reduce T -> F (After both `F`s have been shifted)
        if (top >= 0 && strcmp(stack[top], "F") == 0)
        {
            printf("Reduce T -> F\n");
            strcpy(stack[top], "T");

            // Reduce E -> T immediately if applicable
            if (top == 0 && strcmp(stack[top], "T") == 0)
            {
                printf("Reduce E -> T\n");
                strcpy(stack[top], "E");
            }
        }
    }

    // Apply precedence-based reductions
    while (top >= 0)
    {
        if (top >= 2 && strcmp(stack[top - 2], "T") == 0 &&
            strcmp(stack[top - 1], "*") == 0 &&
            strcmp(stack[top], "F") == 0)
        {
            printf("Reduce T -> T * F\n");
            pop(2);
            strcpy(stack[top], "T");
        }
        else if (top >= 2 && strcmp(stack[top - 2], "E") == 0 &&
                 strcmp(stack[top - 1], "+") == 0 &&
                 strcmp(stack[top], "T") == 0)
        {
            printf("Reduce E -> E + T\n");
            pop(2);
            strcpy(stack[top], "E");
        }
        else
        {
            break; // Stop reducing when no rules apply
        }
    }

    // Final Validation
    if (top == 0 && strcmp(stack[top], "E") == 0)
    {
        printf("Valid Expression\n");
    }
    else
    {
        printf("Invalid Expression\n");
    }
}

// Main Function
int main()
{
    printf("Enter input string: ");
    fgets(input, MAX, stdin);
    input[strcspn(input, "\n")] = 0; // Remove newline

    tokenize_input();
    shift_reduce_parser();

    return 0;
}