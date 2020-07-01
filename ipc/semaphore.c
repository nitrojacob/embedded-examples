/* Must be linked with -lpthread
 * The shared file shall be created at /dev/shm/sem.<SEM_NAME>
 * gcc semaphore.c -lpthread
 */

#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>

#include <stdio.h>

#define SEM_NAME "/xclusion"


void process1(void)
{
    sem_t *sem;
    sem = sem_open(SEM_NAME, O_CREAT, 0666, 1);

    sem_wait(sem);
    
    printf("Process1: Accessing shared resources\n");
    sleep(10);
    printf("Process1: Releasing shared resources\n");

    sem_post(sem);
    sem_close(sem);
    sleep(15);
}

void process2(void)
{
    sem_t *sem;
    sem = sem_open(SEM_NAME, O_CREAT, 0666, 1);

    sem_wait(sem);
    
    printf("Process2: Accessing shared resources\n");
    sleep(10);
    printf("Process2: Releasing shared resources\n");

    sem_post(sem);
    sem_close(sem);
    sleep(15);
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
