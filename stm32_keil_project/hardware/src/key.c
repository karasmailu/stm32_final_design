#include "key.h"



void KEY_init(void){

	GPIO_InitTypeDef GPIO_InitStructure; //定义结构体变量
	
    /* GPIO config*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;	   //选择你要设置的IO口
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;  
	GPIO_Init(GPIOB,&GPIO_InitStructure);		  /* 初始化GPIO */
    
}


int key_Scan(int mode){
	static u8 key=1;
	
	if(mode==1) //连续按键按下
		key=1;
	if(key==1&&(  GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12) ==0
                ||GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13) ==0
                ||GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) ==0
                ||GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15) ==0)) //任意一个按键按下
	{
		DelayXms(10);  //消抖
		key=0;
		if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12) ==0)
			return UP_Btn; 
		else if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13) ==0)
			return Down_Btn; 
		else if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) ==0)
			return Select_Btn; 
		else if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15) ==0)
			return Check_Btn; 
	}
	else if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12) ==1
            &&GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13) ==1
            &&GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) ==1
            &&GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15) ==1)    //无按键按下
		key=1;
	return 0;
}





