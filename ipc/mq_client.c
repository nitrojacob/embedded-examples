/* Must be linked with -lrt
 * gcc mq_client.c -lrt
 */

#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <mqueue.h>

#include <stdio.h>
#include <string.h>

#define MQ_NAME "/mqueue"
#define MSG_LEN 256



int main(void)
{
    mqd_t mqd;
    char buffer[MSG_LEN];
    int i;

    mqd = mq_open(MQ_NAME, O_WRONLY, 0666, NULL);
    if(mqd == -1){
        printf("Error opening message queue\n");
        return 0;
    }

    for(i=0; i<10; i++){
        sprintf(buffer, "Message #%d from client", i);
        mq_send(mqd, buffer, strlen(buffer), 1);
        printf("Sending Message - %s\n", buffer);
    }

    mq_close(mqd);
    return 0;
}
