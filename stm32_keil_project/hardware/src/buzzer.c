#include "buzzer.h"

int SAFE_FLAG = 0;


/**
  * @brief  buzzer init function
  * @param  None 
  * @retval None
  */
void buzzer_init(void){

	/* GPIO config */
    GPIO_InitTypeDef GPIO_InitTypeStruct;
    RCC_APB2PeriphClockCmd(BUZZER_RCC_PORT, ENABLE);
    
    GPIO_InitTypeStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitTypeStruct.GPIO_Pin = BUZZER_PIN;
    GPIO_InitTypeStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(BUZZER_PORT, &GPIO_InitTypeStruct);
    
	/* GPIO init */
    GPIO_ResetBits(BUZZER_PORT,BUZZER_PIN);

}



/**
  * @brief  
  * @param  None 
  * @retval None
  */
void safe(float U,float A){
	if(U*A >= MAX_POWER){
		RELAYS_OFF;
		SAFE_FLAG = 1;
		for(int i = 0;i < 3; i++){
			BUZZER_ON;
			DelayMs(1000);
		}
		BUZZER_OFF;
	}
}




