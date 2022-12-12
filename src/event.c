#include "event.h"

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
int get_inputevent(int*start_x,int*start_y,int*end_x,int*end_y)
{
    int fd = 0;
    int ret = 0;
    int abs_x,abs_y;//记录触摸点的(x,y)坐标
    struct input_event ev;	//保存获取到的输入事件

    /* 1.打开输入事件设备文件 */
    fd = open("/dev/input/event0",O_RDWR);	//event0是触摸屏的输入事件设备文件
    if(-1 == fd)
    {
        perror("opening failture\n");
        return -1;
    }

    /* 2.读取输入事件 */
        /* 输入子系统往往会将一个设备的一次动作分成几个输入事件上传给应用层
        	比如： 触摸屏的一次触摸 就会被分成：
        		ABS_X	触摸点的X轴事件
        		ABS_Y	触摸点的Y轴事件
        		等内容
        	因此获取输入事件时，通常会采用循环的方式获取，以确保将一次动作的所有事件全部获取
        */
    while(1)
    {
        ret = read(fd,&ev,sizeof(ev)); //读取一整个输入事件的数据量，存入结构体ev中
        if(sizeof(ev) == ret) //确保读取到的就是一整个输入事件
        {
    		if(ev.type == EV_ABS)	//表示产生了触摸屏事件
            {
                if(ev.code == ABS_X)	//事件编码为X轴触发
                {
                    //此时的value就是触摸点X轴的坐标
                    abs_x	=	ev.value;
                }
                else if(ev.code == ABS_Y)	//事件编码为Y轴触发
                {
                    //此时的value就是触摸点y轴的坐标
                    abs_y	=	ev.value;
                }
            }
            else if(ev.type == EV_KEY && ev.code == BTN_TOUCH)	//触摸屏触摸事件：将触摸屏当成一个按键来识别（触摸开关）
            {
                if(ev.value == 1)
                {
                    //表示手指触摸触摸屏的瞬间
                    *start_x = abs_x;
                    *start_y = abs_y;
                }
                else if(ev.value == 0)
                {
                    //表示手指从触摸屏离开的瞬间
                    *end_x = abs_x;
                    *end_y = abs_y;
                    close(fd);
                    return 0;
                }
            }
                
        }
    }
}

