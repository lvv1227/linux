#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int count1=0;
int count2=0;

void mysignal_handler(int signalno){
	//printf("called with %d\n",signalno);
	if(signalno==SIGUSR1)
		count1++;
	if(signalno==SIGUSR2)
		count2++;
	if(signalno==SIGTERM){
		printf("%d",count1);
		printf(" ");
		printf("%d\n",count2);
		exit(0);
	}

}

int main()
{
	int c=0;
	signal(SIGUSR1,mysignal_handler);
	signal(SIGUSR2,mysignal_handler);
	signal(SIGTERM,mysignal_handler);
	while(1){
		//printf("Hello\n");
		usleep(500000);
	}
	return 0;

}
