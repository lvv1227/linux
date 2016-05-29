#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>


void print_ppid(char *pid){
        char str[20],str1[20],
        str2[20],
        str3[20],str4[20];
	
        strcpy(str,"/proc/");
        //char value[20];
        //snprintf(value,20,"%d",pid);
        //strcat(str,value);   
        strcat(str,pid);   
        strcat(str,"/stat");
        
        
        
        //printf("str= %s\n",str);
        FILE * fp;
        fp = fopen (str, "r");
        if(fp==NULL){
                //printf("NULL");
	        return;
        }
   
        fscanf(fp, "%s %s %s %s", str1, str2, str3, str4);
        //printf("Read String1 |%s|\n", str1 );
        //printf("Read String2 |%s|\n", str2 );
        //printf("Read String3 |%s|\n", str3 );
        //printf("Read String4 |%s|\n", str4 );
        fclose(fp);
        
        int ppid=atoi(str4);
        if(ppid!=1){
                printf("%s\n",str4);
                print_ppid(str4);
        }
        else{
                printf("%s\n",str4);
        }
}

int main(int argc,char *argv[]) 
{
   printf("%s\n",argv[1]);   
   print_ppid(argv[1]);
    
   return(0);
 }

