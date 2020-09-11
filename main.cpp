// main.cpp
// Author: Youssef Beltagy

// Description:
// This program takes one argument and prints the number of
// occurences of this argument in text.txt.

#include <stdlib.h>     //exit
#include <stdio.h>      //perror, flush, prinf
#include <unistd.h>     //fork, pipe, execlp
#include <sys/wait.h>   //wait
#include <cstring>      //strcpy
#include <fcntl.h>      //open, close, lseek, write

using namespace std;

// Description: The main function uses for to branch a new child process.
// The child process executes grep and passes the output through a pipe to the
// parent process.
// the parent process executes wc to count the number of occurences of the word.
// Preconditions: argc is 1 or 2. If argc == 2, argv has an agrument for grep.
// Postcontions: the number of occurences of "123" or argv[1] in text.txt will be printed.
int main(int argc, char** argv)
{

    int file = open("file.txt", O_CREAT, S_IRUSR|S_IWUSR|S_IROTH|S_IWOTH);
    char * helloWorld = strcpy(new char[3], "123");
    write(file, helloWorld, 10);
    close(file);

    enum index : int {read = 0, write = 1};

    printf("This Program searches for a word in text.txt.\n");
    printf("The defualt word is \"123\". Add a word as an argument to search for it\n");


    char* chosenWord;

    if(argc >= 2) {
        chosenWord = argv[1];
    }else{
        chosenWord = strcpy(new char[3], "123");
    }

    printf("The number of occurences of \"%s\" in text.txt is ", chosenWord);
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

		execlp("/bin/grep", "grep", "-o", "-i", chosenWord,"text.txt", NULL);
                
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
