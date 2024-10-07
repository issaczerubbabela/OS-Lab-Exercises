#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_PROCESSES 10

int num_seats = 0;
int choosing[MAX_PROCESSES];
int number[MAX_PROCESSES];
int n;  // Number of processes

pthread_mutex_t input_mutex = PTHREAD_MUTEX_INITIALIZER;  // Mutex for synchronizing input operations

void enter_critical_section(int process_id) {
    for (int i = 0; i < n; i++) {
        if (i != process_id) {
            choosing[process_id] = 1;
            number[process_id] = 1 + (number[i] > number[process_id] ? number[i] : number[process_id]);
            choosing[process_id] = 0;
            while (choosing[i]) ;
            while (number[i] != 0 && (number[i] < number[process_id] || (number[i] == number[process_id] && i < process_id))) ;
        }
    }
}

void leave_critical_section(int process_id) {
    number[process_id] = 0;
}

void* process(void* arg) {
    int process_id = (int)arg;
    int choice, count;

    while (1) {
        pthread_mutex_lock(&input_mutex);  // Lock for input synchronization

        printf("Process %d: Enter 1 to book seats, 2 to cancel seats, 0 to exit: ", process_id);
        scanf("%d", &choice);

        if (choice == 0) {
            pthread_mutex_unlock(&input_mutex);  // Unlock before exiting
            pthread_exit(NULL);
        }

        if (choice == 1 || choice == 2) {
            printf("Process %d: Enter number of seats: ", process_id);
            scanf("%d", &count);

            if (count < 0) {
                printf("Process %d: Invalid number of seats. Try again.\n", process_id);
                pthread_mutex_unlock(&input_mutex);  // Unlock before continuing
                continue;
            }

            enter_critical_section(process_id);

            if (choice == 1) {
                if (count <= num_seats) {
                    num_seats -= count;
                    printf("Process %d: %d seat(s) booked. Total seats available: %d\n", process_id, count, num_seats);
                } else {
                    printf("Process %d: Not enough seats available for booking.\n", process_id);
                }
            } else if (choice == 2) {
                num_seats += count;
                printf("Process %d: %d seat(s) canceled. Total seats available: %d\n", process_id, count, num_seats);
            }

            leave_critical_section(process_id);
        } else {
            printf("Process %d: Invalid choice. Try again.\n", process_id);
        }

        pthread_mutex_unlock(&input_mutex);  // Unlock after processing input
    }
    return NULL;
}

int main() {
    pthread_t threads[MAX_PROCESSES];
    int process_ids[MAX_PROCESSES];

    printf("Enter the total number of seats: ");
    scanf("%d", &num_seats);

    printf("Enter the number of processes (1 to %d): ", MAX_PROCESSES);
    scanf("%d", &n);

    if (n < 1 || n > MAX_PROCESSES) {
        printf("Invalid number of processes.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        choosing[i] = 0;
        number[i] = 0;
        process_ids[i] = i;
        pthread_create(&threads[i], NULL, process, &process_ids[i]);
    }

    for (int i = 0; i < n; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&input_mutex);  // Destroy the mutex
    printf("Program exiting...\n");
    return 0;
}