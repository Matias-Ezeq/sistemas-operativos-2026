#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/ipc.h>
#include <sys/shm.h>

#include <sys/types.h>
#include <errno.h>
#include <string.h>

#define BUFFSIZE 1024 //getpagesize()
#define KEY 1234

int main(int argc, char *argv[]) {
    struct shmmsg {
        int read;
        char msg[BUFFSIZE / 2];
    };

    int shmid;
    struct shmmsg *shm;

    shmid = shmget(KEY,BUFFSIZE,IPC_CREAT | 0666);
    if (shmid == -1){
        perror("shmget");
        return 1;
    }

    if ((shm = shmat(shmid,NULL,0)) == (void *) - 1){
        perror("shmat");
        strerror(errno);
        return 1;
    }
    printf("id: %i, address: %X",shmid,shm);
    char *message = shm->msg;

    message = "Hello world!";

    while (shm->read != 1) {
        printf("waiting for the message to be read.\n");
        sleep(10);
    };

    shmdt(shm);
    shmctl(shmid,IPC_RMID, 0);
    return 0;
}