#include <stdio.h>
#include <string.h>

#define MAX_INSTRUCTIONS 100   // Maximum number of instructions in main memory
#define MAX_LINE_LENGTH 50     // Maximum length of each instruction line

// Function to check for operand errors in each instruction
void check_operand_errors(char main_memory[][MAX_LINE_LENGTH], int instruction_count) {
    // Loop through each instruction in main memory
    for (int i = 0; i < instruction_count; i++) {
        int operand_count = 0;   // Counter for operands in the current instruction
        char *token = strtok(main_memory[i], " ,"); // Tokenize the instruction by spaces and commas

        // Count tokens after the opcode as operands
        while (token != NULL) {
            operand_count++;                     // Increment operand count for each token
            token = strtok(NULL, " ,");          // Continue tokenizing to the next part of the instruction
        }

        // Check if operand count is less than 3 (expecting an opcode + 2 operands)
        if (operand_count < 3) {
            printf("Operand error at address %d: Missing operand(s) in instruction '%s'\n", i, main_memory[i]);
        }
    }
}

int main() {
    // Array representing main memory with instruction strings
    char main_memory[MAX_INSTRUCTIONS][MAX_LINE_LENGTH] = {
        "LOAD R1, 100",     // Correct instruction (opcode + 2 operands)
        "STORE R2",         // Missing operand after 'STORE' (for testing)
        "ADD R1, R2",       // Correct instruction (opcode + 2 operands)
        "SUB R3"            // Missing operand after 'SUB' (for testing)
    };
    int instruction_count = 4;  // Total number of instructions loaded in main memory

    // Call function to check for operand errors in each instruction
    check_operand_errors(main_memory, instruction_count);

    return 0;   // End of program
}
