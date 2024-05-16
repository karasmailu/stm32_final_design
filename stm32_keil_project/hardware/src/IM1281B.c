#include "IM1281B.h"

unsigned char IM1281B_buf[128];
unsigned short IM1281B_cnt = 0, IM1281B_cntPre = 0;


unsigned int IM1281B_Data[8];
/*************************************************************
 *
 *	IM1281B_Data[0] 电压	IM1281B_Data[4] 功率因数
 *	IM1281B_Data[1] 电流	IM1281B_Data[5] 二氧化碳
 *	IM1281B_Data[2] 功率	IM1281B_Data[6] 温度
 *	IM1281B_Data[3] 电能	IM1281B_Data[7] 频率  
 *
 ************************************************************/

/*************************************************************

		double U 	= IM1281B_Data[0]/10000.0;
		double A 	= IM1281B_Data[1]/10000.0;
		double W 	= IM1281B_Data[2]/10000.0;
		double kWh 	= IM1281B_Data[3]/10000.0;		
		double Q 	= IM1281B_Data[4]/1000.0;
		double Co2 	= IM1281B_Data[5]/10000.0;
		double temp = IM1281B_Data[6]/100.0;
		double Hz 	= IM1281B_Data[7]/100.0;
		
***************************************************************/


/* IM1281B 获取数据命令 */
/* 数据格式为modbus格式 */
/* 设备地址1字节 + 命令1字节 + 设备寄存器地址2字节 + 读取数据长度2字节 + CRC校验2字节 */
//unsigned char cmd[] = {0x01,0x03,0x00,0x48,0x00,0x08,0xC4,0x1A};

/*
************************************************************
*	函数名称：	Num16to10
*
*	函数功能：	16进制转10进制
*
*	入口参数：	hex 16进制数
*
*	返回参数：	sum 10进制数
*
*	说明：		
************************************************************
*/
int Num16to10(int hex){
	int sum=0,mul=1;
	int i,r;
	int count=0;
	do{
		r=hex%16;
		for(i=0;i<count;i++)
		mul*=16;
		mul*=r;
		sum+=mul;
		mul=1;
		count++; 
	}while(hex/=16);

	return sum;
}

/*
************************************************************
*	函数名称：	IM1281B_Clear
*
*	函数功能：	清空IM1281B_buf数据
*
*	入口参数：	无
*
*	返回参数：	无
*
*	说明：		
************************************************************
*/
void IM1281B_Clear(void)
{
	memset(IM1281B_buf, 0, sizeof(IM1281B_buf));
	IM1281B_cnt = 0;
}





/*
************************************************************
*	函数名称：	IM1281B_Init
*
*	函数功能：	IM1281B串口3初始化
*
*	入口参数：	band 波特率 与IM1281B通信固定为4800
*
*	返回参数：	无
*
*	说明：		
************************************************************
*/
void IM1281B_Init(unsigned int baud){   
    Usart3_Init(baud);
    IM1281B_Clear();
}







/*
************************************************************
*	函数名称：	IM1281B_Data_Change
*
*	函数功能：	IM1281B的16进制数据转换10进制
*
*	入口参数：	res IM1281B的原数据，dest 转换数据（int 最少8个数据）
*
*	返回参数：	无
*
*	说明：		
************************************************************
*/
void IM1281B_Data_Change(const unsigned char *res, unsigned int *dest){
  	int k = 0;
	for(int i = 0; i < 29 ;i += 4){
		int tmp = res[i+3]<<24 | res[i+4]<<16 | res[i+5]<<8 | res[i+6];
		dest[k++] = Num16to10(tmp);
	}	
    IM1281B_Clear();
}

/*
************************************************************
*	函数名称：	USART3_IRQHandler
*
*	函数功能：	USART3接收中断，用于接收IM1281B的返回数据
*
*	入口参数：	无
*
*	返回参数：	无
*
*	说明：		
************************************************************
*/
void USART3_IRQHandler(void)
{
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) //接收中断
	{
		if(IM1281B_cnt >= sizeof(IM1281B_buf))	IM1281B_cnt = 0; //防止串口被刷爆
		IM1281B_buf[IM1281B_cnt++] = USART3->DR;		
		USART_ClearFlag(USART3, USART_FLAG_RXNE);
	}
}



