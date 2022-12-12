#include "lcd.h"
/* 颜色
0xffffff-白色    0x000000-黑色  0x0ff000-绿色
0xff00f0-紫色    0xffff00-黄色  0x0FF0F0-蓝色
*/

//保存着LCD屏幕的描述符,open的返回值
int lcd_fd; 
//指向LCD屏映射的内存地址,mmap的返回值
int *plcd;  
/*
 *	lcd_init:lcd屏幕初始化函数，
 *			负责打开并映射LCD屏到内存
 *	arg：
 *		NONE
 *	return:
 *		-1:打开文件失败
 *      MAP_FAILED:文件映射失败
**/
int lcd_init(void)
{
    /* 打开文件 */
    lcd_fd = open("/dev/fb0",O_RDWR);
    if(-1 == lcd_fd)
    {
        return -1;
    }
    plcd = (unsigned int*)mmap(NULL, //系统自动选择映射地址
        800*480*32/4,//LCD屏 800*480像素点的32位屏
        PROT_WRITE|PROT_READ, //文件描述符是可读可写的
        MAP_SHARED, //共享映射，操作映射内存会同步到文件
        lcd_fd, //要映射的文件
        0); //从文件头开始映射

    return *plcd;
}

/*
 *	lcd_init:解除lcd屏幕函数，
 *			负责解除映射和关闭LCD屏文件
 *	arg：
 *		NONE
 *	return:
 *		NONE
**/
void lcd_uninit(void)
{
    /* 解除映射 */
    munmap(plcd,800*480*32/4);
    /* 关闭文件（不再操作该文件，则记得关闭，避免浪费内核资源 */
    close(lcd_fd);
}

/*
 *	lcd_draw_point画点函数，用来将参数指定的坐标像素点显示成指定颜色
 *	arg：
 *		@x：像素点的X轴坐标
 *		@y：像素点的Y轴坐标
 *		@color：该像素点要显示的颜色
 *	return：
 *		NONE
**/
void lcd_draw_point(int x,int y,int color)
{
    //给坐标位 (x,y)像素点显示
    *(plcd+y*800+x) = color; 
}


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
void lcd_draw_clear(int x0,int y0,int h,int w,unsigned int color)
{
    int x,y;
    for(y=y0;y<h;y++)
    {
        for(x=x0;x<w;x++)
        {
            //给坐标位 (x,y)像素点显示 黄色
            lcd_draw_point(x,y,color); 
        }
    }
}



