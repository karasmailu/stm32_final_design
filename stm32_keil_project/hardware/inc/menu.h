#ifndef _menu_H
#define _menu_H

//����Э���
#include "onenet.h"

//�����豸
#include "esp8266.h"

//Ӳ������
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

//ģʽ�궨��
#define TIME_MODE        0
#define MONEY_MODE       1
#define CHARGE_MODE      2
#define FIND_MODE        3
#define APP_MODE         4
#define NO_MODE          5

//֧����ʽ�궨��
#define PAY_MODE_APP     0
#define PAY_MODE_IC      1

extern int Min;		/* ���� */	
extern int Hour;	/* Сʱ */


int Menu1(void);
void money_mode(void);
void time_mode(void);
void charge_mode(void);
void test_menu(void);
void find_mode(void);
void app_mode(void);
void OLED_Show_Data(double U,double A,double kWh);

#endif
