#include <stdio.h>
#include <stdlib.h>

// Function to copy the contents of a file character by character
void copyFileCharacterByCharacter(const char *sourceFile, const char *destFile) {
    // Open the source file in read mode and the destination file in write mode
    FILE *src = fopen(sourceFile, "r");
    FILE *dest = fopen(destFile, "w");
    
    // Check if the files were successfully opened
    if (src == NULL || dest == NULL) {
        perror("Error opening file");  // Print error if any file cannot be opened
        exit(1);  // Exit the program if there is an error
    }
    
    char ch;  // Variable to hold each character while copying
    
    // Copy the content of the source file character by character
    while ((ch = fgetc(src)) != EOF) {  // Read one character at a time until EOF is reached
        fputc(ch, dest);  // Write the character to the destination file
    }
    
    // Indicate that the file has been copied successfully
    printf("File copied character by character successfully.\n");
    
    // Close both the source and destination files
    fclose(src);
    fclose(dest);
}


// Function to copy the contents of a file line by line
void copyFileLineByLine(const char *sourceFile, const char *destFile) {
    // Open the source file in read mode and the destination file in write mode
    FILE *src = fopen(sourceFile, "r");
    FILE *dest = fopen(destFile, "w");
    
    // Check if the files were successfully opened
    if (src == NULL || dest == NULL) {
        perror("Error opening file");  // Print error if any file cannot be opened
        exit(1);  // Exit the program if there is an error
    }
    
    char line[1024];  // Array to store each line from the source file
    
    // Copy the content of the source file line by line
    while (fgets(line, sizeof(line), src) != NULL) {  // Read one line at a time
        fputs(line, dest);  // Write the line to the destination file
    }
    
    // Indicate that the file has been copied successfully
    printf("File copied line by line successfully.\n");
    
    // Close both the source and destination files
    fclose(src);
    fclose(dest);
}


int main() {
    // Declare variables to store file names for source and destination files
    char sourceFile[100];  // Holds the name of the source file
    char destFileChar[100];  // Holds the name of the destination file for character-by-character copy
    char destFileLine[100];  // Holds the name of the destination file for line-by-line copy

    // Prompt the user to enter the name of the source file
    printf("Enter the name of the source file: ");
    scanf("%s", sourceFile);  // Read the source file name from user input

    // Prompt the user to enter the name of the destination file for character-by-character copy
    printf("Enter the name of the destination file for character-by-character copy: ");
    scanf("%s", destFileChar);  // Read the destination file name for character-by-character copy

    // Prompt the user to enter the name of the destination file for line-by-line copy
    printf("Enter the name of the destination file for line-by-line copy: ");
    scanf("%s", destFileLine);  // Read the destination file name for line-by-line copy
    
    // Call the function to copy the file character by character
    printf("\nCopying file character by character...\n");
    copyFileCharacterByCharacter(sourceFile, destFileChar);  // Pass the source and destination file names
    
    // Call the function to copy the file line by line
    printf("\nCopying file line by line...\n");
    copyFileLineByLine(sourceFile, destFileLine);  // Pass the source and destination file names

    return 0;  // Return 0 to indicate the successful execution of the program
}


//Enter the name of the source file: copy.txt
//Enter the name of the destination file for character-by-character copy: char_copy
//Enter the name of the destination file for line-by-line copy: line_copy

