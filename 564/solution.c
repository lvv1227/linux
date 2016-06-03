#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void mysignal_handler(int signalno){
 	//printf("called with %d\n",signalno);
	//if(signalno==SIGURG){
		exit(0);
	//}
}

int main(){
    
    int pid=fork();
    if (pid == -1) // если не удалось запустить потомка
    {
        // выведем на экран ошибку и её описание
        printf("Error: Start Daemon failed \n");
        
        return -1;
    }
    else if (!pid) // если это потомок
    {
        
        
        // создаём новый сеанс, чтобы не зависеть от родителя
        setsid();
        
        // переходим в корень диска, если мы этого не сделаем, то могут быть проблемы.
        // к примеру с размантированием дисков
        chdir("/");
        printf("%d\n",getpid());
        // закрываем дискрипторы ввода/вывода/ошибок, так как нам они больше не понадобятся
        close(STDIN_FILENO);
        close(STDOUT_FILENO);
        close(STDERR_FILENO);
        signal(SIGURG,mysignal_handler);
        for(;;){
            usleep(100000);
        }
        
        
        return 0;
    }
    else // если это родитель
    {
        // завершим процес, т.к. основную свою задачу (запуск демона) мы выполнили
        return 0;
    }

}
