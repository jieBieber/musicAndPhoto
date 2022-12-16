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
#include <wait.h>

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
    int i = 0,j = 0,k = 0;
	char *mp3_name[] = {"1.mp3","2.mp3"};

    //记录菜单等级
    int menuState = -1;
    //记录音乐播放的状态
    int pictrueState = 1;
    //记录纯音乐播放的状态
    int musicState = -1,flag = 0;
    //记录是否已经开始自动播放图片
    bool autoPicture = false;


    printf("test for arm-linux-gcc\n");
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
        //从左上往右下滑动
        if(end_y-start_y>50 && end_x-start_x>50 && menuState!=-1)
        {
            menuState = -1;
            stopMusic();
            lcd_draw_clear(0,0,480,800,0xffffff);
            bmp_show("home.bmp",30,168);
            continue;
        }
        //从右上往左下滑动
        else if(end_y-start_y>50 && start_x-end_x>50 && menuState!=2)
        {
            stopMusic();
            menuState = 2;
            continue;
        }
        //向上滑动
        else if(abs(end_x-start_x)<50 && start_y-end_y>50 && menuState!=0)
        {
            menuState = 0;
            stopMusic();
            lcd_draw_clear(0,0,480,800,0xffffff);
            bmp_show("picture.bmp",269,184);
            continue;
        }
        //向下滑动
        else if (abs(end_x-start_x)<50 && end_y-start_y>50 && menuState!=1)
        {
            menuState = 1;
            musicState = -1;
            lcd_draw_clear(0,0,480,800,0xffffff);
            showMenu(0);
            stopMusic();
            continue;
        }
        
        //图片播放
        if(menuState == 0)
        {
            if(end_x-start_x > 50)
            {
                stopMusic();
                pid = fork();
                if(pid>0)
                {
                    if(++k>4)
                        k=0;
                    lcd_draw_clear(0,0,480,800,0x000000);
                    bmp_show(bmp[k],0,0);
                }
                else if(pid == 0)
                    playMusic(mp3_name[k%2]);
            }
            else if(start_x-end_x > 50)
            {
                stopMusic();
                pid = fork();
                if(pid>0)
                {
                    if(--k<0)
                        k=4;
                    lcd_draw_clear(0,0,480,800,0x000000);
                    bmp_show(bmp[k],0,0);
                }
                else if(pid == 0)
                    playMusic(mp3_name[k%2]);
            }
            else if((end_x>200 && end_x < 600) || (end_y>200 && end_y < 400))
            {
                pid = fork();
                if(pid == 0)
                {
                    stopMusic();
                    for(j=0;j<12;j++)
                    {
                        lcd_draw_clear(0,0,480,800,0x000000);
                        bmp_show(bmp[j],0,0);
                        sleep(1);
                    }
                    exit(0);
                }
                else if(pid > 0)
                {
                    printf("wait:%d\n",wait(NULL));
                }
            }
        }

        //音乐播放
        else if(menuState == 1)
        {
            int temp = getMenuValueByLocation(start_x,start_y,end_x,end_y);
            //1表示点击了开始按钮
            if(temp==1 && musicState==-1)
            {
                //第一次放歌
                musicState = 1;
                showMenu(1);
                pid = fork();
                if(pid == 0)
                {
                    playMusic(mp3_name[i++%2]);
                }
            }
            //2表示点击暂停
            else if(temp == 1 && musicState!=-1)
            {
                //放歌已经暂停 接下来应该是继续上一首 而不是重新开始
                if(musicState%2 == 0)
                {
                    showMenu(1);
                    system("killall -CONT madplay");
                }
                //还未放歌 应该点击开始放歌
                else
                {
                    showMenu(0);
                    system("killall -STOP madplay");
                }
                musicState ^= 1;
            }
            //3表示点击切换上一首
            else if(temp == 2)
            {
                showMenu(1);
                musicState ^= 1;
                pid = fork();
                if(--i == -1)
                    i = 1;
                if(pid == 0)
                {
                    stopMusic(); 
                    playMusic(mp3_name[i]);
                }
            }
            //4表示切换下一首
            else if(temp == 3)
            {
                showMenu(1);
                musicState ^= 1;
                pid = fork();
                if(++i == 2)
                    i = 0;
                if(pid == 0)
                {
                    stopMusic(); 
                    playMusic(mp3_name[i%2]); 
                }
            }
            //无效值
            else
            {
                printf("无效值\n");
            }
        }
        //视频播放
        else if(menuState == 1)
        {
            printf("播放视频\n");
        }
    }
    //3.解除屏幕，不再需要LCD显示时，解除屏幕    
    lcd_uninit(); //解除屏幕
}

