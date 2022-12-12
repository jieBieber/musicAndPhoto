#ifndef __LCD_H__
#define __LCD_H__

/* open 的头文件 */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
/* close 的头文件 */
#include <unistd.h>
/* strlen的头文件 */
#include <string.h> //==>提供字符串操作函数
#include <sys/mman.h>
#include "lcd.h"

extern int lcd_fd; //保存着LCD屏幕的描述符,open的返回值
extern int *plcd;  //指向LCD屏映射的内存地址,mmap的返回值

/*
 *	lcd_init:lcd屏幕初始化函数，
 *			负责打开并映射LCD屏到内存
 *	arg：
 *		NONE
 *	return:
 *		NONE
**/
int lcd_init(void);

/*
 *	lcd_init:解除lcd屏幕函数，
 *			负责解除映射和关闭LCD屏文件
 *	arg：
 *		NONE
 *	return:
 *		NONE
**/
void lcd_uninit(void);

/*
 *	lcd_draw_point画点函数，用来将参数指定的坐标像素点显示成指定颜色
 *	arg：
 *		@x：像素点的X轴坐标
 *		@y：像素点的Y轴坐标
 *		@color：该像素点要显示的颜色
 *	return：
 *		NONE
**/
void lcd_draw_point(int x,int y,int color);


/*
 *	lcd_draw_clear清屏函数，用来将指定位置指定大小的矩形范围显示为同一种颜色
 *	arg：
 *		@x0：清屏起始点的X轴坐标
 *		@y0：清屏起始点的Y轴坐标
 *		@w：清屏范围的宽度
 *		@h：清屏范围的高度
 *		@color：清屏显示的颜色
 *	return：
 *		NONE
**/
void lcd_draw_clear(int x0,int y0,int w,int h,unsigned int color);



#endif
