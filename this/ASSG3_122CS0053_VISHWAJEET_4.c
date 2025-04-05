// Implementation: LR(1) Parser (Table-Driven - C Implementation) 
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STACK_SIZE 100
#define MAX_TOKEN_SIZE 20
#define MAX_INPUT_SIZE 200

// Terminal symbols: id, +, *, (, ), $
enum { ID, PLUS, TIMES, LPAREN, RPAREN, DOLLAR, NUM_TERMINALS };
// Nonterminals: E, T, F
enum { NON_E, NON_T, NON_F, NUM_NONTERMINALS };

// Production rules (numbered 1 to 6)
// 1: E -> E + T   (length 3)
// 2: E -> T       (length 1)
// 3: T -> T * F   (length 3)
// 4: T -> F       (length 1)
// 5: F -> ( E )   (length 3)
// 6: F -> id      (length 1)
typedef struct {
    int lhs;         // left-hand side (NON_E, NON_T, NON_F)
    int rhs_len;     // length of the right-hand side
    const char *prodStr; // production string for printing
} Production;

// Note: Productions 1 and 3 have been augmented with operator precedence notes.
Production productions[] = {
    {0, 0, ""}, // dummy production so indexing starts at 1.
    {NON_E, 3, "E -> E + T (Operator precedence: '+' is lower than '*' and left-associative)"},
    {NON_E, 1, "E -> T"},
    {NON_T, 3, "T -> T * F (Operator precedence: '*' binds tighter than '+')"},
    {NON_T, 1, "T -> F"},
    {NON_F, 3, "F -> ( E )"},
    {NON_F, 1, "F -> id"}
};

// Action types for the LR parsing table.
enum { ACT_ERROR, ACT_SHIFT, ACT_REDUCE, ACT_ACCEPT };

typedef struct {
    int action; // ACT_SHIFT, ACT_REDUCE, ACT_ACCEPT, ACT_ERROR
    int number; // for shift: new state; for reduce: production number.
} Action;

// There are 12 states (numbered 0..11) in this table.
#define NUM_STATES 12

// ACTION table: rows are states, columns are terminals (id, +, *, (, ), $).
Action actionTable[NUM_STATES][NUM_TERMINALS] = {
    // state 0:
    { {ACT_SHIFT, 5}, {ACT_ERROR, 0},     {ACT_ERROR, 0},     {ACT_SHIFT, 4}, {ACT_ERROR, 0},     {ACT_ERROR, 0} },
    // state 1:
    { {ACT_ERROR, 0}, {ACT_SHIFT, 6},       {ACT_ERROR, 0},     {ACT_ERROR, 0}, {ACT_ERROR, 0},     {ACT_ACCEPT, 0} },
    // state 2:
    { {ACT_ERROR, 0}, {ACT_REDUCE, 2},      {ACT_SHIFT, 7},     {ACT_ERROR, 0}, {ACT_REDUCE, 2},    {ACT_REDUCE, 2} },
    // state 3:
    { {ACT_ERROR, 0}, {ACT_REDUCE, 4},      {ACT_REDUCE, 4},    {ACT_ERROR, 0}, {ACT_REDUCE, 4},    {ACT_REDUCE, 4} },
    // state 4:
    { {ACT_SHIFT, 5}, {ACT_ERROR, 0},       {ACT_ERROR, 0},     {ACT_SHIFT, 4}, {ACT_ERROR, 0},     {ACT_ERROR, 0} },
    // state 5:
    { {ACT_ERROR, 0}, {ACT_REDUCE, 6},      {ACT_REDUCE, 6},    {ACT_ERROR, 0}, {ACT_REDUCE, 6},    {ACT_REDUCE, 6} },
    // state 6:
    { {ACT_SHIFT, 5}, {ACT_ERROR, 0},       {ACT_ERROR, 0},     {ACT_SHIFT, 4}, {ACT_ERROR, 0},     {ACT_ERROR, 0} },
    // state 7:
    { {ACT_SHIFT, 5}, {ACT_ERROR, 0},       {ACT_ERROR, 0},     {ACT_SHIFT, 4}, {ACT_ERROR, 0},     {ACT_ERROR, 0} },
    // state 8:
    { {ACT_ERROR, 0}, {ACT_SHIFT, 6},       {ACT_ERROR, 0},     {ACT_ERROR, 0}, {ACT_SHIFT, 11},    {ACT_ERROR, 0} },
    // state 9:
    { {ACT_ERROR, 0}, {ACT_REDUCE, 1},      {ACT_SHIFT, 7},     {ACT_ERROR, 0}, {ACT_REDUCE, 1},    {ACT_REDUCE, 1} },
    // state 10:
    { {ACT_ERROR, 0}, {ACT_REDUCE, 3},      {ACT_REDUCE, 3},    {ACT_ERROR, 0}, {ACT_REDUCE, 3},    {ACT_REDUCE, 3} },
    // state 11:
    { {ACT_ERROR, 0}, {ACT_REDUCE, 5},      {ACT_REDUCE, 5},    {ACT_ERROR, 0}, {ACT_REDUCE, 5},    {ACT_REDUCE, 5} }
};

// GOTO table: rows are states, columns are nonterminals (E, T, F).
// If no valid transition, use -1.
int gotoTable[NUM_STATES][NUM_NONTERMINALS] = {
    /* state 0: */ { 1, 2, 3 },
    /* state 1: */ { -1, -1, -1 },
    /* state 2: */ { -1, -1, -1 },
    /* state 3: */ { -1, -1, -1 },
    /* state 4: */ { 8, 2, 3 },
    /* state 5: */ { -1, -1, -1 },
    /* state 6: */ { -1, 9, 3 },
    /* state 7: */ { -1, -1, 10 },
    /* state 8: */ { -1, -1, -1 }, 
    /* state 9: */ { -1, -1, -1 },
    /* state 10: */ { -1, -1, -1 },
    /* state 11: */ { -1, -1, -1 }
};

// Helper: map a token string to a terminal symbol index.
int tokenToTerminal(const char *token) {
    if(strcmp(token, "id") == 0)
        return ID;
    else if(strcmp(token, "+") == 0)
        return PLUS;
    else if(strcmp(token, "*") == 0)
        return TIMES;
    else if(strcmp(token, "(") == 0)
        return LPAREN;
    else if(strcmp(token, ")") == 0)
        return RPAREN;
    else if(strcmp(token, "$") == 0)
        return DOLLAR;
    return -1;
}

// The parsing stack holds state numbers.
int stack[MAX_STACK_SIZE];
int topStack = 0; // stack[0] is the initial state.

void pushState(int state) {
    stack[++topStack] = state;
}

void popState(int count) {
    topStack -= count;
}

int main() {
    char inputLine[MAX_INPUT_SIZE];
    char tokensInput[50][MAX_TOKEN_SIZE];
    int tokenCount = 0;

    printf("Enter input string: ");
    fgets(inputLine, MAX_INPUT_SIZE, stdin);
    inputLine[strcspn(inputLine, "\n")] = '\0';

    // Tokenize input (assume tokens are space-separated).
    char *token = strtok(inputLine, " ");
    while(token != NULL) {
        strcpy(tokensInput[tokenCount++], token);
        token = strtok(NULL, " ");
    }
    // Append end marker "$".
    strcpy(tokensInput[tokenCount++], "$");

    // Initialize the parsing stack with state 0.
    topStack = 0;
    stack[0] = 0;
    int ip = 0; // input pointer

    // Begin LR parsing loop.
    while (1) {
        int currentState = stack[topStack];
        int currentTerminal = tokenToTerminal(tokensInput[ip]);
        if (currentTerminal == -1) {
            printf("Invalid token: %s\n", tokensInput[ip]);
            exit(1);
        }
        Action act = actionTable[currentState][currentTerminal];
        if (act.action == ACT_SHIFT) {
            printf("Shift %s\n", tokensInput[ip]);
            // If the token is an operator, print a note about operator precedence.
            if (currentTerminal == PLUS) {
                printf("Note: '+' has lower precedence than '*'\n");
            } else if (currentTerminal == TIMES) {
                printf("Note: '*' binds tighter than '+'\n");
            }
            pushState(act.number);
            ip++;
        } else if (act.action == ACT_REDUCE) {
            Production prod = productions[act.number];
            printf("Reduce %s\n", prod.prodStr);
            // Pop states according to production length.
            popState(prod.rhs_len);
            int stateAfterPop = stack[topStack];
            int nextState = gotoTable[stateAfterPop][prod.lhs];
            if (nextState == -1) {
                printf("Goto error.\n");
                exit(1);
            }
            pushState(nextState);
        } else if (act.action == ACT_ACCEPT) {
            printf("Valid Expression\n");
            break;
        } else { // ACT_ERROR
            printf("Invalid Expression\n");
            break;
        }
    }
    return 0;
}
