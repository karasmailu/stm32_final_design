//单片机头文件
#include "stm32f10x.h"

//网络协议层
#include "onenet.h"

//网络设备
#include "esp8266.h"

//硬件驱动
#include "buzzer.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "OLED.h"
#include "time.h"
#include "key.h"
#include "menu.h"
#include "IM1281B.h"
#include "relays.h"
#include "rc522_config.h"
#include "rc522_function.h"

//C库
#include <string.h>

//2023.10.24 修改时钟频率，调节串口1
//2023.10.27 调节LED状态
//2023.10.31 调节esp8266连接wifi
//2023.10.31 连接onenet服务器
//2023.10.31 设备登录成功
//2023.11.3  设备发送数据成功
//2024.3.7   OLED模块显示调试、定时器4、3调试成功
//2024.3.18  完成所有基础硬件的调试	
//2024.3.20  完成时间模式、金额模式的操作流程
//2024.3.24  添加应用支付、IC支付功能分支
//2024.3.28  完成时间模式 ----> 应用支付 ----> 数据上云 功能分支
//2024.4.1   完成应用模式下数据采集APP控制
//2024.4.2   优化代码、将原本使用的三个定时器优化成一个

/*
************************************************************
*	函数名称：	Hardware_Init
*
*	函数功能：	硬件初始化
*
*	入口参数：	无
*
*	返回参数：	无
*
*	说明：		初始化单片机功能以及外接设备
************************************************************
*/
void Hardware_Init(void)
{
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//中断控制器分组设置
		Delay_Init(); //systick初始化
		Usart1_Init(115200); //串口1，打印信息用
		buzzer_init();
		OLED_Init();
		led_Init(); //初始化LED
		KEY_init();
		IM1281B_Init(4800);
		RC522_SPI_Config();
		RELAYS_Init();
    ESP8266_Init();	//初始化ESP8266
//	UsartPrintf(USART_DEBUG, "Hardware init OK\r\n");
    
	//连接onenet服务器
//    UsartPrintf(USART_DEBUG, "Connet ONETNET Server ....\r\n");
    while(ESP8266_SendCmd(ONENET_SERVER_INFO, "CONNECT"));
    DelayXms(500);
//    UsartPrintf(USART_DEBUG, "Connet ONETNET Server succ \r\n");
    
    //连接onenet设备
//    UsartPrintf(USART_DEBUG, "Device CONNECT ....\r\n");
    while(OneNet_DevLink());
    DelayXms(500);
//    UsartPrintf(USART_DEBUG, "Device CONNECT succ \r\n");
		OneNet_SendData();
		OneNet_SendData_APP_mode();
    OLED_ShowString(0,32, "6.ONENET Init OK", OLED_8X16);
		OLED_Update();
}


/*
************************************************************
*	函数名称：	main
*
*	函数功能：	
*
*	入口参数：	无
*
*	返回参数：	0
*
*	说明：		
************************************************************
*/
int cur_mode = NO_MODE;
int main(void)
{
		Hardware_Init();//初始化外围硬件
		OneNET_Subscribe();//订阅发布的主题	
		U = A = kWh = Hour = Min = 0;

		while(1)
		{	
				OLED_Clear();
				OLED_Update();
				int menu2 = Menu1();                        
				switch(menu2){
					case TIME_MODE   :time_mode();  break;
					case MONEY_MODE  :money_mode(); break;  
					case CHARGE_MODE :charge_mode();break;
					case FIND_MODE   :find_mode();  break;
					case APP_MODE	 	 :app_mode();		break;	
					default:break;
				}
				cur_mode = NO_MODE;
				U = A = kWh = Hour = Min = 0;
		}
}











