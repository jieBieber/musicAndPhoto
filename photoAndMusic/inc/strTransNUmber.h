#ifndef _TEST_H
#define __TEST_H

#include "stdio.h"
#include "string.h"
#include "stdlib.h"

/*************************************
* Str_to_digit:字符串转换成数字
* arg:
*       char *str:待转换的字符串
* return:
*	    -1:传入参数错误 
*	    int digit:转换得到的数字
************************************/
int  Str_to_digit(unsigned char *str);

/***********************************************
*  Sixtheen_to_ten:十六进制数转换成十进制数  
*  arg:
*  		unsigned char*str:传入的十六进制的数组 
*  return:
* 		int:返回转换后的十进制值 
***********************************************/
int Sixtheen_to_ten(unsigned char *str);

/***********************************************
* 	Str_to_Digit:字符串转换成 
*   arg:
*		int num:待转换的数字 
* 		unsigned char*str：存放转换后的字符串 
* 	return： 
*		int：返回值 
************************************************/
int Digit_to_Str(int num,unsigned char*str);

#endif 
