#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
 
#define BUFFER_SIZE 256
 
/*
 * cat: A basic implementation of the 'cat' utility.
 *
 * This program should read a file specified by the user
 * and print its contents to the standard output (the terminal).
 *
 * Usage:
 * ./cat <filename>
 *
 * The program should:
 * 1. Check if exactly one filename is provided as a command-line argument.
 * 2. Open the specified file for reading.
 * 3. Read the file's contents in chunks (using a buffer).
 * 4. Write each chunk to standard output (STDOUT_FILENO).
 * 5. Close the file and handle any potential errors.
 */
int main(int argc, char *argv[]) {
    // TODO: Step 1 - Check for the correct number of command-line arguments.
    // If argc is not equal to 2, print a usage message to stderr
    // (e.g., "Usage: %s <filename>\n") and exit with a status of 1.
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1; 
    }

    
 
    // TODO: Step 2 - Open the file.
    // The filename is in argv[1].
    // Use the open() system call to open it in read-only mode (O_RDONLY).
    // Store the returned file descriptor in an integer variable.
    // If open() returns -1, an error occurred. Use perror("Error opening file")
    // to print the error and exit with a status of 1.
    char *filepath = argv[1];
    int fd = open(filepath, O_RDONLY);

    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }
 
    // TODO: Step 3 & 4 - Read from the file and write to standard output.
    // Create a buffer (an array of chars) of size BUFFER_SIZE.
    // Use a loop with the read() system call to read from the file into the buffer.
    // The read() call returns the number of bytes read.
    // The loop should continue as long as read() returns a value greater than 0.
    // Inside the loop, use the write() system call to write the buffer's contents
    // to standard output (STDOUT_FILENO). The number of bytes to write is the
    // value returned by read().
    // Be sure to handle potential errors from both read() and write().
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read = read(fd, buffer, BUFFER_SIZE);
    while (bytes_read  > 0) {
        if (write(STDOUT_FILENO, buffer, bytes_read) == -1) {
            perror("Error writing to stdout");
            close(fd);
            return 1;
        }
        bytes_read = read(fd, buffer, BUFFER_SIZE);
    }

    if (bytes_read == -1) {
        perror("Error reading file");
        close(fd);
        return 1;
    }
 
    // TODO: Step 5 - Close the file.
    // Use the close() system call to close the file descriptor.
    // Handle any potential errors from close().
    int status = close(fd);
    if (status == -1) {
        perror("Error closing file");
        return 1;
    }

    return 0; // Return 0 for success.
}
