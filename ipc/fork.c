#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

int main(void)
{
    pid_t pid;
    time_t startTime;
    unsigned long i;

    pid = fork();

    if (pid < 0)
        printf("Fork Failed\n");
    else if(pid == 0)
    {
        startTime = time(NULL);
        printf("Hi from child process: %d\n", pid);
        for(;;)
            if(time(NULL) - startTime >= 20)
                break;
    }
    else
    {
        printf("Hi form parent process: %d\n", pid);
        sleep (40);
    }
    return 0;
}
