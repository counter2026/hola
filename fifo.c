#include <stdio.h>

#define MAX_FRAMES 10 // Define the maximum number of frames in the memory

// Function to check if a page is already in one of the frames
int isPageInFrames(int frames[], int frameCount, int page) {
    for (int i = 0; i < frameCount; i++) {
        if (frames[i] == page) { // If the page is found in the frames
            return 1; // Page is already in the frames
        }
    }
    return 0; // Page is not in the frames
}

int main() {
    int frameCount, pageCount;
    int pageFaults = 0; // Variable to count the number of page faults
    int nextFrameToReplace = 0; // Pointer to track the next frame to replace in a circular manner

    // Input: Number of frames in the memory
    printf("Enter the number of frames: ");
    scanf("%d", &frameCount);

    // Input: Number of pages in the reference string
    printf("Enter the number of pages in the reference string: ");
    scanf("%d", &pageCount);

    int pages[pageCount]; // Array to hold the reference string (sequence of page requests)
    printf("Enter the reference string (space-separated): ");
    for (int i = 0; i < pageCount; i++) {
        scanf("%d", &pages[i]); // Read each page in the reference string
    }

    // Initialize frames to -1, indicating that they are empty
    int frames[MAX_FRAMES]; // Array to represent the frames in memory
    for (int i = 0; i < frameCount; i++) {
        frames[i] = -1; // Mark all frames as empty (-1)
    }

    // Process each page in the reference string
    for (int i = 0; i < pageCount; i++) {
        int currentPage = pages[i]; // Current page being accessed

        // Check if the current page is already in one of the frames
        if (!isPageInFrames(frames, frameCount, currentPage)) {
            // If the page is not in frames, a page fault occurs
            frames[nextFrameToReplace] = currentPage; // Replace the page at the frame indicated by nextFrameToReplace
            pageFaults++; // Increment the page fault count
            nextFrameToReplace = (nextFrameToReplace + 1) % frameCount; // Move to the next frame in a circular manner
        }
    }

    // Output: Total number of page faults
    printf("\nTotal Page Faults: %d\n", pageFaults);

    return 0; // Return 0 to indicate successful execution
}

/* Sample Input:
Enter the number of frames: 3
Enter the number of pages in the reference string: 6
Enter the reference string (space-separated): 1 2 3 4 5 3

Sample Output:
Total Page Faults: 5
*/
