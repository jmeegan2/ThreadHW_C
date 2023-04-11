#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

// Function to read input and exit when "x" or "ESC" is entered
void *input_thread_func(void *arg) {
    char input[10];
    while (strcasecmp(input, "x") != 0 && strcasecmp(input, "ESC") != 0) {
        printf("Enter 'x' or 'ESC' to exit:\n");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0'; // Remove trailing newline
    }
    printf("Exited.\n");
    return NULL;
}

// Function to print "Hello" and thread ID
void *hello_thread_func(void *arg) {
    printf("Hello from thread ID: %lu\n", pthread_self());
    return NULL;
}

int main() {
    // Part 1
    pthread_t input_thread;

    // Create and start the input thread
    pthread_create(&input_thread, NULL, input_thread_func, NULL);

    // Wait for the input thread to finish before moving to Part 2
    pthread_join(input_thread, NULL);

    // Part 2
    pthread_t hello_threads[10];

    // Create and start 10 hello threads
    for (int i = 0; i < 10; i++) {
        pthread_create(&hello_threads[i], NULL, hello_thread_func, NULL);
    }

    // Wait for all hello threads to finish
    for (int i = 0; i < 10; i++) {
        pthread_join(hello_threads[i], NULL);
    }

    return 0;
}
