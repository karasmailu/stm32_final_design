#include "time.h"

int time_hour = 0;
int time_min = 0;
int dev_Charge = 0;
int TIME_OUT = 0;

float U 		= 0;	 /* 电压 */
float A 		= 0;   /* 电流 */
float W 		= 0;   /* 电功率 */
float kWh 	= 0;	 /* 电量 */
float Q 		= 0;   /* 功率因数 */
float Co2 	= 0;   /* 二氧化碳 */
float temp 	= 0;   /* 温度 */
float Hz 		= 0;   /* 频率 */		

/*
************************************************************
*	函数名称：	Tim4_Init
*
*	函数功能：	定时器4初始化
*
*	入口参数：	无
*
*	返回参数：	无
*
*	说明：		使用定时器定时固定的时间（时、分、秒）
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
*	函数名称：	Tim3_Init
*
*	函数功能：	Tim3初始化
*
*	入口参数：	per 计数次数，psc 预分频系数
*
*	返回参数：	无
*   
*	说明：      使用定时器3每隔一段时间获取IM1281B的电压电流等参数   		
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
  * @brief  定时器2初始化
  * @param  per 重装系数 int 0-65535	见time.h
  * @param  pcs 预分频系数				见time.h
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
//		UsartPrintf(USART1, "%d ：%d \r\n",APP_Hour,APP_Min);
//		/* 15秒上传一次信息 */
//		OneNet_SendData_APP_mode();
//    }
//    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
//}

/*
************************************************************
*	函数名称：	TIM3_IRQHandler
*
*	函数功能：	定时发送Modbus协议获取IM1281B数据
*
*	入口参数：	无
*
*	返回参数：	无
*
*	说明：		配置成3秒一次
************************************************************
*/
extern int cur_mode;
void TIM3_IRQHandler(void){
    /* 获取IM1281B电压电流数据 8个数据，每个占用4个字节，3秒获取一次 */
    /* 数据为 	电压[3-6]、	单位0.0001V	   
				电流[7-10]、单位0.0001A		
				有功功率[11-14]、单位0.0001W
				有功电能[15-18]、单位0.0001kWh
				功率因数[19-22]、单位0.001
				二氧化碳[23-26]、单位0.0001kg
				温度[27-30]、单位0.01°C	 
				频率[31-34]、单位0.01Hz */
    /* IM1281B 采用Modbus协议发送Modbus协议报文获取数据 */
    unsigned char cmd[] = {0x01,0x03,0x00,0x48,0x00,0x08,0xC4,0x1A};
    if(TIM_GetFlagStatus(TIM3, TIM_IT_Update)){
		/* 时间模式与金钱模式 */
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
		
		/* 应用模式 */
		if(cur_mode == APP_MODE){
			APP_Min+=10;
			if(APP_Min >= 60){
				APP_Hour++;
				APP_Min = 0;
			}
//			UsartPrintf(USART1, "%d:%d\r\n",APP_Hour,APP_Min);
			OneNet_SendData_APP_mode();						
		}
		
		/* 发送采集数据命令 */
        Usart_SendString(USART3, cmd, sizeof(cmd));
        DelayXms(500);
		
		/* 调试数据 ---- 打印返回数据 */
		UsartPrintf(USART1, "------------------- IM1281B ---------------------\r\n");
		for(int i = 0; i < 38; i++){
			UsartPrintf(USART1, "IM1281B_buf[%d] = 0x%02x\r\n",i,IM1281B_buf[i]);
		}
		UsartPrintf(USART1, "------------------- IM1281B ---------------------\r\n\r\n");
		
		/* 16进制转10进制 数据转换 */
        IM1281B_Data_Change( IM1281B_buf, IM1281B_Data);
		
		U 	 = IM1281B_Data[0]/10000.0;		/* 电压 */
		A 	 = IM1281B_Data[1]/10000.0;		/* 电流 */
		W 	 = IM1281B_Data[2]/10000.0;		/* 电功率 */
		kWh  = IM1281B_Data[3]/10000.0;		/* 电量 */
		Q 	 = IM1281B_Data[4]/1000.0;		/* 功率因数 */
		Co2  = IM1281B_Data[5]/10000.0;		/* 二氧化碳 */
		temp = IM1281B_Data[6]/100.0;		/* 温度 */
		Hz 	 = IM1281B_Data[7]/100.0;		/* 频率 */		
		
		/* 调试数据 ---- 打印转换数据 */
		UsartPrintf(USART1, "----------------- IM1281B Data ------------------\r\n");
		for(int i = 0; i < 8; i++){
			UsartPrintf(USART1, "data[%d] = %d\r\n",i,IM1281B_Data[i]);
		}
		UsartPrintf(USART1, "----------------- IM1281B Data ------------------\r\n");		
		
		/* 清除转换数据 */
		memset(IM1281B_Data,0,sizeof(IM1281B_Data));				
    }
    TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
}

