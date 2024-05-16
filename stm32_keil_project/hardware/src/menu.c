#include "menu.h"



int Min =  0;	/* 分钟 */	
int Hour = 0;	/* 小时 */
extern int cur_mode;


//==========================================================
//	函数名称：	select_pay_mode
//
//	函数功能：	OLED显示选择支付模式
//
//	入口参数：	无
//
//	返回参数：	无
//
//	说明：		
//==========================================================
int select_pay_mode(void){

    int flag = 0; 
	OLED_Show_Pay_Mode();
    while(1){
		/* 用户选项 */
		
		/* 按键扫描 */
        int key = key_Scan(0);
        if(key == Select_Btn){
            flag++;
			flag %= 2;
        }
		
		/* 返回用户的选择 */
        if(key == Check_Btn){
            return flag;
        }

        switch(flag){                
            case 0:{
                OLED_ShowChar(20, 17, '>', OLED_8X16);
				OLED_ShowChar(20, 34, ' ', OLED_8X16);
            }break;
			
            case 1:{
				OLED_ShowChar(20, 17, ' ', OLED_8X16);
                OLED_ShowChar(20, 34, '>', OLED_8X16);
            }break;
			
			default:break;
        }
		OLED_Update();
    }

}



//==========================================================
//	函数名称：	Menu1
//
//	函数功能：	显示一级菜单
//
//	入口参数：	无
//
//	返回参数：	无
//
//	说明：		
//==========================================================
int Menu1(void){
	/* 用户选项 */
    int flag = 0; 
    while(1){
		/* 按键扫描 */
        int key = key_Scan(0);
        if(key == Select_Btn){
            flag++;
			flag %= 5;
        }
		/* 返回用户的选择 */
        if(key == Check_Btn){
            return flag;
        }

		/* 显示菜单 */
        switch(flag){                
            case 0:{
								OLED_Clear();
								OLED_ShowString(39, 0, "SELECT",OLED_8X16);
								OLED_ReverseArea(0, 0, 127, 16);
                OLED_ShowChar(20, 17, '>', OLED_8X16);
								OLED_ShowChinese(31, 17,"时间模式");
                OLED_ShowChar(20, 34, ' ', OLED_8X16);
								OLED_ShowChinese(31, 35,"金额模式");
                OLED_Update();
            }break;
			
            case 1:{
                OLED_ShowChar(20, 17, ' ', OLED_8X16);
								OLED_ShowChinese(31, 17,"时间模式");
                OLED_ShowChar(20, 34, '>', OLED_8X16);
								OLED_ShowChinese(31, 35,"金额模式");
                OLED_Update();
            }break;
			
			case 2:{
				OLED_Clear();
				OLED_ShowString(39, 0, "SELECT",OLED_8X16);
				OLED_ReverseArea(0, 0, 127, 16);
                OLED_ShowChar(20, 17, '>', OLED_8X16);
				OLED_ShowChinese(31, 17,"卡片充值");
				OLED_ShowChinese(31, 35,"查询模式");
                OLED_Update();
            }break;
			
			case 3:{
				OLED_Clear();
				OLED_ShowString(39, 0, "SELECT",OLED_8X16);
				OLED_ReverseArea(0, 0, 127, 16);
                OLED_ShowChar(20, 35, '>', OLED_8X16);
				OLED_ShowChinese(31, 17,"卡片充值");
				OLED_ShowChinese(31, 35,"查询模式");
                OLED_Update();
            }break;
						
			case 4:{
				OLED_Clear();
				OLED_ShowString(39, 0, "SELECT",OLED_8X16);
				OLED_ReverseArea(0, 0, 127, 16);
                OLED_ShowChar(20, 17, '>', OLED_8X16);
				OLED_ShowChinese(31, 17,"应用模式");
                OLED_Update();
            }break;
			default:break;
        }
    }
}




//==========================================================
//	函数名称：	money_mode
//
//	函数功能：	金额模式
//
//	入口参数：	无
//
//	返回参数：	无
//
//	说明：		
//==========================================================
void money_mode(void){
    int flag = 0;
	int money = 0;
	cur_mode = MONEY_MODE;	
	int pay_mode = select_pay_mode();	
	OLED_Clear();
    while(1){			
		/* 扫描按键 */
		int key = key_Scan(0);
		switch (key){
			case Select_Btn:{
				flag++;
				flag %= 3;				
			}break;
			case Check_Btn:{
				Hour = time_hour = 0;
				Min = time_min = money*30;
				if(flag == 1 && pay_mode == PAY_MODE_APP){
					OLED_Show_App_Tip();
					DelayXms(2000);					
					Tim3_Init(PER_1s,PSC_CONST);
					RELAYS_ON;										
					while(1){
						/* 任意按键按下时退出 */
						OLED_Show_Data(U,A,kWh);						
						if(key_Scan(0) != 0 || TIME_OUT || SAFE_FLAG){
							RELAYS_OFF;
							TIM_DeInit(TIM3);
							TIME_OUT = 0;
							SAFE_FLAG = 0;
							Hour = Min = 0;
							OneNet_SendData();
							return;
						}
						safe(U,A);
						DelayXms(500);
						ESP8266_Clear();
					}
				}
				if(flag == 1 && pay_mode == PAY_MODE_IC){				
					OLED_Clear();
					OLED_ShowChinese(0, 0, "请放卡片");
					OLED_Update();
					RC522_Ctrl(PICC_DECREMENT,4,money);
					OLED_ShowChinese(0, 16, "卡片余额");OLED_ShowNum(70,16,RC522_Read(4), 3, OLED_8X16);
					OLED_ShowChinese(0, 32, "任意键退出");
					OLED_Update();
										
					Tim3_Init(PER_1s,PSC_CONST);
					RELAYS_ON;					
					
					while(1){
						/* 任意按键按下时退出 */
						OLED_Show_Data(U,A,kWh);						
						if(key_Scan(0) != 0 || TIME_OUT || SAFE_FLAG){
							RELAYS_OFF;
							TIM_DeInit(TIM3);
							TIME_OUT = 0;
							SAFE_FLAG = 0;
							Hour = Min = 0;
							OneNet_SendData();
							return;
						}	
						DelayXms(500);
						ESP8266_Clear();
					}				
				}
				if(flag == 2)return;
			}break;
			case UP_Btn:{
				money++;
                OLED_ShowNum(80, 0, money, 2, OLED_8X16);
			}break;
			case Down_Btn:{
				if(money <= 0){
					money = 0;
					continue;
				}
				money--;
				OLED_ShowNum(80, 0, money, 2, OLED_8X16);               				
			}break;
			default:break;
		}
		
		OLED_Clear();
		/* 显示菜单选项 */
        switch(flag){
            case 0:{
                OLED_ShowChar(0, 0, '>', OLED_8X16);
				OLED_ShowChinese(20, 0, "金额");OLED_ShowNum(80, 0, money, 2, OLED_8X16);
				OLED_ShowChinese(20, 17, "确认");
				OLED_ShowChinese(20, 35, "退出");
            }break;
                
            case 1:{
				OLED_ShowChinese(20, 0, "金额");OLED_ShowNum(80, 0, money, 2, OLED_8X16);
                OLED_ShowChar(0, 17, '>', OLED_8X16);
				OLED_ShowChinese(20, 17, "确认");
				OLED_ShowChinese(20, 35, "退出");								
            }break;
			
			case 2:{
				OLED_ShowChinese(20, 0, "金额");OLED_ShowNum(80, 0, money, 2, OLED_8X16);
				OLED_ShowChinese(20, 17, "确认");
                OLED_ShowChar(0, 34, '>', OLED_8X16);
				OLED_ShowChinese(20, 35, "退出");								
            }break;
			default:break;
        }
		OLED_Update();
    }	
}




//==========================================================
//	函数名称：	time_mode
//
//	函数功能：	时间模式
//
//	入口参数：	无
//
//	返回参数：	无
//
//	说明：		在时间模式下用户选择充电时间
//==========================================================
void time_mode(void){
	
	int flag = 0;
	cur_mode = TIME_MODE;
	float sumMoney = 0;	/* 总价 */
	
	/* 用户选择支付方式 */
	int pay_mode = select_pay_mode();
	OLED_Clear();

    while(1){	
		/* 扫描按键 */
		int key = key_Scan(0);

		/* 用户选项 */
		if(key == Select_Btn){
			flag++;
			flag %= 4;			
        }
		
		/* 确认时确定支付模式 */
		if(key == Check_Btn && flag == 2){			
			/* 将用户数据反馈到定时器 */
			time_hour = Hour;
			time_min = Min;			
			/* 计算总价 */
			sumMoney = Hour + Min;				
			switch(pay_mode){
				/* APP支付模式 */
				case PAY_MODE_APP:{
					/* 显示扫码下载APP提示 */
					OLED_Show_App_Tip();					
					/* 延时2秒 */
					for(int i = 0;i < 2;i++){
						DelayXms(1000);
					}										
					/* 开启定时器 */
					Tim3_Init(PER_1s,PSC_CONST);
					RELAYS_ON;
					
					/* 任意按键按下或定时结束退出 */
					while(1){
						OLED_Show_Data(U,A,kWh);
						
						if(key_Scan(0) != 0 || TIME_OUT || SAFE_FLAG){
							RELAYS_OFF;
							TIM_DeInit(TIM3);
							TIME_OUT = 0;
							SAFE_FLAG = 0;
							Hour = Min = 0;
							OneNet_SendData();
							return;
						}
						safe(U,A);
						DelayXms(500);
						ESP8266_Clear();
					}
				}
				
				/* IC卡支付模式 */
				case PAY_MODE_IC:{
					OLED_Clear();
					OLED_ShowChinese( 0, 0, "金额");
					OLED_ShowFloatNum(30,0, sumMoney, 2, 2, OLED_8X16);
					OLED_ShowChinese( 0, 16,"请放卡片");
					OLED_Update();

					OLED_ShowChinese(0, 16,"卡上金额");
					OLED_ShowNum(80, 16, RC522_Read(4), 3, OLED_8X16);
					RC522_Ctrl(PICC_DECREMENT,4,sumMoney);
					OLED_ShowChinese(0, 32,"卡上余额");
					OLED_ShowNum(80, 32, RC522_Read(4), 3, OLED_8X16);
					OLED_Update();
					for(int i = 0;i<2;i++){
						DelayXms(1000);
					}
					/* 开启定时器 */
					Tim3_Init(PER_1s,PSC_CONST);
					RELAYS_ON;
					while(1){						
						OLED_Show_Data(U,A,kWh);
						if(key_Scan(0) != 0 || TIME_OUT || SAFE_FLAG){
							TIM_DeInit(TIM3);
							TIME_OUT = 0;
							SAFE_FLAG = 0;
							Hour = Min = 0;
							RELAYS_OFF;
							return;
						}
						safe(U,A);
					}
				}
				default:break;
			}			
        }
        
        /* 退出选项 */
        if(key == Check_Btn && flag == 3){
			break;			
        }
		/* 数值增加并数值限制大小 */
        if(key == UP_Btn){
            if(flag == 0){
                Hour++;
                Hour %= 24;
                OLED_ShowNum(80, 0, Hour, 2, OLED_8X16);
            }
            if(flag == 1){
                Min++;
                Min %=60;
                OLED_ShowNum(80, 17, Min, 2, OLED_8X16);
            }
			OLED_Update();
        }
        /* 数值减少并数值限制大小 */
        if(key == Down_Btn){
            if(flag == 0 ){
                if(Hour == 0){
                    Hour = 23;
                    continue;
                }
                Hour--;
                OLED_ShowNum(80, 0, Hour, 2, OLED_8X16);                               
            }
            if(flag == 1){
                if(Min == 0){
                    Min = 59;
                    continue;
                }
                Min--;
                OLED_ShowNum(80, 17, Min, 2, OLED_8X16);               
            }
			OLED_Update();
        }
		OLED_Clear();		
		/* 显示菜单选项 */
        switch(flag){
            case 0:{
                OLED_ShowChar(0, 0, '>', OLED_8X16);
				OLED_ShowChinese(20,0 ,"时");OLED_ShowNum(80, 0, Hour, 2, OLED_8X16);
				OLED_ShowChinese(20,17,"分");OLED_ShowNum(80, 17, Min, 2, OLED_8X16);
				OLED_ShowChinese(20,35,"确认");
            }break;
                
            case 1:{
				OLED_ShowChinese(20, 0 , "时");OLED_ShowNum(80, 0, Hour, 2, OLED_8X16);
                OLED_ShowChar(0, 17, '>', OLED_8X16);
				OLED_ShowChinese(20, 17, "分");OLED_ShowNum(80, 17, Min, 2, OLED_8X16);
				OLED_ShowChinese(20, 35, "确认");
            }break;
            
            case 2:{
				OLED_ShowChinese(20, 0 , "时");OLED_ShowNum(80, 0, Hour, 2, OLED_8X16);
				OLED_ShowChinese(20, 17, "分");OLED_ShowNum(80, 17, Min, 2, OLED_8X16);
                OLED_ShowChar(0, 34, '>', OLED_8X16);
				OLED_ShowChinese(20, 35, "确认");
            }break;
			
			case 3:{
				/* 切换页面 */
				OLED_Clear();
                OLED_ShowChar(0, 0, '>', OLED_8X16); 
				OLED_ShowChinese(20, 0, "退出");
            }break;
        }
		OLED_Update();
    }	
}






//==========================================================
//	函数名称：	charge_mode
//
//	函数功能：	卡片充值模式
//
//	入口参数：	无
//
//	返回参数：	无
//
//	说明：		  调用时可以为卡片充值
//==========================================================
void charge_mode(void){
	
		int money = 0;
		
    int flag = 0; 	/* 用户选项 */
    while(1){	
        int key = key_Scan(0);/* 按键扫描 */
				switch(key){
						case Select_Btn:{
								flag++;
								flag %= 3;
						}break;
						case Check_Btn:{
							if(flag == 1){
								OLED_Clear();
								OLED_ShowChinese(0, 0, "请放卡片");
								OLED_Update();
								/* 往卡片写入金额 */
								RC522_Ctrl(PICC_INCREMENT,4,money);
								OLED_ShowChinese(0, 16, "充值完成");				
								OLED_ShowChinese(0, 32, "任意键退出");
								OLED_Update();										
								while(1){/* 任意按键按下时退出 */											
									if(key_Scan(0) != 0)return;							
								}					
							}
							if(flag == 2){
								return;
							}
						}break;
						case UP_Btn:{
							money++;
						}break;
						case Down_Btn:{
							if(money <= 0){
								money = 0;
								continue;
							}
							money--;
						}break;			
				}
		OLED_Clear();
		/* 显示菜单选项 */		
        switch(flag){                
            case 0:{
								OLED_ShowString(30, 0, "INCREMENT",OLED_8X16);
								OLED_ReverseArea(0, 0, 127, 16);
								OLED_ShowChar(20, 17, '>', OLED_8X16);
								OLED_ShowChinese(31, 17,"金额");OLED_ShowNum(80, 17, money, 2, OLED_8X16);
								OLED_ShowChinese(31, 35,"确认");
            }break;
			
            case 1:{
								OLED_ShowString(30, 0, "INCREMENT",OLED_8X16);
								OLED_ReverseArea(0, 0, 127, 16);
								OLED_ShowChinese(31, 17,"金额");OLED_ShowNum(80, 17, money, 2, OLED_8X16);
								OLED_ShowChar(20, 34, '>', OLED_8X16);
								OLED_ShowChinese(31, 35,"确认");
            }break;
			
						case 2:{
								OLED_ShowString(30, 0, "INCREMENT",OLED_8X16);
								OLED_ReverseArea(0, 0, 127, 16);
								OLED_ShowChar(20, 17, '>', OLED_8X16);
								OLED_ShowChinese(31, 17,"退出");
            }break;
						default:break;
        }
				OLED_Update();
    }
}




//==========================================================
//	函数名称：	find_mode
//
//	函数功能：	卡片查询模式
//
//	入口参数：	无
//
//	返回参数：	无
//
//	说明：		调用时可以查询卡片金额
//==========================================================
void find_mode(void){
	int read_money;
	OLED_Clear();
	OLED_ShowChinese(30, 0, "卡片查询");
	OLED_ReverseArea(0, 0, 127, 16);
	OLED_ShowChinese(0, 16, "卡金额");
	OLED_ShowString(60, 16, "xxxx", OLED_8X16);
	OLED_ShowString(103, 16, "RMB", OLED_8X16);
	OLED_Update();
	
	/* 读取卡片内部数值 */
	read_money = RC522_Read(4);
	OLED_ShowNum(60, 16, read_money, 4, OLED_8X16);
	OLED_Update();
	OLED_ShowChinese(0, 32, "任意键退出");
	OLED_Update();
	
	while(1){						
		/* 任意按键按下时退出 */
		if(key_Scan(0) != 0)return;							
	}
}




//==========================================================
//	函数名称：	OLED_Show_Data
//
//	函数功能：	OLED显示采集数据
//
//	入口参数：	A[in]:电流
//				U[in]:电压
//				kWh[in]:电量
//
//	返回参数：	无
//
//	说明：		通过OLED显示IM1281b采集的数据
//==========================================================
void OLED_Show_Data(double U,double A,double kWh){
	OLED_Clear();
	OLED_ShowChinese(0,0 ,"电压"); OLED_Printf(33, 0 , OLED_8X16, ": %.2f V",U);
	OLED_ShowChinese(0,18,"电流"); OLED_Printf(33, 18, OLED_8X16, ": %.2f A",A);
	OLED_ShowChinese(0,36,"电量"); OLED_Printf(33, 36, OLED_8X16, ": %.2f kWh",kWh);
	OLED_Update();
}



extern int APP_Hour;
extern int APP_Min;
extern int APP_Return_flag;
void app_mode(void){
	/* 定时器时间初始化 */
	APP_Hour = 0;
	APP_Min = 0;
	cur_mode = APP_MODE;
	/* 显示APP提示信息 */
	OLED_Clear();
	OLED_Show_App_Tip();
	OLED_Update();
	DelayXms(1000);
	/* 清除云平台数值 */
	OneNet_SendData_APP_mode();
	while(1){
		/* 用户关闭继电器时退出函数 */
		if(APP_Return_flag == 1){
			APP_Return_flag = 0;
			return;
		}		
		/* 接收APP控制 */
		unsigned char *tmp = ESP8266_GetIPD(0);
		if(tmp !=NULL){
			OneNet_RevPro(tmp);
		}				
		/* 显示采集信息 */
		OLED_Show_Data(U,A,kWh);				
		DelayXms(100);
	}
}



