#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#include <stdio.h>

#define FILENAME "/dev/shm/ipc.demo"
#define FILEMODE S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP

int pseudoSharedMem = 0;

void process1(void)
{
    int fd;
    int *sharedMem;
    fd = open("/dev/shm/ipc.demo", O_CREAT | O_RDWR, FILEMODE);
    write(fd, &pseudoSharedMem, sizeof(int));   /*The file size should be >= size of mmap region*/
    if(fd == -1){
        printf("process 1: Unable to open file %s\n", FILENAME);
        return;
    }
    sharedMem = (int*) mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);
    if (sharedMem == (int*)(-1)){
        printf("process 1: Unable to memory map\n");
        return;
    }
    pseudoSharedMem = 3333;
    *sharedMem = 5555;
    //msync((void*)sharedMem, sizeof(int), MS_SYNC);
    sleep(10);
}

void process2(void)
{
    int fd;
    int *sharedMem;
    sleep(10);
    fd = open("/dev/shm/ipc.demo", O_CREAT | O_RDWR, FILEMODE);
    if(fd == -1){
        printf("process 2: Unable to open file %s\n", FILENAME);
        return;
    }
    sharedMem = (int*) mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);
    if ((sharedMem) == (int*)(-1)){
        printf("process 2: Unable to memory map\n");
        return;
    }
    printf("*sharedMem = %d\n", *sharedMem);
    printf("pseudoSharedMem = %d\n", pseudoSharedMem);
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
