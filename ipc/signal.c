#include <signal.h>
#include <stdio.h>
#include <string.h>

unsigned char msg[100] = "";

void sigHandler(int sigNum)
{
    sprintf(msg, "Signal Received: %d\n", sigNum);
}


int main(void)
{
    struct sigaction mySigAction;
    sigaction(SIGINT, NULL, &mySigAction);
    mySigAction.sa_handler = sigHandler;
    sigaction(SIGINT, &mySigAction, NULL);

    while(strlen(msg) == 0);
    printf("%s", msg);

    return 0;
}
