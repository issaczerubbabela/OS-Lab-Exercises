#include <stdio.h>

// Function to find the index of the least recently used page in frames
int findLRU(int time[], int n) {
    int i, minimum = time[0], pos = 0;

    for (i = 1; i < n; ++i) {
        if (time[i] < minimum) {
            minimum = time[i];
            pos = i;
        }
    }
    return pos;
}

int main() {
    int no_of_frames, no_of_pages, frames[10], pages[30], counter = 0, time[10], i, j, pos, faults = 0;

    printf("Enter number of frames: ");
    scanf("%d", &no_of_frames);

    printf("Enter number of pages: ");
    scanf("%d", &no_of_pages);

    printf("Enter reference string: ");
    for (i = 0; i < no_of_pages; ++i) {
        scanf("%d", &pages[i]);
    }

    for (i = 0; i < no_of_frames; ++i) {
        frames[i] = -1;
        time[i] = 0; // Initialize the time array to 0
    }

    for (i = 0; i < no_of_pages; ++i) {
        int page = pages[i];
        int page_found = 0;

        // Check if the page is already in frames
        for (j = 0; j < no_of_frames; ++j) {
            if (frames[j] == page) {
                time[j] = counter++; // Update the time of use
                page_found = 1;
                break;
            }
        }

        // If the page is not in frames, find the LRU page to replace
        if (!page_found) {
            pos = findLRU(time, no_of_frames);
            frames[pos] = page; // Replace the LRU page
            time[pos] = counter++; // Update the time of use
            faults++;
        }

        // Print the current state of frames
        printf("Current frames: ");
        for (j = 0; j < no_of_frames; ++j) {
            printf("%d\t", frames[j]);
        }
        printf("\n");
    }

    printf("\nTotal Page Faults = %d\n", faults);

    return 0;
}

