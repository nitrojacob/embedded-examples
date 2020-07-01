#include <sys/types.h>
#include <unistd.h>
#include <semaphore.h>

#include <stdio.h>

#define SEM_NAME "xclusion"


void process1(void)
{
    int i, j;
    for(i=0; i<60; i++){
        for(j=0; j<80; j++){
            printf("^");
            fflush(NULL);
            sleep(0.1);
        }
        printf("\n");
    }
}

void process2(void)
{
    int i, j;
    for(i=0; i<60; i++){
        for(j=0; j<80; j++){
            printf("-");
            fflush(NULL);
            sleep(0.1);
        }
        printf("\n");
    }
}

int main(void)
{
    pid_t pid;
    
    pid = fork();

    if (pid < 0)
        printf("Fork Failed\n");
    else if(pid == 0)
    {
        process1();
    }
    else
    {
        process2();
    }
    return 0;
}
