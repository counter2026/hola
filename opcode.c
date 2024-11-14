#include <stdio.h>
#include <string.h>

#define MAX_INSTRUCTIONS 100    // Maximum number of instructions that can be stored in main memory
#define MAX_LINE_LENGTH 50      // Maximum length of each instruction line

// Array of valid opcodes
const char *valid_opcodes[] = {"LOAD", "STORE", "ADD", "SUB", "JMP", "HALT"};
#define NUM_OPCODES (sizeof(valid_opcodes) / sizeof(valid_opcodes[0]))  // Calculate the number of valid opcodes

// Function to check if the given opcode is valid
int is_valid_opcode(const char *opcode) {
    // Loop through the list of valid opcodes
    for (int i = 0; i < NUM_OPCODES; i++) {
        // Compare the input opcode with each valid opcode
        if (strcmp(opcode, valid_opcodes[i]) == 0) {
            return 1;  // Return 1 if a match is found, indicating the opcode is valid
        }
    }
    return 0;  // Return 0 if no match is found, indicating the opcode is invalid
}

// Function to check for opcode errors in each instruction
void check_opcode_errors(char main_memory[][MAX_LINE_LENGTH], int instruction_count) {
    // Loop through each instruction in main memory
    for (int i = 0; i < instruction_count; i++) {
        char opcode[MAX_LINE_LENGTH];  // Buffer to hold the extracted opcode
        sscanf(main_memory[i], "%s", opcode);  // Extract the first word in the instruction as the opcode

        // Check if the extracted opcode is valid
        if (!is_valid_opcode(opcode)) {
            // Print an error message if the opcode is invalid
            printf("Opcode error at address %d: Invalid opcode '%s'\n", i, opcode);
        }
    }
}

int main() {
    // Array representing main memory with instruction strings
    char main_memory[MAX_INSTRUCTIONS][MAX_LINE_LENGTH] = {
        "LOAD R1, 100",        // Valid instruction
        "STOREE R2, 200",      // Invalid opcode for testing
        "ADD R1, R2",          // Valid instruction
        "INVALID_OP R3, 300"   // Invalid opcode for testing
    };
    int instruction_count = 4;  // Total number of instructions in main memory

    // Call function to check for opcode errors in each instruction
    check_opcode_errors(main_memory, instruction_count);

    return 0;  // End of program
}
