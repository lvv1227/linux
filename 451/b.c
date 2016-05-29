#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() 
{
    char str[80],str1[10],
    str2[10],
    str3[10],str4[10];
	
    strcpy(str,"/proc/");
    char value[20];
    snprintf(value,20,"%d",getpid());
    printf(value);
    printf("\n");
    strcat(str,value);
    strcat(str,"/stat");
    printf("str %s\n",str);
    printf("pid %d\n",getpid());
    printf("ppid %d\n",getppid());
int year;
    FILE * fp;
    fp = fopen (str, "r");
    if(fp==NULL){
        printf("NULL");
	return 0;
    }
    //fputs("We are in 2012", fp);
    //rewind(fp);
    fscanf(fp, "%s %s %s %s", str1, str2, str3, str4);
    printf("Read String1 |%s|\n", str1 );
    printf("Read String2 |%s|\n", str2 );
    printf("Read String3 |%s|\n", str3 );
    printf("Read String4 |%s|\n", str4 );
    fclose(fp);
    return(0);
 }
