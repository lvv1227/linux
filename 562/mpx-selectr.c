#include <fcntl.h>
#include <stdio.h>
#include <sys/select.h>
#include <unistd.h>
  
int main(){
  int fds[2];
  char buf[4096];
  int i;
  int fd;
  
  if ((fds[0]=open("p1",O_RDONLY))<0){
    perror ("open p1");
    return 1;
  }
  if ((fds[1]=open("p2",O_RDONLY))<0){
    perror ("open p2");
    return 1;
  }
  fd=0;
  while(1){
    i=read(fds[fd],buf,sizeof(buf)-1);
    if(i<0){
      perror("read");
      return 1;
    }
    else if(!i){
      printf("channel closed\n");
      return 0;
    }
    buf[i]='\0';
    printf("reading:%s",buf);
    fd=(fd+1)%2;
  }
}
