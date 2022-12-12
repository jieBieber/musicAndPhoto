#ifndef _TOUCH_H
#define _TOUCH_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>	//输入子系统的头文件

#define TS_PATH "/dev/input/event0"
int getxy();

#endif 

