#include "bmp.h"
#include "lcd.h"
#include "stdio.h"
//系统延时函数的头文件
#include <unistd.h>
#include "event.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

void my_signal(int signum)
{
    if(signum == SIGINT)
    {
        system("killall -9 madplay");       //杀死madplay放歌的进程
        system("killall -9 system");        //杀死system进程 （system是您执行的那个程序名）
        exit(0); //结束进程
    }
}

int main(void)
{

    int i = 0;
    char show[20];

    signal(SIGINT,my_signal);
#if 0
    char*bmp[] = {"1.bmp","2.bmp","3.bmp","4.bmp","5.bmp","6.bmp","7.bmp","8.bmp","9.bmp",
                  "10.bmp","11.bmp"};
    lcd_init();
    for(i=0;i<11;i++)
    {
        printf("i:%d   res:%d\n",i+1,bmp_show(bmp[i]));
        sleep(3);
    }
    lcd_uninit();

#endif
    
    execlp("madplay","madplay","1.mp3",NULL);	// madplay end.mp3

    //get_inputevent();

    return 0;
}

