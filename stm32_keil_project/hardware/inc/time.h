#ifndef _TIME_H
#define _TIME_H

#include "stm32f10x.h"
#include "led.h"
#include "menu.h"
#include "IM1281B.h"
#include "usart.h"
#include "delay.h"
#include <string.h>
#include "onenet.h"

#define     PER_1s        2000  
#define     PER_1min      2000*60
#define     PSC_CONST     36000-1

extern int time_hour;
extern int time_min;
extern int dev_Charge;
extern int TIME_OUT;

extern float U 	;	//��ѹ
extern float A 	;	//����
extern float W 	;	//�繦��
extern float kWh 	;	//����
extern float Q 	;	//��������
extern float Co2 	;	//������̼
extern float temp  ;	//�¶�
extern float Hz 	;	//Ƶ��

//timer��ʼ��
void Tim3_Init(u16 per,u16 psc);

#endif
