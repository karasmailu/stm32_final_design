#ifndef _LED_H
#define _LED_H


#include "stm32f10x.h"
#include "delay.h"

#define LED_RCC_PORT    RCC_APB2Periph_GPIOC    
#define LED_PORT        GPIOC
#define LED_PIN         GPIO_Pin_13

#define LED_ON          GPIO_ResetBits(LED_PORT,LED_PIN)
#define LED_OFF         GPIO_SetBits(LED_PORT,LED_PIN)


void led_Init(void);
void led_Flash(void);


#endif
