#ifndef _MUSIC_H_
#define _MUSIC_H_

#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "bmp.h"

/*
* stopMusic:用来停止播放音乐
* arg:无
* return:无
*/
void stopMusic(void);

/*
* playMusic:用来播放音乐
* arg:无
* return:无
*/
void playMusic(char*musicName);


/*
* showMenu:用来显示播放音乐的菜单
* arg:
*    flag:
*           1:显示暂停
*           0:显示开始
* return:无
*/
void showMenu(int flag);

/*
* showMenu:用来显示播放音乐的菜单
* arg:
*      @start_x：指向一个int型空间，用来保存按下时触摸点的X坐标
*      @start_y：指向一个int型空间，用来保存按下时触摸点的Y坐标
*      @end_x：指向一个int型空间，用来保存松开时触摸点的X坐标
*      @end_y：指向一个int型空间，用来保存松开时触摸点的Y坐标
* return:
*       整型：-1表示点击错误  1表示点击了开始按钮
*             2表示点击暂停  3表示点击切换上一首
*             4表示切换下一首
*/
int getMenuValueByLocation(int start_x,int start_y,int end_x,int end_y);

#endif



