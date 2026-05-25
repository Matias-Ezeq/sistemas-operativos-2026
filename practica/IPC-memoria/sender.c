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

int main(int argc, char *argv[]) {
    struct shmmsg {
        int read;
        char msg[BUFFSIZE - 1];
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
    printf("id: %i, address: %X\n",shmid,shm);
    char *message = shm->msg;
    //char mensaje[];
    printf("Mensaje: ");
    fgets(message,sizeof(shm->msg),stdin);
    printf("%s\n",message);
    
    //int length = sizeof(mensaje) / sizeof(mensaje[0]);

    //for(int i = 0; i < length; i++){
    //    message[i] = mensaje[i];
    //}



    while (shm->read != 1) {
        printf("waiting for the message to be read.\n");
        sleep(2);
    }

    shmdt(shm);
    shmctl(shmid,IPC_RMID, 0);
    return 0;
}