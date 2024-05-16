#include "relays.h"

/*
************************************************************
*	函数名称：	RELAYS_Init
*
*	函数功能：	继电器初始化
*
*	入口参数：	无
*
*	返回参数：	无
*
*	说明：		使用到继电器需要调用此函数
************************************************************
*/
void RELAYS_Init(void){
    
    /* GPIO_InitTypeStruct */
    GPIO_InitTypeDef GPIO_InitTypeStruct;
    RCC_APB2PeriphClockCmd(RELAYS_RCC_PORT, ENABLE);
    
    /* GPIO_config */
    GPIO_InitTypeStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitTypeStruct.GPIO_Pin = RELAYS_PIN;
    GPIO_InitTypeStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(RELAYS_PORT, &GPIO_InitTypeStruct);
    
    /* GPIO_ResetBits */
    GPIO_ResetBits(RELAYS_PORT,RELAYS_PIN);

}







