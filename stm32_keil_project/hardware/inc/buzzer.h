#ifndef __BUZZER_H_
#define __BUZZER_H_

#include "stm32f10x.h"
#include "relays.h"
#include "delay.h"



#define MAX_POWER			40

#define BUZZER_RCC_PORT    	RCC_APB2Periph_GPIOA    
#define BUZZER_PORT        	GPIOA
#define BUZZER_PIN         	GPIO_Pin_0

#define BUZZER_OFF          GPIO_ResetBits(BUZZER_PORT,BUZZER_PIN)
#define BUZZER_ON         	GPIO_SetBits(BUZZER_PORT,BUZZER_PIN)

extern int SAFE_FLAG;

void buzzer_init(void);
void safe(float U,float A);

#endif




