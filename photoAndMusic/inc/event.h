#ifndef _EVENT_H
#define _EVENT_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>

int get_inputevent(int*start_x,int*start_y,int*end_x,int*end_y);

int key();

#endif 

