import java.util.ArrayList;
import java.util.Scanner;

public class ALPLoader {

    // Define memory size for main memory (maximum 256 instructions)
    private static final int MEMORY_SIZE = 256;

    // Main memory to store instructions (ArrayList to hold up to MEMORY_SIZE instructions)
    private static ArrayList<String> mainMemory = new ArrayList<>(MEMORY_SIZE);

    // Method to load ALP instructions into memory
    public static void loadALPToMemory() {
        // Create a Scanner object to read user input from the console
        Scanner scanner = new Scanner(System.in);

        // Pointer to keep track of the current memory address (where to load next instruction)
        int memoryPointer = 0;

        // Prompt the user to start entering instructions
        System.out.println("Enter ALP instructions (type 'END' to stop):");

        // Infinite loop to keep reading instructions until "END" is entered
        while (true) {
            // Ask for the current instruction and display the memory address it's being loaded into
            System.out.print("Instruction " + memoryPointer + ": ");
            String instruction = scanner.nextLine().trim();  // Read instruction and remove leading/trailing spaces

            // If the user enters "END", break the loop to stop entering instructions
            if (instruction.equalsIgnoreCase("END")) {
                break;
            }

            // Check if the memory is full (we can only store up to MEMORY_SIZE instructions)
            if (memoryPointer >= MEMORY_SIZE) {
                // If memory is full, print an error and break the loop
                System.out.println("Error: Main memory is full. Program exceeds available memory.");
                break;
            }

            // Add the instruction to the memory (using the memoryPointer as the index)
            mainMemory.add(instruction);

            // Print a confirmation message showing the instruction has been loaded into the specified memory address
            System.out.println("Loaded '" + instruction + "' into memory address " + memoryPointer);

            // Increment the memoryPointer to load the next instruction at the next memory address
            memoryPointer++;
        }

        // Print a message confirming the program has been successfully loaded into memory
        System.out.println("\nProgram successfully loaded into main memory.");
    }

    // Method to display the contents of main memory
    public static void displayMemory() {
        System.out.println("\nMain Memory Contents:");

        // Loop through each instruction in memory and display it with its memory address
        for (int i = 0; i < mainMemory.size(); i++) {
            System.out.println("Memory Address " + i + ": " + mainMemory.get(i));
        }
    }

    // Main method to execute the ALP loader program
    public static void main(String[] args) {
        loadALPToMemory(); // Load the ALP instructions from user input into memory
        displayMemory(); // Display the contents of main memory after loading
    }
}
