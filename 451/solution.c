#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>


int get_ppid(int pid){
        char str[100],str1[100],
        str2[100],
        str3[100],str4[100];
	
        strcpy(str,"/proc/");
        char value[100];
        snprintf(value,100,"%d",pid);
        strcat(str,value);      
        strcat(str,"/stat");
        
        
        
        //printf("str= %s\n",str);
        FILE * fp;
        fp = fopen (str, "r");
        if(fp==NULL){
                //printf("NULL");
	        return -1;
        }
   
        fscanf(fp, "%s %s %s %s", str1, str2, str3, str4);
        //printf("Read String1 |%s|\n", str1 );
        //printf("Read String2 |%s|\n", str2 );
        //printf("Read String3 |%s|\n", str3 );
        //printf("Read String4 |%s|\n", str4 );
        fclose(fp);
        return atoi(str4);
}

int main() 
{
    int pid=getpid();
    int ppid=get_ppid(pid);
    //int pppid=get_ppid(ppid);
    
    
    //printf("pid %d\n",pid);
    //printf("ppid %d\n",ppid);
    printf("%d\n",ppid);
    
    return(0);
 }

