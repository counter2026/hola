#include <stdio.h>

// Function to find the position of the Least Recently Used (LRU) page
int find_LRU(int time[], int n) {
    int min = time[0], pos = 0; // Initialize min time and position for LRU
    for (int i = 1; i < n; i++) { // Iterate through time array to find minimum
        if (time[i] < min) { // Update min time and position if smaller value found
            min = time[i];
            pos = i;
        }
    }
    return pos; // Return the position of LRU page
}

// Function to calculate page faults using LRU page replacement
int page_faults_LRU(int pages[], int n, int capacity) {
    int frame[capacity]; // Array to hold pages in frames (current memory)
    int time[capacity];  // Array to track the last used time for each page in frame
    int page_faults = 0, counter = 0; // page_faults counts faults, counter tracks time

    // Initialize frames to -1, representing empty slots
    for (int i = 0; i < capacity; i++) {
        frame[i] = -1;
    }

    // Loop through each page in the reference string
    for (int i = 0; i < n; i++) {
        int page = pages[i]; // Get current page from reference string
        int found = 0; // Flag to check if page is already in frame

        // Check if the page is already in any frame slot
        for (int j = 0; j < capacity; j++) {
            if (frame[j] == page) { // If page found in frame
                found = 1;  // Set found flag to true
                time[j] = counter++; // Update last used time for this frame slot
                break; // Break out of the loop as page is already in frame
            }
        }

        // If page is not in frame, it’s a page fault
        if (!found) {
            int pos = -1; // Initialize position to store new page

            // Check if there is an empty slot in frame
            for (int j = 0; j < capacity; j++) {
                if (frame[j] == -1) { // If empty slot found
                    pos = j; // Use this position to store new page
                    break;
                }
            }

            // If no empty slot, find LRU page to replace
            if (pos == -1) {
                pos = find_LRU(time, capacity); // Get position of least recently used page
            }

            // Replace page at pos with new page
            frame[pos] = page;
            time[pos] = counter++; // Update the last used time for the replaced page
            page_faults++; // Increment page faults as a new page was added to frame
        }

        // Display current frame contents after each page reference
        printf("Frame: ");
        for (int j = 0; j < capacity; j++) {
            if (frame[j] == -1)
                printf("- "); // Show '-' for empty slots
            else
                printf("%d ", frame[j]); // Display page number in frame
        }
        printf("\n");
    }

    return page_faults; // Return the total number of page faults
}

int main() {
    int n, capacity;

    // Get the number of pages in the reference string
    printf("Enter the number of pages: ");
    scanf("%d", &n);

    int pages[n]; // Array to store page reference string
    printf("Enter the reference string (page numbers): ");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]); // Input each page number

    // Get the capacity of frames (number of pages that can be in memory at once)
    printf("Enter the frame capacity: ");
    scanf("%d", &capacity);

    // Calculate and display the total page faults using LRU algorithm
    int faults = page_faults_LRU(pages, n, capacity);
    printf("Total page faults: %d\n", faults);

    return 0;
}

/* Example Input:
Enter the number of pages: 7
Enter the reference string (page numbers): 0 1 2 0 3 1 2
Enter the frame capacity: 3
*/
