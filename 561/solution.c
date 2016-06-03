#include <stdio.h>

int main(int argc, char *argv[]){
	FILE *fp;
	if(argc<2){
		printf("args needed");
		exit(1);
	}
	char str[50]="";
	strcat(str,argv[1]);
	strcat(str," ");
	strcat(str,argv[2]);
	
	if (( fp = popen(str, "r")) == NULL){
                 perror("popen");
                 exit(1);         
	}
	
	int c;
	int count=0;
	while((c=fgetc(fp))!=EOF){
		//printf("%c%c",(char)c,(char)c);
		if ((char)c=='0')
			count++;
	}
	printf("%d\n",count);
	pclose(fp);
	return 0;
}
