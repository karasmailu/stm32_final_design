#include "led.h"
#include "relays.h"



/*
************************************************************
*	�������ƣ�	led_Init
*
*	�������ܣ�	led��ʼ��
*
*	��ڲ�����	��
*
*	���ز�����	��
*
*	˵����		����LEDʱ��Ҫ����
************************************************************
*/
void led_Init(void){
    /* GPIO config */
    GPIO_InitTypeDef GPIO_InitTypeStruct;
    RCC_APB2PeriphClockCmd(LED_RCC_PORT, ENABLE);
    
    GPIO_InitTypeStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitTypeStruct.GPIO_Pin = LED_PIN;
    GPIO_InitTypeStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED_PORT, &GPIO_InitTypeStruct);
    
	/* GPIO init */
    GPIO_SetBits(LED_PORT,LED_PIN);

}





/*
************************************************************
*	�������ƣ�	led_Flash
*
*	�������ܣ�	led��˸
*
*	��ڲ�����	��
*
*	���ز�����	��
*
*	˵����		����LEDʱ��Ҫ����
************************************************************
*/
void led_Flash(void){

    DelayXms(500);
//	RELAYS_ON;
    LED_ON;
    DelayXms(500);
    LED_OFF;
//	RELAYS_OFF;
}




