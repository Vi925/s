#include <stdio.h>
#include <string.h>

// Function to simulate the DFA
int simulateDFA(const char *input) {
    // DFA states
    // 0: Start state
    // 1: Odd number of 'a's
    // 2: Even number of 'a's
    // 3: Accepting state
    // 4: Dead state
    int state = 0;

    // Process each character in the input string
    for (int i = 0; i < strlen(input); i++) {
        char ch = input[i];

        switch (state) {
            case 0: // Start state
                if (ch == 'a') {
                    state = 1; // Move to odd 'a' state
                } else if (ch == 'b') {
                    state = 4; // Invalid, as 'b' cannot appear first
                } else {
                    return 0; // Reject invalid characters
                }
                break;

            case 1: // Odd 'a' state
                if (ch == 'a') {
                    state = 2; // Move to even 'a' state
                } else if (ch == 'b') {
                    state = 4; // Invalid, 'b' cannot follow odd 'a's
                } else {
                    return 0; // Reject invalid characters
                }
                break;

            case 2: // Even 'a' state
                if (ch == 'a') {
                    state = 1; // Move to odd 'a' state
                } else if (ch == 'b') {
                    state = 3; // Move to accepting state (b+ starts)
                } else {
                    return 0; // Reject invalid characters
                }
                break;

            case 3: // Accepting state
                if (ch == 'b') {
                    state = 3; // Stay in accepting state for b+
                } else {
                    return 0; // Reject invalid characters
                }
                break;

            case 4: // Dead state
                return 0; // Reject immediately

            default:
                return 0; // Reject for unexpected state
        }
    }

    // Final state check
    return state == 3; // Accept only if in state 3
}

int main() {
    char input[100];

    // Read input string
    printf("Enter the input string: ");
    scanf("%s", input);

    // Simulate DFA and output result
    if (simulateDFA(input)) {
        printf("ACCEPTED\n");
    } else {
        printf("NOT ACCEPTED\n");
    }

    return 0;
}
