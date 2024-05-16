#ifndef _key_H
#define _key_H

#include "stm32f10x.h"
#include "delay.h"
#include "led.h"
#include "menu.h"

#define KEY1_PASS       1
#define KEY2_PASS       2
#define KEY3_PASS       3
#define KEY4_PASS       4

#define Select_Btn      14
#define Check_Btn       15
#define UP_Btn          12
#define Down_Btn        13


void KEY_init(void);
int key_Scan(int mode);


#endif
