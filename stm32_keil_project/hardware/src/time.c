#include "time.h"

int time_hour = 0;
int time_min = 0;
int dev_Charge = 0;
int TIME_OUT = 0;

float U 		= 0;	 /* ��ѹ */
float A 		= 0;   /* ���� */
float W 		= 0;   /* �繦�� */
float kWh 	= 0;	 /* ���� */
float Q 		= 0;   /* �������� */
float Co2 	= 0;   /* ������̼ */
float temp 	= 0;   /* �¶� */
float Hz 		= 0;   /* Ƶ�� */		

/*
************************************************************
*	�������ƣ�	Tim4_Init
*
*	�������ܣ�	��ʱ��4��ʼ��
*
*	��ڲ�����	��
*
*	���ز�����	��
*
*	˵����		ʹ�ö�ʱ����ʱ�̶���ʱ�䣨ʱ���֡��룩
************************************************************
*/
//void Tim4_Init(u16 per,u16 psc){
//    
//    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
//    NVIC_InitTypeDef NVIC_InitStructure;
//    
//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
//    
//    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
//    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
//    TIM_TimeBaseInitStructure.TIM_Period = per;
//    TIM_TimeBaseInitStructure.TIM_Prescaler = psc;
//    TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);

//    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
//    TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
//    
//    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
//    NVIC_Init(&NVIC_InitStructure);
//    
//    TIM_Cmd(TIM4,ENABLE);
//    
//}


/*
************************************************************
*	�������ƣ�	Tim3_Init
*
*	�������ܣ�	Tim3��ʼ��
*
*	��ڲ�����	per ����������psc Ԥ��Ƶϵ��
*
*	���ز�����	��
*   
*	˵����      ʹ�ö�ʱ��3ÿ��һ��ʱ���ȡIM1281B�ĵ�ѹ�����Ȳ���   		
************************************************************
*/
void Tim3_Init(u16 per,u16 psc){
  
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
    
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period = per;
    TIM_TimeBaseInitStructure.TIM_Prescaler = psc;
    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);

    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
    TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
    
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
    NVIC_Init(&NVIC_InitStructure);
    
    TIM_Cmd(TIM3,ENABLE);
    
}


/**
  * @brief  ��ʱ��2��ʼ��
  * @param  per ��װϵ�� int 0-65535	��time.h
  * @param  pcs Ԥ��Ƶϵ��				��time.h
  *   
  * @retval None
  */
//void Tim2_Init(u16 per,u16 psc){
//  
//    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
//    NVIC_InitTypeDef NVIC_InitStructure;
//    
//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
//    
//    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
//    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
//    TIM_TimeBaseInitStructure.TIM_Period = per;
//    TIM_TimeBaseInitStructure.TIM_Prescaler = psc;
//    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);

//    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
//    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
//    
//    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
//    NVIC_Init(&NVIC_InitStructure);
//    
//    TIM_Cmd(TIM2,ENABLE);
//    
//}




int APP_Hour = 0;
int APP_Min = 0;
//void TIM2_IRQHandler(void){
//	
//    if(TIM_GetFlagStatus(TIM2, TIM_IT_Update)){
//		APP_Min+=15;
//		if(APP_Min >= 60){
//			APP_Hour++;
//			APP_Min = 0;
//		}
//		UsartPrintf(USART1, "%d ��%d \r\n",APP_Hour,APP_Min);
//		/* 15���ϴ�һ����Ϣ */
//		OneNet_SendData_APP_mode();
//    }
//    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
//}

/*
************************************************************
*	�������ƣ�	TIM3_IRQHandler
*
*	�������ܣ�	��ʱ����ModbusЭ���ȡIM1281B����
*
*	��ڲ�����	��
*
*	���ز�����	��
*
*	˵����		���ó�3��һ��
************************************************************
*/
extern int cur_mode;
void TIM3_IRQHandler(void){
    /* ��ȡIM1281B��ѹ�������� 8�����ݣ�ÿ��ռ��4���ֽڣ�3���ȡһ�� */
    /* ����Ϊ 	��ѹ[3-6]��	��λ0.0001V	   
				����[7-10]����λ0.0001A		
				�й�����[11-14]����λ0.0001W
				�й�����[15-18]����λ0.0001kWh
				��������[19-22]����λ0.001
				������̼[23-26]����λ0.0001kg
				�¶�[27-30]����λ0.01��C	 
				Ƶ��[31-34]����λ0.01Hz */
    /* IM1281B ����ModbusЭ�鷢��ModbusЭ�鱨�Ļ�ȡ���� */
    unsigned char cmd[] = {0x01,0x03,0x00,0x48,0x00,0x08,0xC4,0x1A};
    if(TIM_GetFlagStatus(TIM3, TIM_IT_Update)){
		/* ʱ��ģʽ���Ǯģʽ */
		if(cur_mode == TIME_MODE || cur_mode == MONEY_MODE){
			if(time_min != 0){
				time_min--;
			}		
			if(time_hour != 0 && time_min <= 0){
				time_hour--;
				time_min = 59;
			}
			if(time_hour <= 0 && time_min <= 0){
				TIM_DeInit(TIM3);
				TIME_OUT = 1;
			}
//			UsartPrintf(USART1, "%d:%d\r\n",time_hour,time_min);
			OneNet_SendData();
		}
		
		/* Ӧ��ģʽ */
		if(cur_mode == APP_MODE){
			APP_Min+=10;
			if(APP_Min >= 60){
				APP_Hour++;
				APP_Min = 0;
			}
//			UsartPrintf(USART1, "%d:%d\r\n",APP_Hour,APP_Min);
			OneNet_SendData_APP_mode();						
		}
		
		/* ���Ͳɼ��������� */
        Usart_SendString(USART3, cmd, sizeof(cmd));
        DelayXms(500);
		
		/* �������� ---- ��ӡ�������� */
		UsartPrintf(USART1, "------------------- IM1281B ---------------------\r\n");
		for(int i = 0; i < 38; i++){
			UsartPrintf(USART1, "IM1281B_buf[%d] = 0x%02x\r\n",i,IM1281B_buf[i]);
		}
		UsartPrintf(USART1, "------------------- IM1281B ---------------------\r\n\r\n");
		
		/* 16����ת10���� ����ת�� */
        IM1281B_Data_Change( IM1281B_buf, IM1281B_Data);
		
		U 	 = IM1281B_Data[0]/10000.0;		/* ��ѹ */
		A 	 = IM1281B_Data[1]/10000.0;		/* ���� */
		W 	 = IM1281B_Data[2]/10000.0;		/* �繦�� */
		kWh  = IM1281B_Data[3]/10000.0;		/* ���� */
		Q 	 = IM1281B_Data[4]/1000.0;		/* �������� */
		Co2  = IM1281B_Data[5]/10000.0;		/* ������̼ */
		temp = IM1281B_Data[6]/100.0;		/* �¶� */
		Hz 	 = IM1281B_Data[7]/100.0;		/* Ƶ�� */		
		
		/* �������� ---- ��ӡת������ */
		UsartPrintf(USART1, "----------------- IM1281B Data ------------------\r\n");
		for(int i = 0; i < 8; i++){
			UsartPrintf(USART1, "data[%d] = %d\r\n",i,IM1281B_Data[i]);
		}
		UsartPrintf(USART1, "----------------- IM1281B Data ------------------\r\n");		
		
		/* ���ת������ */
		memset(IM1281B_Data,0,sizeof(IM1281B_Data));				
    }
    TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
}

