#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024  /* make it a 1K shared memory segment */

//requesting new shared memory
int *createAndGetAddess(char *path){
    /* make the key: */
    int shmid;
    key_t key;
    
    if ((key = ftok(path, 'R')) == -1) /*Here the file must exist */ 
    {
        perror("ftok");
        exit(1);
    }

    /*  create the segment: */
    if ((shmid = shmget(key, SHM_SIZE, 0644 | IPC_CREAT)) == -1) {
        perror("shmget");
        exit(1);
    }

    /* attach to the segment to get a pointer to it: */
    data = shmat(shmid, (void *)0, 0);
    if (data == (char *)(-1)) {
        perror("shmat");
        exit(1);
    }
    return (int *)data;
}

void closeData(void *p){
    //detach from segment
    if (shmdt(p) == -1) {
        perror("shmdt");
        exit(1);
    }
}
//put 10 numbers
void fillData(int *p){
    int i;
    for(int i=0;i<10;i++){
        *(p+i)=i;
    }
}

int main()
{
    key_t key;
    int shmid;
    char *data;
    int mode;

    int *p1=createAndGetAddess("hello1.txt");
    int *p2=createAndGetAddess("hello2.txt");
    fillData(p1);
    fillData(p2);

    closeData(p1);
    closeData(p2);

    

    /* detach from the segment: */
    

    return 0;
}
