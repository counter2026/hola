#include <stdio.h>

#define MAX_FRAMES 10 // Defines the maximum number of frames available in memory

// Function to find the optimal frame to replace based on future usage
int findOptimal(int frames[], int frameCount, int pages[], int pageCount, int currentIndex) {
    int farthest = currentIndex; // Tracks the farthest future use of a page
    int indexToReplace = -1;     // Stores the index of the frame to be replaced

    // Loop through each frame to determine which page will be used farthest in the future
    for (int i = 0; i < frameCount; i++) {
        int j; // Loop variable to check future use of pages in the reference string
        for (j = currentIndex; j < pageCount; j++) {
            if (frames[i] == pages[j]) { // If the page in the current frame is found in future pages
                if (j > farthest) {      // Update if this page is used farther in the future
                    farthest = j;        // Set the farthest usage position
                    indexToReplace = i;  // Set the index of this frame as the one to replace
                }
                break; // Page will be used again in the future, so break inner loop
            }
        }
        // If the frame’s page is never used again in the future, select it for replacement
        if (j == pageCount) {
            return i; // Return the index of the frame to replace immediately
        }
    }

    // If all pages are used in the future, replace the one used the farthest away
    return (indexToReplace != -1) ? indexToReplace : 0;
}

// Function to check if a page is already loaded in the frames
int isPageInFrames(int frames[], int frameCount, int page) {
    for (int i = 0; i < frameCount; i++) {
        if (frames[i] == page) { // If the page is found in any frame
            return 1; // Return true (1) to indicate page is in frames
        }
    }
    return 0; // Return false (0) to indicate page is not in frames
}

int main() {
    int frameCount, pageCount; // Number of frames and pages in the reference string
    int pageFaults = 0;        // Counter for page faults (when a page is not in frames)

    // Input the number of frames (memory slots) available
    printf("Enter the number of frames: ");
    scanf("%d", &frameCount);

    // Input the total number of pages in the reference string
    printf("Enter the number of pages in the reference string: ");
    scanf("%d", &pageCount);

    // Input the reference string (sequence of page requests)
    int pages[pageCount]; // Array to hold the reference string
    printf("Enter the reference string (space-separated): ");
    for (int i = 0; i < pageCount; i++) {
        scanf("%d", &pages[i]); // Store each page request in the array
    }

    // Initialize all frames to -1 to indicate they are empty initially
    int frames[MAX_FRAMES]; // Array representing frames in memory
    for (int i = 0; i < frameCount; i++) {
        frames[i] = -1; // Set each frame to empty (-1 means empty)
    }

    // Loop through each page in the reference string
    for (int i = 0; i < pageCount; i++) {
        int currentPage = pages[i]; // Current page request from reference string

        // Check if the current page is already in any of the frames
        if (!isPageInFrames(frames, frameCount, currentPage)) {
            // Page fault occurs if the page is not found in any frame
            int indexToReplace = findOptimal(frames, frameCount, pages, pageCount, i); // Get index of frame to replace
            frames[indexToReplace] = currentPage; // Replace the page in selected frame with the current page
            pageFaults++; // Increment the page fault counter
        }
    }

    // Output the total number of page faults encountered
    printf("\nTotal Page Faults: %d\n", pageFaults);

    return 0;
}
