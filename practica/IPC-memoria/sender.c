#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/ipc.h>
#include <sys/shm.h>

#include <sys/types.h>
#include <errno.h>
#include <string.h>

#define BUFFSIZE 1024
#define KEY 1234

struct shmmsg {
        int read;
        char msg[1023];
    };

int main(int argc, char *argv[]) {

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
    
    //int length = sizeof(mensaje) / sizeof(mensaje[0]);

    //for(int i = 0; i < length; i++){
    //    message[i] = mensaje[i];
    //}



    while (shm->read != 1) {
        printf("Esperando que el mensaje sea leido.\n");
        printf("\x1b[1F"); // Move to beginning of previous line
        printf("\x1b[2K"); // Clear entire line
    }

    shmdt(shm);
    shmctl(shmid,IPC_RMID, 0);
    return 0;
}

int sendMessage(struct shmmsg mem) {

}