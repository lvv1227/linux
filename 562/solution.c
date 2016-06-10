#include <fcntl.h>
#include <stdio.h>
#include <sys/select.h>
#include <unistd.h>
  
int main(){
  int fds[2];
  char buf[4096];
  int i,rc,maxfd;
  fd_set watchset;
  fd_set inset;
  int sum=0;
  
  if((fds[0]=open("p1",O_RDONLY | O_NONBLOCK)) <0){
    perror("open p1");
    return 1;
  }
  
  if((fds[1]=open("p2",O_RDONLY | O_NONBLOCK)) <0){
    perror("open p2");
    return 1;
  }
  
  FD_ZERO(&watchset);
  FD_SET(fds[0],&watchset);
  FD_SET(fds[1],&watchset);
  
  maxfd=fds[0]>fds[1] ? fds[0] : fds[1];
  while (FD_ISSET(fds[0],&watchset) ||
         FD_ISSET(fds[1],&watchset)){
    inset=watchset;
    //printf("select start\n");
    if (select(maxfd+1,&inset,NULL,NULL,NULL)<0){
      perror("select");
      return 1;
    }
    //printf("select end\n");
    
    for(i=0;i<2;i++){
      if (FD_ISSET(fds[i],&inset)){
        rc=read(fds[i],buf,sizeof(buf)-1);
        if(rc<0){
          perror("read");
          return 1;
        }
        else if (!rc) {
          close(fds[i]);
          //printf("close %d\n",fds[i]);
          FD_CLR(fds[i],&watchset);
        }
        else{
          buf[rc]='\0';
          //printf("read: %s",buf);
          sum=sum+atoi(buf);
        }
      }
    }
  }
  printf("%d\n",sum);
  return 0;
}
