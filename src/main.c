#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "lcd.h"
#include "bmp.h"
#include "event.h"
#include "music.h"
#include "stdbool.h"

void my_signal(int signum)
{
    if(signum == SIGINT)
    {
        stopMusic();       //杀死madplay放歌的进程
        exit(0);
    }
}

int main(void)
{
    int start_x,start_y,end_x,end_y;
    char*bmp[] = {"1.bmp","2.bmp","3.bmp","4.bmp","5.bmp","6.bmp","7.bmp",
                  "8.bmp","9.bmp","10.bmp","11.bmp","12.bmp"};
    pid_t  pid = 0;
    int i = 0,j = 0;
	char *mp3_name[] = {"1.mp3","2.mp3"};

    //记录菜单等级
    int menuState = -1;
    //记录音乐播放的状态
    int pictrueState = 1;
    //记录纯音乐播放的状态
    bool musicState = true;


    /* 捕捉了SIGINT信号（Ctrl+C），当用户按下 Ctrl+C结束父进程时，会自动去执行 my_signal 函数 */
    signal(SIGINT,my_signal);

    //1.初始化LCD 为显示做准备
    lcd_init(); //初始换LCD屏，屏幕已经做好显示的准备工作
    lcd_draw_clear(0,0,480,800,0xffffff);
    bmp_show("home.bmp",30,168);

    /*增加触摸屏控制*/
    while(1)
    {
            get_inputevent(&start_x,&start_y,&end_x,&end_y);

            printf("start_x:%d,start_y:%d,end_x:%d,end_y:%d\n",start_x,start_y,end_x,end_y);

            //向上滑动
            if(start_y-end_y>50)
            {
                printf("向上滑动 照片播放\n");
                menuState = 0;
                lcd_draw_clear(0,0,480,800,0xffffff);
                bmp_show("picture.bmp",269,184);
                continue;
            }
            //向下滑动
            else if (end_y-start_y>50)
            {
                printf("向下滑动  音乐播放\n");
                menuState = 1;
                lcd_draw_clear(0,0,480,800,0xffffff);
                showMenu(0);
                stopMusic();
                continue;
            }
            
            printf("menuState:%d\n",menuState);
#if 1
        if(menuState == 0)
        {
            if(end_x-start_x > 50)
            {
                printf("切换到下一张照片\n");
                pid = fork();
                stopMusic();
                if(pid>0)
                {
                    if(++i>4)
                        i=0;
                    lcd_draw_clear(0,0,480,800,0xffffff);
                    bmp_show(bmp[i],0,0);
                }
                else if(pid == 0)
                    playMusic(mp3_name[i%2]);
            }
            else if(start_x-end_x > 50)
            {
                printf("切换到上一张照片\n");
                pid = fork();
                stopMusic();
                if(pid>0)
                {
                    if(--i<0)
                        i=4;
                    lcd_draw_clear(0,0,480,800,0x000000);
                    bmp_show(bmp[i],0,0);
                }
                else if(pid == 0)
                    playMusic(mp3_name[i%2]);
            }
            else if((end_x>200 && end_x < 600) || (end_y>200 && end_y < 400))
            {
                printf("停止播放音乐开始自动播放照片\n");
                // pid = fork();
                // count++;
                // if(pid == 0 && count%2 == 0)
                // {
                    printf("开始幻灯片播放\n");
                    stopMusic();
                    for(j=0;j<12;j++)
                    {
                        lcd_draw_clear(0,0,480,800,0x000000);
                        bmp_show(bmp[j],0,0);
                        sleep(1);
                    }
                // }
                // else if(pid== 0 && count%2 == 1)
                // {
                //     printf("结束幻灯片播放\n");
                // }
            }
        }
        else if(menuState == 1)
#endif

#if 1
        {
            int temp = getMenuValueByLocation(start_x,start_y,end_x,end_y);
            printf("getMenuValueByLocation:%d",temp);  
            printf("   i:%d   j:%d musicState:%d\n",i,j,musicState);
            //1表示点击了开始按钮
            if(temp==1 && musicState)
            {
                printf("开始放歌\n");
                musicState = false;
                showMenu(1);
                pid = fork();
                if(pid == 0)
                {
                    printf("bofang\n");
                    playMusic(mp3_name[i]);
                    kill(pid,SIGKILL);
                }
            }
            //2表示点击暂停
            else if(temp == 1 && musicState==false)
            {
                printf("停止放歌\n");
                musicState = true;
                showMenu(0);
                stopMusic();
            }
            //3表示点击切换上一首
            else if(temp == 2)
            {
                printf("切换上一首\n");
                showMenu(1);
                pid = fork();
                if(--i == -1)
                    i = 1;
                if(pid == 0)
                {
                    stopMusic(); 
                    printf("i:%d\n",i);
                    playMusic(mp3_name[i]);
                    kill(pid,SIGKILL);
                }
            }
            //4表示切换下一首
            else if(temp == 3)
            {
                printf("切换下一首\n"); 
                showMenu(1);
                pid = fork();
                if(++i == 2)
                    i = 0;
                if(pid == 0)
                {
                    stopMusic(); 
                    printf("i:%d\n",i);
                    playMusic(mp3_name[i%2]); 
                    kill(pid,SIGKILL);
                }
            }
            //发生错误
            else
            {
                printf("无效值\n");
            }
        }
        
#endif
    }
    //3.解除屏幕，不再需要LCD显示时，解除屏幕    
    lcd_uninit(); //解除屏幕
}

