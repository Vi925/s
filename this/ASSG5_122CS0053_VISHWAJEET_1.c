// Implementation: Parse Tree Generator (Recursive Descent - C Implementation) 
 
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Node structure for parse tree
typedef struct Node {
    char data;
    struct Node *left, *right;
} Node;

const char *input;
int i = 0;

// Function to create a new tree node
Node* createNode(char data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// Forward declarations
Node* E();
Node* T();
Node* F();

// Function to parse an expression (E -> T {(+|-) T})
Node* E() {
    Node* left = T();  // Start with first term
    while (input[i] == '+' || input[i] == '-') {
        Node* node = createNode(input[i]);
        i++;
        node->left = left;    // Previous tree becomes left child
        node->right = T();    // Parse next term
        left = node;          // The new tree becomes the "left" to allow chaining
    }
    return left;
}

// Function to parse a term (T -> F {(*|/) F})
Node* T() {
    Node* left = F();  // Start with first factor
    while (input[i] == '*' || input[i] == '/') {
        Node* node = createNode(input[i]);
        i++;
        node->left = left;    // Previous tree becomes left child
        node->right = F();    // Parse next factor
        left = node;          // Chain again
    }
    return left;
}

// Function to parse a factor (F -> (E) | id)
Node* F() {
    if (input[i] == '(') {
        i++;
        Node* node = E();
        if (input[i] == ')') {
            i++;
            return node;
        } else {
            printf("Invalid Expression: Missing ')'\n");
            exit(1);
        }
    } else if (isalpha(input[i])) {
        Node* node = createNode(input[i]);
        i++;
        return node;
    } else {
        printf("Invalid Expression: Unexpected character '%c'\n", input[i]);
        exit(1);
    }
}

// Function to print the parse tree in the specified format
void printTree(Node* root, int depth, int isLeft) {
    if (root == NULL) return;

    // Print indentation and connector
    if (depth > 0) {
        for (int j = 0; j < depth - 1; j++) {
            printf("│   ");
        }
        printf("%s── ", isLeft ? "├" : "└");
    }

    // Print current node data
    if (root->left || root->right) {
        printf("(%c)\n", root->data);  // Internal node (operator)
    } else {
        printf("%c\n", root->data);     // Leaf node (operand)
    }

    // Recursively print left and right children
    if (root->left) {
        printTree(root->left, depth + 1, 1);
    }
    if (root->right) {
        printTree(root->right, depth + 1, 0);
    }
}

// Parse the input expression and print result
void parseExpression(const char *expr) {
    input = expr;
    i = 0;

    Node* root = E();

    if (input[i] != '\0') {
        printf("Invalid Expression: Extra characters detected\n");
        exit(1);
    }

    printf("Valid Expression\n");
    printf("Parse Tree:\n");
    printTree(root, 0, 0);
}

// Main function to take input and parse it
int main() {
    char expression[100];
    printf("Enter an arithmetic expression: ");
    scanf("%s", expression);

    parseExpression(expression);
    return 0;
}
