#include "led.h"
#include "relays.h"



/*
************************************************************
*	函数名称：	led_Init
*
*	函数功能：	led初始化
*
*	入口参数：	无
*
*	返回参数：	无
*
*	说明：		点亮LED时需要调用
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
*	函数名称：	led_Flash
*
*	函数功能：	led闪烁
*
*	入口参数：	无
*
*	返回参数：	无
*
*	说明：		点亮LED时需要调用
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




