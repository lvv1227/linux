#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>



char *table[1000];
int size=0;

int LIMIT=1000;
int lcount=0;

int compare(){  
        
        //printf("tpid=%d\n",tpid);
        int count=0;
        //lcount++;
        //if(lcount>LIMIT) return 0;
        
        char str[20],str1[20],
        str2[20],
        str3[20],str4[20];
	    
	    int i;
	    char *sample="(genenv)";
	for(i=0;i<size;i++){
	    strcpy(str,"/proc/");
        //char value[20];
        //snprintf(value,20,"%d",pid);
        //strcat(str,value);   
        
        int pid=atoi(table[i]);
        if(pid==0)
            continue;
            
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
        
        if(strcmp(str2,sample)==0){
            count++;
            //printf("%s %s\n",str1,str2);
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
  printf("%d\n",compare());
  //int i;
  //for (i=0;i<pos;i++)
  //      printf("%s\n",table[i]);
  return 0;
 }

