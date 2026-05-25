#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/ipc.h>
#include <sys/shm.h>

#include <sys/types.h>
#include <errno.h>
#include <string.h>

#define BUFFSIZE getpagesize()
#define KEY 1234

int main() {
    struct shmmsg {
        int read;
        char msg[BUFFSIZE - 1];
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

   
        printf("sender says:\n%s\n",shm->msg);
        shm->read = 1;
    

    shmdt(shm);

    return 0;
}