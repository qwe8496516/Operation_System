#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid, pid2;
    int status, i;

    if (fork() == 0)
    {
        printf("This is the child process = %d\n", getpid());
        exit(100); // return a value '100'
    }
    else
    {
        sleep(1);
        pid = wait(&status);
        i = WEXITSTATUS(status);          // get the return value 100
        printf("child return = %d\n", i); // print the return value
        pid2 = fork();
        if (pid2 == 0)
        {
            pid2 = system("cal 2021"); // do the system code
            wait(&pid2);
            return pid2;
        }
        else if (pid > 0)
        {
            sleep(1);
            printf("This is the parent process = %d, wait for child...\n", pid2);
        }
    }
    return 0;
}
