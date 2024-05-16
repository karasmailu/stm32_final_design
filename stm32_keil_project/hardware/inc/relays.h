#ifndef _RELAYS_H
#define _RELAYS_H


#include "stm32f10x.h"
#include "delay.h"

/* relays pin and port */
#define RELAYS_RCC_PORT    RCC_APB2Periph_GPIOC    
#define RELAYS_PORT        GPIOC
#define RELAYS_PIN         GPIO_Pin_14


/* relays ctrl func */
#define RELAYS_OFF          GPIO_ResetBits(RELAYS_PORT,RELAYS_PIN)
#define RELAYS_ON         	GPIO_SetBits(RELAYS_PORT,RELAYS_PIN)
#define RELAYS_STATE		GPIO_ReadOutputDataBit(RELAYS_PORT, RELAYS_PIN)


void RELAYS_Init(void);

#endif
