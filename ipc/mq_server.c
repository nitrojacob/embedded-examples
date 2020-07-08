/* Must be linked with -lrt
 * gcc mq_server.c -lrt
 */

#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <mqueue.h>

#include <errno.h>
#include <error.h>
#include <stdio.h>

#define MQ_NAME "/mqueue"
#define MSG_LEN 256

struct mq_attr myMQAttr = {
    .mq_maxmsg = 10,
    .mq_msgsize = MSG_LEN,
};

void process1(void)
{
    mqd_t mqd;
    ssize_t len;
    char buffer[MSG_LEN];
    mqd = mq_open(MQ_NAME, O_CREAT|O_RDONLY, 0666, &myMQAttr);
    if(mqd == -1)
        error(-1, errno, "Process1: mq_open");

    while(1){
        len = mq_receive(mqd, buffer, MSG_LEN, NULL);
        if(len == -1)
            error(-1, errno, "Process1: mq_receive");
        
        printf("Process1: Received Message - %s\n", buffer);
        sleep(1);
    }

    mq_close(mqd);
}

void process2(void)
{
    mqd_t mqd;
    ssize_t len;
    char buffer[MSG_LEN];
    mqd = mq_open(MQ_NAME, O_CREAT|O_RDONLY, 0666, &myMQAttr);
    if(mqd == -1)
        error(-1, errno, "Process2: mq_open");

    while(1){
        len = mq_receive(mqd, buffer, MSG_LEN, NULL);
        if(len == -1)
            error(-1, errno, "Process2: mq_receive");

        printf("Process2: Received Message - %s\n", buffer);
        sleep(2);
    }

    mq_close(mqd);
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
