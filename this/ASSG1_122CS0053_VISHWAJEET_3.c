// Implementation: DFA Simulation (Accepts strings ending in ""01"") 
 
#include <stdio.h>
#include <string.h>

// Function to simulate the DFA
int simulateDFA(const char *input) {
    // DFA states
    // 0: Start state
    // 1: Last character was '0'
    // 2: Last two characters were "01" (accepting state)
    int state = 0;

    // Process each character in the input string
    for (int i = 0; i < strlen(input); i++) {
        char ch = input[i];

        switch (state) {
            case 0: // Start state
                if (ch == '0') {
                    state = 1; // Move to state 1
                } else if (ch == '1') {
                    state = 0; // Remain in state 0
                } else {
                    return 0; // Reject invalid characters
                }
                break;

            case 1: // Last character was '0'
                if (ch == '0') {
                    state = 1; // Remain in state 1
                } else if (ch == '1') {
                    state = 2; // Move to accepting state (last two characters are "01")
                } else {
                    return 0; // Reject invalid characters
                }
                break;

            case 2: // Last two characters were "01" (accepting state)
                if (ch == '0') {
                    state = 1; // Move back to state 1
                } else if (ch == '1') {
                    state = 0; // Move back to state 0
                } else {
                    return 0; // Reject invalid characters
                }
                break;

            default:
                return 0; // Reject for unexpected state
        }
    }

    // Final state check
    return state == 2; // Accept only if in state 2
}

int main() {
    char input[100];

    // Read input string
    printf("Enter the string to be checked: ");
    scanf("%s", input);

    // Simulate DFA and output result
    if (simulateDFA(input)) {
        printf("String is accepted.\n");
    } else {
        printf("String is not accepted.\n");
    }

    return 0;
}
