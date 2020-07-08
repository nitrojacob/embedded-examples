#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#include <errno.h>
#include <error.h>
#include <stdio.h>

#define MAX_LEN 256

int pipefd[2];

void process1(void)
{
    int i, len;
    char buffer[MAX_LEN];
    close(pipefd[0]);
    for(i=0; i<10; i++){
        len = sprintf(buffer, "Message #%d\n", i);
        if(write(pipefd[1], buffer, len) == -1)
            error(-1, errno, "Process1: write");
        sleep(1);
    }
    close(pipefd[1]);
}

void process2(void)
{
    int len = 1;
    char buffer[MAX_LEN];
    close(pipefd[1]);
    while(len){
        if((len = read(pipefd[0], buffer, MAX_LEN)) == -1)
            error(-1, errno, "Process2: read");
        if(len)
            printf("%s", buffer);
    }
    close(pipefd[0]);
}

int main(void)
{
    pid_t pid;
    int result;

    result = pipe(pipefd);
    if(result == -1)
        error(-1, errno, "Pipe Creation");
    
    
    pid = fork();

    if (pid < 0)
        error(-1, errno, "fork");
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
