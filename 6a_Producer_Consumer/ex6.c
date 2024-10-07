#include <stdio.h>
#include <stdlib.h>

void start_producer() {
    system("gnome-terminal -- ./producer");
}

void start_consumer() {
    system("gnome-terminal -- ./consumer");
}

int main() {
    int choice;
    while (1) {
        printf("1. Start Producer\n");
        printf("2. Start Consumer\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                start_producer();
                break;
            case 2:
                start_consumer();
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}