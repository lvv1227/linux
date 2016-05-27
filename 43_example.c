#include <sched.h>
#include <stdio.h>
#include <unistd.h>

#define STACK_SIZE 10000
char child_stack[STACK_SIZE+1]; //allocating array

int child(void *params){
  int c=0;
  while(true){
    usleep(50000);
    printf("child turn %d\n",c++);
  }
}

int main(){
  int c=0;
  int result=clone(child,child_stack+STACK_SIZE,0,0); //the end of the array is used as the stack is movign backward
  printf("clone result=\%d\n",result);
  
  while(true){
    usleep(50000);
    printf("parent turn %d\n",c++);
  }
}