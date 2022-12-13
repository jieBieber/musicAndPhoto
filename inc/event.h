#ifndef _EVENT_H
#define _EVENT_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>

/*
 *  get_inputevent: 用来获取触摸屏输入事件
 *  arg：
 *      @start_x：指向一个int型空间，用来保存按下时触摸点的X坐标
 *      @start_y：指向一个int型空间，用来保存按下时触摸点的Y坐标
 *      @end_x：指向一个int型空间，用来保存松开时触摸点的X坐标
 *      @end_y：指向一个int型空间，用来保存松开时触摸点的Y坐标
 *  return：
 *      成功返回0
 *      失败返回-1
**/
int get_inputevent(int*start_x,int*start_y,int*end_x,int*end_y);

int key();

#endif 

