#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>



char *table[1000];
int size=0;

int LIMIT=1000;
int lcount=0;

int check_pid(int tpid){ // target pid     look if ppid==pid for the process with pid=dir  
        
        //printf("tpid=%d\n",tpid);
        int count=0;
        //lcount++;
        //if(lcount>LIMIT) return 0;
        
        char str[20],str1[20],
        str2[20],
        str3[20],str4[20];
	    
	    int i;
	for(i=0;i<size;i++){
	    strcpy(str,"/proc/");
        //char value[20];
        //snprintf(value,20,"%d",pid);
        //strcat(str,value);   
        strcat(str,table[i]);   
        strcat(str,"/stat");
        
        //printf("tpid=%d,path=%s\n",tpid,str);
        
        
        //printf("str= %s\n",str);
        FILE * fp;
        fp = fopen (str, "r");
        if(fp==NULL){
                //printf("NULL");
	        continue;
        }
   
        fscanf(fp, "%s %s %s %s", str1, str2, str3, str4);
        
        fclose(fp);
        
        int ppid=atoi(str4);
        if(ppid==0) //error
            continue;
        int pid=atoi(table[i]); 
        if (pid==0) //error self
            continue;
        
        if(ppid==tpid){ //the process is a child of tpid process
               
               if(pid==1){
                    printf("pid=1 %s %d",table[i],tpid);
               }
               if(pid==0){
                    printf("pid=0 %s %d",table[i],tpid);
               }
               count+=check_pid(pid)+1; //go deeper,+1 for the child process itself
        }
          
	    
	}
	return count;
              
}


void init_table(){
        DIR *dp;
        struct dirent *ep;
        dp = opendir ("/proc/");
        int pos=0;
        if (dp != NULL)
        {
                while (ep = readdir (dp)){
                       
                        table[pos++]=ep->d_name;
                        //printf("dirent=%s\n",ep->d_name);
                }
        
                (void) closedir (dp);
        }
        else
                perror ("Couldn't open the directory");
        size=pos;
        //printf("size=%d\n",pos);
}

int main(int argc,char *argv[]) 
{
  
  init_table();
  int pid=atoi(argv[1]);
  
  
  
  printf("%d\n",check_pid(pid)+1);
  //int i;
  //for (i=0;i<pos;i++)
  //      printf("%s\n",table[i]);
  return 0;
 }

