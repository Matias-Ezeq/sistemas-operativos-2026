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

int main() {
    struct shmmsg {
        int read;
        char msg[BUFFSIZE];
    };
    
    int shmid;
    char message;
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

    if(shm->msg){
        printf("sender says:\n%s\n",shm->msg);
        shm->read = 1;
    }
    else {
        printf("no message");
    }

    shmdt(shm);

    return 0;
}