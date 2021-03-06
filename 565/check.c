#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024  /* make it a 1K shared memory segment */





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
void print(int *p){
    int i;
    for (i=0;i<100;i++){
        int val1=*(p+i);
       
        printf("%d\n",val1);
        
    }
    
}
//usage ./check key
int main(int argc, char *argv[])
{
    
    if (argc!=2){
        perror("argc should be 2\n");
	printf("argc=%d\n",argc);
    }
    
    //get segment
    int id1=atoi(argv[1]);
    if(id1==0){
        exit(1);
        printf("wrong id 1");
    }
    
    
    int *a1=getAddress(id1);
    print(a1);
    closeData(a1);
    

   
   

    return 0;
}
