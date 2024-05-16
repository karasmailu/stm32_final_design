#include "relays.h"

/*
************************************************************
*	�������ƣ�	RELAYS_Init
*
*	�������ܣ�	�̵�����ʼ��
*
*	��ڲ�����	��
*
*	���ز�����	��
*
*	˵����		ʹ�õ��̵�����Ҫ���ô˺���
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







