#include "music.h"

/*
* stopMusic:用来停止播放音乐
* arg:无
* return:无
*/
void stopMusic(void)
{
    system("killall -9 madplay");
}

/*
* playMusic:用来播放音乐
* arg:无
* return:无
*/
void playMusic(char*musicName)
{
    execlp("madplay","madplay",musicName,NULL);
}

/*
* showMenu:用来显示播放音乐的菜单
* arg:
*    flag:
*           1:显示暂停
*           0:显示开始
* return:无
*/
void showMenu(int flag)
{
    //显示主题
    bmp_show("music.bmp",100,71);

    //显示上一首按钮
    bmp_show("12.bmp",100,208);

    //清除上一次的暂停或者是开始状态显示
    lcd_draw_clear(320,208,500,208,0xffffff);

    //显示暂停按钮  目前处于开始
    if(flag == 1)
        bmp_show("11.bmp",300,208);
    //显示开始按钮  目前处于暂停
    else
        bmp_show("10.bmp",300,208);

    //显示下一首按钮
    bmp_show("4.bmp",500,208);
}

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
int getMenuValueByLocation(int start_x,int start_y,int end_x,int end_y)
{
    //开始或者是暂停
    if(end_x>300 && end_x<=500 && end_y>208 && end_y<320)
    {
         return 1;
    }
    //上一首
    else if(end_x>100 && end_x<=300 && end_y>208 && end_y<320)
    {
        return 2;
    }
    //下一首
    else if(end_x>500 && end_x<=700 && end_y>208 && end_y<320)
    {
        return 3;
    }

    return -1;
}




