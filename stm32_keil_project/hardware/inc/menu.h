#ifndef _menu_H
#define _menu_H

//网络协议层
#include "onenet.h"

//网络设备
#include "esp8266.h"

//硬件驱动
#include "delay.h"
#include "buzzer.h"
#include "usart.h"
#include "led.h"
#include "OLED.h"
#include "time.h"
#include "key.h"
#include "menu.h"
#include "IM1281B.h"
#include "relays.h"
#include "rc522_config.h"
#include "rc522_function.h"

//模式宏定义
#define TIME_MODE        0
#define MONEY_MODE       1
#define CHARGE_MODE      2
#define FIND_MODE        3
#define APP_MODE         4
#define NO_MODE          5

//支付方式宏定义
#define PAY_MODE_APP     0
#define PAY_MODE_IC      1

extern int Min;		/* 分钟 */	
extern int Hour;	/* 小时 */


int Menu1(void);
void money_mode(void);
void time_mode(void);
void charge_mode(void);
void test_menu(void);
void find_mode(void);
void app_mode(void);
void OLED_Show_Data(double U,double A,double kWh);

#endif
