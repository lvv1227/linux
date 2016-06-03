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
    printf("key=%d\n",key);
    /*  create the segment: */
    if ((shmid = shmget(key, SHM_SIZE, 0644 | IPC_CREAT)) == -1) {
        perror("shmget");
        exit(1);
    }

    /* attach to the segment to get a pointer to it: */
    int *data = shmat(shmid, (void *)0, 0);
    if (data == (int *)(-1)) {
        perror("shmat");
        exit(1);
    }
    return data;
}



//get shared memore address for existing id
int *getAddress(int key){
    int shmid;
    char *data;
    if ((shmid = shmget(key, SHM_SIZE, 0644)) == -1) {
        printf("error getting id, id=%d\n",key);
        exit(1);
    }
    
    data = shmat(shmid, (void *)0, 0);
    if (data == (char *)(-1)) {
        printf("error getting address, id=%d\n",key);
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
void print(int *p1,int *p2,int *out){
    int i;
    for (i=0;i<100;i++){
        int val1=*(p1+i);
        int val2=*(p2+i);
        printf("%d\n",val1+val2);
        *(out+i)=val1+val2;
    }
    
}
//usage ./solution key1 key2
int main(int argc, char *argv[])
{
    key_t key;
    int shmid;
    char *data;
    int mode;
    if (argc!=2){
        perror("argc should be 2\n");
	printf("argc=%d\n",argc);
    }
    
    //get segment 1
    int id1=atoi(argv[1]);
    if(id1==0){
        exit(1);
        printf("wrong id 1");
    }
    int id2=atoi(argv[2]);
    if(id2==0){
        exit(1);
        printf("wrong id 2");
    }
    
    int *a1=getAddress(id1);
    int *a2=getAddress(id2);
    int *out=createAndGetAddess("solution");
    print(a1,a2,out);
    closeData(a1);
    closeData(a2);
    closeData(out);

   
   

    return 0;
}
