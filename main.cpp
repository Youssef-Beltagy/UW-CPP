// main.cpp
// Author: Youssef Beltagy

// Description:
// This program takes one argument and prints the number of
// occurrences of this argument in treasure_island.txt.

#include <stdlib.h>     //exit
#include <stdio.h>      //perror, flush, prinf
#include <unistd.h>     //fork, pipe, execlp, dup2
#include <sys/wait.h>   //wait
#include <cstring>      //strcpy, cmpstr
#include <fcntl.h>      //open, close, lseek, write

using namespace std;


// Description: Tests the open, write, read, close, remove, and lseek system calls.
// Preconditions: There isn't a file.txt in the current directory.
// Postcontions: file.txt will be deleted from the current directory. 
void testFileSystemCalls();

// Description: tests fork, wait, execlp, pipe, and dup2 system calls.
// Uses fork to branch a new child process. The child process executes grep 
// and passes the output through a pipe to the parent process.
// The parent process executes wc to count the number of occurrences of the word.
// Preconditions: chosenWord points to a word you want to count.
// Postcontions: the number of occurences of chosenWord in treasure_island.txt will be printed.
void testProcessSystemCalls(char * chosenWord);

// Description: Tests system calls.
// Preconditions: argc is 1 or 2. If argc == 2, argv has an agrument for testProcessSystemCalls
// Postcontions: file.txt will be deleted from the current directory and the test results will be printed.
int main(int argc, char** argv)
{   

    printf("\n\nThis program tests system calls that are used in CSS courses at UWB.\n");
    printf("It first test the open, close, write, read, remove, and lseek file system calls.\n");
    printf("Then it tests the fork, wait, execlp, pipe, and dup2 process system calls.\n");
    printf("The second test finds the number of occurrences of a word in treasure_island.txt.\n");
    printf("The defualt word is \"Jim\" (The protagonist of Treasure Island).\n");
    printf("Add a word as a program argument to search for it.\n");

    testFileSystemCalls();

    char * chosenWord;

    if(argc >= 2) {
        chosenWord = argv[1];
    }else{
        chosenWord = strcpy(new char[4], "Jim");
        // Here is a memory leak, but isn't worth fixing since it isn't in a for loop.
        // And the program will end shortly. 
    }

    testProcessSystemCalls(chosenWord);

}

void testFileSystemCalls(){
    int file = open("file.txt", O_CREAT|O_WRONLY, S_IRUSR|S_IWUSR|S_IROTH|S_IWOTH);

    if(file < 0){
        perror("Error in creating file.txt");
        exit(EXIT_FAILURE);
    }

    char * fileBuffer = static_cast<char*>(malloc(14));
    strcpy(fileBuffer, "Hello World!");

    if (write(file, fileBuffer, 12) != 12){
        perror("Error in writing to file");
        exit(EXIT_FAILURE);
    }

    if(close(file) < 0){
        perror("Error closing file.txt");
        exit(EXIT_FAILURE);
    }

    file = open("file.txt", O_RDWR | O_APPEND);

    if(file < 0){
        perror("Error in opening file.txt (second time)");
        exit(EXIT_FAILURE);
    }

    strcpy(fileBuffer, " A new World!");

    if (write(file, fileBuffer, 13) != 13){
        perror("Error appending to file.txt");
        exit(EXIT_FAILURE);
    }

    if(lseek(file, 19, SEEK_SET) < 0){
        perror("Error seeking in file.txt");
        exit(EXIT_FAILURE);
    }

    if(read(file, fileBuffer, 5) != 5){
        perror("Error reading from file.txt");
        exit(EXIT_FAILURE);
    }

    // terminate the word
    fileBuffer[5] = '\0';

    char * expectedOutput = static_cast<char*>(malloc(6));
    strcpy(expectedOutput, "World");
    if (strcmp(fileBuffer, expectedOutput) != 0){
        perror("Error Value read from file.txt is unexpected");
        exit(EXIT_FAILURE);
    }

    free(fileBuffer);
    free(expectedOutput);

    if(close(file) < 0){
        perror("Error closing file.txt (second time)");
        exit(EXIT_FAILURE);
    }

    if(remove("file.txt") < 0){
        perror("Error deleting file.txt");
        exit(EXIT_FAILURE);
    }

    printf( "\nThe file tests passed.\n");
    printf("open, write, lseek, remove, and read work.\n\n");

}

void testProcessSystemCalls(char* chosenWord){

    enum index : int {read = 0, write = 1};

    printf("The number of occurrences of \"%s\" in treasure_island.txt is ", chosenWord);
    fflush(stdout);

    pid_t pid;

    int pipe1[2]; // Between parent and child

    if (pipe(pipe1) < 0)
    {

        perror("Error in creating pipe1");
        exit(EXIT_FAILURE);

    }

    // Create the child.
    pid = fork();

    if (pid < 0) {
        perror("Error during first fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)  //Child
    {

        dup2(pipe1[write], STDOUT_FILENO);
        close(pipe1[read]);
        close(pipe1[write]);

		execlp("/bin/grep", "grep", "-o", "-i", chosenWord,"treasure_island.txt", NULL);
                
        // grep process is overlayed so these two lines are never executed
        perror("Error executing grep");
        exit(EXIT_FAILURE);

    } else { //Parent
    

        wait(NULL);
        
        dup2(pipe1[read], STDIN_FILENO);
        close(pipe1[read]);
        close(pipe1[write]);

		execlp("/bin/wc", "wc", "-l", NULL);
                
        // wc process is overlayed so these two lines are never executed
        perror("Error executing grep");
        exit(EXIT_FAILURE);

    }

}