#ifndef _BMP_H
#define _BMP_H

#include "lcd.h"
#include <stdio.h>
/* open 的头文件 */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
/* close 的头文件 */
#include <unistd.h>
/* strlen的头文件 */
#include <string.h> 
#include <sys/mman.h>
#include "stdio.h"
#include "stdlib.h"

/*
* bmp_show:打开bmp文件,从文件特定位置读取数据并处理
* arg:
* @filename:字符串,指定要解析的bmp文件的名称
* @x0:整型数据,指定横坐标
* @y0:整型数据,指定纵坐标
* return：
* 成功返回0 失败返回-1
**/
int bmp_show(char * filename,int x0,int y0);

#endif 

