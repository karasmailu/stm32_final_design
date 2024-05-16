/************************************************************************************
//�����������������ҡ����Ա�����: https://shop149406681.taobao.com/?spm=a1z10.1-c.0.0.64cb457fKzgKea 
//�Ա����������ؼ��ʣ�K_A33_001
//  �� �� ��   : v1.0
//  ��    ��   : ����������
//  ����Ⱥ :			 1041406448�����������������ע���棩
//    CSDN  ��������������Դ�����б����н���˵����   :��Ƭ��������˹�(�����ؼ��ʣ�K_A33_001)
//    BILIBILI����ʾ��Ƶ�� :����������(�����ؼ��ʣ�K_A33_001)
//  ��������   : 2021-6-21
//  ����޸�   : 2021-11-21
//  ��������   : RC522ģ����Գ���
//  ��������   : STM32F103C8T6   ����8M  ϵͳʱ��72M

RC522-------------------------------------STM32F103C8T6
VCC  -------------------------------------3.3V
GND  -------------------------------------GND
RST  -------------------------------------GPIOB_0
MISO -------------------------------------GPIOA_6
MOSI -------------------------------------GPIOA_7
SCK  -------------------------------------GPIOA_5
SDA  -------------------------------------GPIOA_4
**************************************************************/
#include "rc522_function.h"
#include "rc522_config.h"
#include "stm32f10x.h"
#include "delay.h"
#include "usart.h"


#define 	MAXRLEN 18
#define   	RC522_DELAY()  		DelayUs(2)
#define   	macRC522_DELAY()  	DelayUs(200)

/////////////////////////////////////////////////////////////////////
//��    �ܣ���RC632�Ĵ���
//����˵����Address[IN]:�Ĵ�����ַ
//��    �أ�������ֵ
/////////////////////////////////////////////////////////////////////
unsigned char ReadRawRC(unsigned char Address)
{
     unsigned char i, ucAddr;
     unsigned char ucResult=0;

     macRC522_SCK_0;
		 RC522_DELAY();
     macRC522_SDA_0;
		 RC522_DELAY();
     ucAddr = ((Address<<1)&0x7E)|0x80;

     for(i=8;i>0;i--)
     {
			 
         if(ucAddr&0x80)
				 {
						macRC522_MOSI_1;
				 }
				 else
				 {
						macRC522_MOSI_0;
				 }
				 RC522_DELAY();
         macRC522_SCK_1;
				 RC522_DELAY();
         ucAddr <<= 1;
         macRC522_SCK_0;
				 RC522_DELAY();
     }

     for(i=8;i>0;i--)
     {
         macRC522_SCK_1;
			 RC522_DELAY();
         ucResult <<= 1;
         ucResult|=macRC522_MISO_GET;
         macRC522_SCK_0;
			 RC522_DELAY();
     }

     macRC522_SCK_1;
		 RC522_DELAY();
     macRC522_SDA_1;
		 RC522_DELAY();
     return ucResult;
}

/////////////////////////////////////////////////////////////////////
//��    �ܣ�дRC632�Ĵ���
//����˵����Address[IN]:�Ĵ�����ַ
//          value[IN]:д���ֵ
/////////////////////////////////////////////////////////////////////
void WriteRawRC(unsigned char Address, unsigned char value)
{  
    unsigned char i, ucAddr;

     macRC522_SCK_0;
     macRC522_SDA_0;
    ucAddr = ((Address<<1)&0x7E);

    for(i=8;i>0;i--)
    {
			   if(ucAddr&0x80)
				 {
						macRC522_MOSI_1;
				 }
				 else
				 {
						macRC522_MOSI_0;
				 }
				 RC522_DELAY();
         macRC522_SCK_1;
				 RC522_DELAY();
         ucAddr <<= 1;
         macRC522_SCK_0;
				 RC522_DELAY();
    }

    for(i=8;i>0;i--)
    {
			   if(value&0x80)
				 {
						macRC522_MOSI_1;
				 }
				 else
				 {
						macRC522_MOSI_0;
				 }
				 RC522_DELAY();
         macRC522_SCK_1;
				 RC522_DELAY();
         value <<= 1;
         macRC522_SCK_0;
				 RC522_DELAY();
    }

		 macRC522_SCK_1;
		RC522_DELAY();
     macRC522_SDA_1;
		RC522_DELAY();
}

/////////////////////////////////////////////////////////////////////
//��    �ܣ���λRC522
//��    ��: �ɹ�����MI_OK
/////////////////////////////////////////////////////////////////////
char PcdReset(void) 
{
	
	//unsigned char i;
    macRC522_Reset_1;
	DelayUs (1);             
    macRC522_Reset_0;
	DelayUs (1);                         
    macRC522_Reset_1;
	DelayUs (1);        	

    //macRC522_Reset_1;
    WriteRawRC(CommandReg,0x0F); //soft reset
    while(ReadRawRC(CommandReg) & 0x10); //wait chip start ok

	DelayUs (1);            
	
 //   WriteRawRC(CommandReg,PCD_RESETPHASE);
  
    WriteRawRC(ModeReg,0x3D);            //��Mifare��ͨѶ��CRC��ʼֵ0x6363
    WriteRawRC(TReloadRegL,30);           
    WriteRawRC(TReloadRegH,0);
    WriteRawRC(TModeReg,0x8D);
    WriteRawRC(TPrescalerReg,0x3E);
    WriteRawRC(TxAutoReg,0x40);
    return MI_OK;
}
/////////////////////////////////////////////////////////////////////
//��    �ܣ���RC522�Ĵ���λ
//����˵����reg[IN]:�Ĵ�����ַ
//          mask[IN]:��λֵ
/////////////////////////////////////////////////////////////////////
void SetBitMask(unsigned char reg,unsigned char mask)  
{
    char tmp = 0x0;
    tmp = ReadRawRC(reg);
    WriteRawRC(reg,tmp | mask);  // set bit mask
}

/////////////////////////////////////////////////////////////////////
//��    �ܣ���RC522�Ĵ���λ
//����˵����reg[IN]:�Ĵ�����ַ
//          mask[IN]:��λֵ
/////////////////////////////////////////////////////////////////////
void ClearBitMask(unsigned char reg,unsigned char mask)  
{
    char tmp = 0x0;
    tmp = ReadRawRC(reg);
    WriteRawRC(reg, tmp & ~mask);  // clear bit mask
} 


/////////////////////////////////////////////////////////////////////
//��    �ܣ�ͨ��RC522��ISO14443��ͨѶ
//����˵����Command[IN]:RC522������
//          pInData[IN]:ͨ��RC522���͵���Ƭ������
//          InLenByte[IN]:�������ݵ��ֽڳ���
//          pOutData[OUT]:���յ��Ŀ�Ƭ��������
//          *pOutLenBit[OUT]:�������ݵ�λ����
/////////////////////////////////////////////////////////////////////
char PcdComMF522(unsigned char Command, 
                 unsigned char *pInData, 
                 unsigned char InLenByte,
                 unsigned char *pOutData, 
                 unsigned int  *pOutLenBit)
{
    char status = MI_ERR;
    unsigned char irqEn   = 0x00;
    unsigned char waitFor = 0x00;
    unsigned char lastBits;
    unsigned char n;
    unsigned int i;
    switch (Command)
    {
       case PCD_AUTHENT:
          irqEn   = 0x12;
          waitFor = 0x10;
          break;
       case PCD_TRANSCEIVE:
          irqEn   = 0x77;
          waitFor = 0x30;
          break;
       default:
         break;
    }
   
    WriteRawRC(ComIEnReg,irqEn|0x80);	//PCD_TRANSCEIVEģʽ ������ı�
    ClearBitMask(ComIrqReg,0x80);			//IRQ��©���
    WriteRawRC(CommandReg,PCD_IDLE);  //ȡ����ǰ����
    SetBitMask(FIFOLevelReg,0x80);		//���FIFO Flash ��ErrReg  BufferOvfl��־
    
    for (i=0; i<InLenByte; i++)
    {   
		WriteRawRC(FIFODataReg, pInData[i]);    //�����ݴ浽FIFO
	}
    WriteRawRC(CommandReg, Command);   //����FIFO����
   
    
    if (Command == PCD_TRANSCEIVE)
    {    
		SetBitMask(BitFramingReg,0x80);  //����ֹͣ��ʱ��
	}
    
	n = ReadRawRC(ComIrqReg);
    i = 1500;//����ʱ��Ƶ�ʵ���������M1�����ȴ�ʱ��25ms
    do 
    {
         n = ReadRawRC(ComIrqReg);
         i--;		
    }
    while ((i!=0) && !(n&0x01) && !(n&waitFor));
    ClearBitMask(BitFramingReg,0x80);
	      
    if (i!=0)
    {    
         if(!(ReadRawRC(ErrorReg)&0x1B))
         {
             status = MI_OK;
             if (n & irqEn & 0x01)
             {   status = MI_NOTAGERR;   }
             if (Command == PCD_TRANSCEIVE)
             {
               	n = ReadRawRC(FIFOLevelReg);
              	lastBits = ReadRawRC(ControlReg) & 0x07;
                if (lastBits)
                {   *pOutLenBit = (n-1)*8 + lastBits;   }
                else
                {   *pOutLenBit = n*8;   }
                if (n == 0)
                {   n = 1;    }
                if (n > MAXRLEN)
                {   n = MAXRLEN;   }
                for (i=0; i<n; i++)
                {   pOutData[i] = ReadRawRC(FIFODataReg);    }
            }
         }
         else
         {   
					status = MI_ERR;   
		}
        
   }
   

   SetBitMask(ControlReg,0x80);           // stop timer now
   WriteRawRC(CommandReg,PCD_IDLE); 
   return status;
}

/////////////////////////////////////////////////////////////////////
//��������  
//ÿ��������ر����շ���֮��Ӧ������1ms�ļ��
/////////////////////////////////////////////////////////////////////
void PcdAntennaOn(void)
{
    unsigned char i;
    i = ReadRawRC(TxControlReg);
    if (!(i & 0x03))
    {
        SetBitMask(TxControlReg, 0x03);
    }
}


/////////////////////////////////////////////////////////////////////
//�ر�����
/////////////////////////////////////////////////////////////////////

void PcdAntennaOff(void)
{
    ClearBitMask(TxControlReg, 0x03);
}




/////////////////////////////////////////////////////////////////////
//��MF522����CRC16����
/////////////////////////////////////////////////////////////////////
void CalulateCRC(unsigned char *pIndata,unsigned char len,unsigned char *pOutData)
{
    unsigned char i,n;
    ClearBitMask(DivIrqReg,0x04);
    WriteRawRC(CommandReg,PCD_IDLE);
    SetBitMask(FIFOLevelReg,0x80);
    for (i=0; i<len; i++)
    {   WriteRawRC(FIFODataReg, *(pIndata+i));   }
    WriteRawRC(CommandReg, PCD_CALCCRC);
    i = 0xFF;
    do 
    {
        n = ReadRawRC(DivIrqReg);
        i--;
    }
    while ((i!=0) && !(n&0x04));
    pOutData[0] = ReadRawRC(CRCResultRegL);
    pOutData[1] = ReadRawRC(CRCResultRegM);
}




/////////////////////////////////////////////////////////////////////
//��    �ܣ����Ƭ��������״̬
//��    ��: �ɹ�����MI_OK
/////////////////////////////////////////////////////////////////////
char PcdHalt(void)
{
    
    unsigned int  unLen;
    unsigned char ucComMF522Buf[MAXRLEN]; 
	char status;
    ucComMF522Buf[0] = PICC_HALT;
    ucComMF522Buf[1] = 0;
    CalulateCRC(ucComMF522Buf,2,&ucComMF522Buf[2]);
 
    status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,4,ucComMF522Buf,&unLen);

    return status;
}
/////////////////////////////////////////////////////////////////////
//��    �ܣ�����Ǯ��
//����˵��: sourceaddr[IN]��Դ��ַ
//          goaladdr[IN]��Ŀ���ַ
//��    ��: �ɹ�����MI_OK
/////////////////////////////////////////////////////////////////////
char PcdBakValue(unsigned char sourceaddr, unsigned char goaladdr)
{
    char status;
    unsigned int  unLen;
    unsigned char ucComMF522Buf[MAXRLEN]; 

    ucComMF522Buf[0] = PICC_RESTORE;
    ucComMF522Buf[1] = sourceaddr;
    CalulateCRC(ucComMF522Buf,2,&ucComMF522Buf[2]);
 
    status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,4,ucComMF522Buf,&unLen);

    if ((status != MI_OK) || (unLen != 4) || ((ucComMF522Buf[0] & 0x0F) != 0x0A))
    {   status = MI_ERR;   }
    
    if (status == MI_OK)
    {
        ucComMF522Buf[0] = 0;
        ucComMF522Buf[1] = 0;
        ucComMF522Buf[2] = 0;
        ucComMF522Buf[3] = 0;
        CalulateCRC(ucComMF522Buf,4,&ucComMF522Buf[4]);
 
        status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,6,ucComMF522Buf,&unLen);
        if (status != MI_ERR)
        {    status = MI_OK;    }
    }
    
    if (status != MI_OK)
    {    return MI_ERR;   }
    
    ucComMF522Buf[0] = PICC_TRANSFER;
    ucComMF522Buf[1] = goaladdr;

    CalulateCRC(ucComMF522Buf,2,&ucComMF522Buf[2]);
 
    status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,4,ucComMF522Buf,&unLen);

    if ((status != MI_OK) || (unLen != 4) || ((ucComMF522Buf[0] & 0x0F) != 0x0A))
    {   status = MI_ERR;   }

    return status;
}

/////////////////////////////////////////////////////////////////////
//��    �ܣ��ۿ�ͳ�ֵ
//����˵��: dd_mode[IN]��������
//               0xC0 = �ۿ�
//               0xC1 = ��ֵ
//          addr[IN]��Ǯ����ַ
//          pValue[IN]��4�ֽ���(��)ֵ����λ��ǰ
//��    ��: �ɹ�����MI_OK
/////////////////////////////////////////////////////////////////////                 
char PcdValue(unsigned char dd_mode,unsigned char addr,unsigned char *pValue)
{
    char status;
    unsigned int  unLen;
    unsigned char i,ucComMF522Buf[MAXRLEN]; 
    
    ucComMF522Buf[0] = dd_mode;
    ucComMF522Buf[1] = addr;
    CalulateCRC(ucComMF522Buf,2,&ucComMF522Buf[2]);
 
    status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,4,ucComMF522Buf,&unLen);

    if ((status != MI_OK) || (unLen != 4) || ((ucComMF522Buf[0] & 0x0F) != 0x0A))
    {   
				status = MI_ERR;   
		}
        
    if (status == MI_OK)
    {
       // memcpy(ucComMF522Buf, pValue, 4);
        for (i=0; i<16; i++)
        {    
						ucComMF522Buf[i] = *(pValue+i);   
				}
        CalulateCRC(ucComMF522Buf,4,&ucComMF522Buf[4]);
        unLen = 0;
        status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,6,ucComMF522Buf,&unLen);
        if (status != MI_ERR)
        {    	
						status = MI_OK;   
				}
    }
    
    if (status == MI_OK)
    {
        ucComMF522Buf[0] = PICC_TRANSFER;
        ucComMF522Buf[1] = addr;
        CalulateCRC(ucComMF522Buf,2,&ucComMF522Buf[2]); 
   
        status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,4,ucComMF522Buf,&unLen);

        if ((status != MI_OK) || (unLen != 4) || ((ucComMF522Buf[0] & 0x0F) != 0x0A))
        {   
						status = MI_ERR;   
				}
    }
    return status;
}

/////////////////////////////////////////////////////////////////////
//��    �ܣ�Ѱ��
//����˵��: req_code[IN]:Ѱ����ʽ
//                0x52 = Ѱ��Ӧ�������з���14443A��׼�Ŀ�
//                0x26 = Ѱδ��������״̬�Ŀ�
//          pTagType[OUT]����Ƭ���ʹ���
//                0x4400 = Mifare_UltraLight
//                0x0400 = Mifare_One(S50)
//                0x0200 = Mifare_One(S70)
//                0x0800 = Mifare_Pro(X)
//                0x4403 = Mifare_DESFire
//��    ��: �ɹ�����MI_OK
/////////////////////////////////////////////////////////////////////
char PcdRequest(unsigned char req_code,unsigned char *pTagType)
{
   char status;  
   unsigned int  unLen;
   unsigned char ucComMF522Buf[MAXRLEN]; 

   ClearBitMask(Status2Reg,0x08);
   WriteRawRC(BitFramingReg,0x07);
   SetBitMask(TxControlReg,0x03);
 
   ucComMF522Buf[0] = req_code;

   status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,1,ucComMF522Buf,&unLen);
   
   if ((status == MI_OK) && (unLen == 0x10))
   {    
       *pTagType     = ucComMF522Buf[0];
       *(pTagType+1) = ucComMF522Buf[1];
   }
   else
   {   status = MI_ERR;  
 


	}
   
   return status;
}

/////////////////////////////////////////////////////////////////////
//��    �ܣ�����ײ
//����˵��: pSnr[OUT]:��Ƭ���кţ�4�ֽ�
//��    ��: �ɹ�����MI_OK
/////////////////////////////////////////////////////////////////////  
char PcdAnticoll(unsigned char *pSnr)
{
    char status;
    unsigned char i,snr_check=0;
    unsigned int  unLen;
    unsigned char ucComMF522Buf[MAXRLEN]; 
    

    ClearBitMask(Status2Reg,0x08);
    WriteRawRC(BitFramingReg,0x00);
    ClearBitMask(CollReg,0x80);
 
    ucComMF522Buf[0] = PICC_ANTICOLL1;
    ucComMF522Buf[1] = 0x20;

    status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,2,ucComMF522Buf,&unLen);

    if (status == MI_OK)
    {
    	 for (i=0; i<4; i++)
         {   
             *(pSnr+i)  = ucComMF522Buf[i];
             snr_check ^= ucComMF522Buf[i];

         }
         if (snr_check != ucComMF522Buf[i])
         {   status = MI_ERR;    }
    }
    
    SetBitMask(CollReg,0x80);
    return status;
}

/////////////////////////////////////////////////////////////////////
//��    �ܣ�ѡ����Ƭ
//����˵��: pSnr[IN]:��Ƭ���кţ�4�ֽ�
//��    ��: �ɹ�����MI_OK
/////////////////////////////////////////////////////////////////////
char PcdSelect(unsigned char *pSnr)
{
    char status;
    unsigned char i;
    unsigned int  unLen;
    unsigned char ucComMF522Buf[MAXRLEN]; 
    
    ucComMF522Buf[0] = PICC_ANTICOLL1;
    ucComMF522Buf[1] = 0x70;
    ucComMF522Buf[6] = 0;
    for (i=0; i<4; i++)
    {
    	ucComMF522Buf[i+2] = *(pSnr+i);
    	ucComMF522Buf[6]  ^= *(pSnr+i);
    }
    CalulateCRC(ucComMF522Buf,7,&ucComMF522Buf[7]);
  
    ClearBitMask(Status2Reg,0x08);

    status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,9,ucComMF522Buf,&unLen);
    
    if ((status == MI_OK) && (unLen == 0x18))
    {   status = MI_OK;  }
    else
    {   status = MI_ERR;    }

    return status;
}

/////////////////////////////////////////////////////////////////////
//��    �ܣ���֤��Ƭ����
//����˵��: auth_mode[IN]: ������֤ģʽ
//                 0x60 = ��֤A��Կ
//                 0x61 = ��֤B��Կ 
//          addr[IN]�����ַ
//          pKey[IN]������
//          pSnr[IN]����Ƭ���кţ�4�ֽ�
//��    ��: �ɹ�����MI_OK
/////////////////////////////////////////////////////////////////////               
char PcdAuthState(unsigned char auth_mode,unsigned char addr,unsigned char *pKey,unsigned char *pSnr)
{
    char status;
    unsigned int  unLen;
    unsigned char i,ucComMF522Buf[MAXRLEN]; 

    ucComMF522Buf[0] = auth_mode;
    ucComMF522Buf[1] = addr;
    for (i=0; i<6; i++)
    {    ucComMF522Buf[i+2] = *(pKey+i);   }
    for (i=0; i<6; i++)
    {    ucComMF522Buf[i+8] = *(pSnr+i);   }
 //   memcpy(&ucComMF522Buf[2], pKey, 6); 
 //   memcpy(&ucComMF522Buf[8], pSnr, 4); 
    
    status = PcdComMF522(PCD_AUTHENT,ucComMF522Buf,12,ucComMF522Buf,&unLen);
    if ((status != MI_OK) || (!(ReadRawRC(Status2Reg) & 0x08)))
    {   status = MI_ERR;   }
    
    return status;
}

/////////////////////////////////////////////////////////////////////
//��    �ܣ���ȡM1��һ������
//����˵��: addr[IN]�����ַ
//          pData[OUT]�����������ݣ�16�ֽ�
//��    ��: �ɹ�����MI_OK
///////////////////////////////////////////////////////////////////// 
char PcdRead(unsigned char addr,unsigned char *pData)
{
    char status;
    unsigned int  unLen;
    unsigned char i,ucComMF522Buf[MAXRLEN]; 

    ucComMF522Buf[0] = PICC_READ;
    ucComMF522Buf[1] = addr;
    CalulateCRC(ucComMF522Buf,2,&ucComMF522Buf[2]);
   
    status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,4,ucComMF522Buf,&unLen);
    if ((status == MI_OK) && (unLen == 0x90))
 //   {   memcpy(pData, ucComMF522Buf, 16);   }
    {
        for (i=0; i<16; i++)
        {    *(pData+i) = ucComMF522Buf[i];   }
    }
    else
    {   status = MI_ERR;   }
    
    return status;
}

/////////////////////////////////////////////////////////////////////
//��    �ܣ�д���ݵ�M1��һ��
//����˵��: addr[IN]�����ַ
//          pData[IN]��д������ݣ�16�ֽ�
//��    ��: �ɹ�����MI_OK
/////////////////////////////////////////////////////////////////////                  
char PcdWrite(unsigned char addr,unsigned char *pData)
{
    char status;
    unsigned int  unLen;
    unsigned char i,ucComMF522Buf[MAXRLEN]; 
    
    ucComMF522Buf[0] = PICC_WRITE;
    ucComMF522Buf[1] = addr;
    CalulateCRC(ucComMF522Buf,2,&ucComMF522Buf[2]);
 
    status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,4,ucComMF522Buf,&unLen);

    if ((status != MI_OK) || (unLen != 4) || ((ucComMF522Buf[0] & 0x0F) != 0x0A))
    {   status = MI_ERR;   }
        
    if (status == MI_OK)
    {
        //memcpy(ucComMF522Buf, pData, 16);
        for (i=0; i<16; i++)
        {    ucComMF522Buf[i] = *(pData+i);   }
        CalulateCRC(ucComMF522Buf,16,&ucComMF522Buf[16]);

        status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,18,ucComMF522Buf,&unLen);
        if ((status != MI_OK) || (unLen != 4) || ((ucComMF522Buf[0] & 0x0F) != 0x0A))
        {   status = MI_ERR;   }
    }
    
    return status;
}


/*
************************************************************
*	�������ƣ�	Set_Money
*
*	�������ܣ�	RC522����оƬ��ʼ���
*
*	��ڲ�����	addr[in]: ��Ƭ��ַ
*				money[in]: ���
*
*	���ز�����	��
*
*	˵����		���ÿ�Ƭ�ĳ�ʼֵ
************************************************************
*/
//void Set_Money(unsigned char addr , int money){
//	 	
//	unsigned char money_pack[16] = {0};
//	unsigned char DefaultKey[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}; 
//	unsigned char g_ucTempbuf[20]; 
//	unsigned char status;
//	unsigned int temp;
//	int i;	
//	//M1����ĳһ��дΪ���¸�ʽ����ÿ�ΪǮ�����ɽ��տۿ�ͳ�ֵ����(���ֽ���ǰ,��Ϊ��С�˵Ĺ�ϵ��
//	//4�ֽڽ�4�ֽڽ��ȡ����4�ֽڽ�1�ֽڿ��ַ��1�ֽڿ��ַȡ����1�ֽڿ��ַ��1�ֽڿ��ַȡ��
//	/* �������ת�� */
//	for(i = 3; i >= 0; i--){
//		money_pack[i+8] = money_pack[i] = money & 0xFF;		
//		money_pack[i+4] = ~(money & 0xFF);
//		money >>= 8;
//	}
//	
//	/* ��ַ����ת�� */
//	for(i = 12 ; i < 16 ; i++){
//		if(i%2 == 0){
//			money_pack[i] = addr;
//		}else{
//			money_pack[i] = ~addr;
//		}
//	}
//	
//	while(1){
//		
//		/* ��һ����Ѱ�� */
//		status = PcdRequest(PICC_REQALL, g_ucTempbuf);//Ѱ��
//		if (status != MI_OK)
//		{    
//			PcdReset();
//			PcdAntennaOff(); 
//			PcdAntennaOn(); 
//			continue;
//		}
//		UsartPrintf(USART1, "Ѱ���ɹ�\r\n");
//		UsartPrintf(USART1, "���ţ�");
//		for(i=0;i<2;i++)
//		{
//			temp=g_ucTempbuf[i];
//			UsartPrintf(USART1, "%x",temp);
//		}
//		
//		UsartPrintf(USART1, "\r\n");

//		
//		/* �ڶ���������ײ */
//		status = PcdAnticoll(g_ucTempbuf);//����ײ
//		if (status != MI_OK)
//		{    
//			continue;    
//		}
//		UsartPrintf(USART1, "����ײ�ɹ�\r\n");
//		UsartPrintf(USART1,"�����кţ�");	//������ʾ,
//		for(i=0;i<4;i++)
//		{
//			temp=g_ucTempbuf[i];
//			UsartPrintf(USART1,"%X",temp);
//		}
//		UsartPrintf( USART1,"\r\n" );

//		
//		/* ��������ѡ����Ƭ */
//		status = PcdSelect(g_ucTempbuf);//ѡ����Ƭ
//		if (status != MI_OK)
//		{    
//			continue;    
//		}
//		UsartPrintf( USART1,"ѡ����Ƭ�ɹ�\r\n" );
//		
//		
//		/* ���Ĳ�����֤��Ƭ���� */
//		status = PcdAuthState(PICC_AUTHENT1A, addr, DefaultKey, g_ucTempbuf);//��֤��Ƭ����
//		if (status != MI_OK)
//		{    
//			continue;    
//		}
//		UsartPrintf( USART1,"��֤��Ƭ����ɹ�\r\n" );
//	
//		
//		/* ���岽��д�� */
//		status = PcdWrite(addr, money_pack);//д��
//		if (status != MI_OK)
//		{    
//			continue;    
//		}
//		UsartPrintf(USART1, "\r\n");
//		UsartPrintf( USART1,"д��ɹ�\r\n" );		


//		/* ������������ */
//		status = PcdRead(addr, g_ucTempbuf);//���� 
//		if (status != MI_OK)
//		{    
//			continue;    
//		}
//		UsartPrintf( USART1,"д��ɹ������飺");//�����ն���ʾ	
//		for(i=0;i<4;i++)
//		{
//			temp=g_ucTempbuf[i];
//			UsartPrintf(USART1,"%X",temp);
//		}
//		UsartPrintf(USART1,"\r\n");	
//		UsartPrintf(USART1,"\r\n");	
//		return;
//	}
//}



/*
************************************************************
*	�������ƣ�	RC522_Ctrl
*
*	�������ܣ�	RC522���ƺ���
*
*	��ڲ�����	mode[in]: PICC_DECREMENT �ۿ�
*						  PICC_INCREMENT ��ֵ
*				addr[in]: ��Ƭ��ַ
*				money[in]: ���
*
*	���ز�����	��
*
*	˵����		����ģʽ�Ĳ�ͬ������ɳ�ֵ�ۿ�Ĳ���
************************************************************
*/
void RC522_Ctrl( unsigned char mode , unsigned char addr , unsigned char money){
	int i;
	unsigned char money_pack[4] = {0};
	unsigned char DefaultKey[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}; 
	unsigned char g_ucTempbuf[20]; 
	unsigned char status;
	unsigned int temp;	

	money_pack[3] = money;
	while(1){
		/* ��һ����Ѱ�� */
		status = PcdRequest(PICC_REQALL, g_ucTempbuf);//Ѱ��
		if (status != MI_OK)
		{    
			PcdReset();
			PcdAntennaOff(); 
			PcdAntennaOn(); 
			continue;
		}
//		UsartPrintf(USART1, "Ѱ���ɹ�\r\n");
//		UsartPrintf(USART1, "���ţ�");
//		for(i=0;i<2;i++)
//		{
//			temp=g_ucTempbuf[i];
//			UsartPrintf(USART1, "%x",temp);
//		}
//		
//		UsartPrintf(USART1, "\r\n");

		
		/* �ڶ���������ײ */
		status = PcdAnticoll(g_ucTempbuf);//����ײ
		if (status != MI_OK)
		{    
			continue;    
		}
//		UsartPrintf(USART1, "����ײ�ɹ�\r\n");
//		UsartPrintf(USART1,"�����кţ�");	//������ʾ,
//		for(i=0;i<4;i++)
//		{
//			temp=g_ucTempbuf[i];
//			UsartPrintf(USART1,"%X",temp);
//		}
//		UsartPrintf( USART1,"\r\n" );

		
		/* ��������ѡ����Ƭ */
		status = PcdSelect(g_ucTempbuf);//ѡ����Ƭ
		if (status != MI_OK)
		{    
			continue;    
		}
//		UsartPrintf( USART1,"ѡ����Ƭ�ɹ�\r\n" );

		
		/* ���Ĳ�����֤��Ƭ���� */
		status = PcdAuthState(PICC_AUTHENT1A, addr, DefaultKey, g_ucTempbuf);//��֤��Ƭ����
		if (status != MI_OK)
		{    
			continue;    
		}
//		UsartPrintf( USART1,"��֤��Ƭ����ɹ�\r\n" );
		
//		/* ���岽������ */
//		status = PcdRead(addr, g_ucTempbuf);//���� 
//		if (status != MI_OK)
//		{    
//			continue;    
//		}
//		UsartPrintf( USART1,"д��ɹ������飺");//�����ն���ʾ	
//		for(i=0;i<4;i++)
//		{
//			temp=g_ucTempbuf[i];
//			UsartPrintf(USART1,"%X",temp);
//		}
//		UsartPrintf(USART1,"\r\n");	
//		UsartPrintf(USART1,"\r\n");

		if(mode == PICC_DECREMENT){
			/* ���������ۿ� */
			status = PcdValue(PICC_DECREMENT,addr,money_pack);//�ۿ�
			if (status != MI_OK)
			{   
				continue;    
			}
//			UsartPrintf(USART1,"�ۿ�ɹ�\r\n");

			/* ���߲������� */
			status = PcdRead(addr, g_ucTempbuf);//���� 
			if (status != MI_OK)
			{    
				continue;    
			}
//			UsartPrintf( USART1,"�ۿ�ɹ������飺" );//�����ն���ʾ	
//			for(i=0;i<4;i++)
//			{
//				temp=g_ucTempbuf[i];
//				UsartPrintf(USART1,"%X",temp);
//			}
//			UsartPrintf(USART1,"\r\n");
//			UsartPrintf(USART1,"\r\n");
			return;
		}
		if(mode == PICC_INCREMENT){
			/* ����������ֵ */
			status = PcdValue(PICC_INCREMENT,addr,money_pack);//��ֵ
			if (status != MI_OK)
			{   
				continue;    
			}
//			UsartPrintf(USART1,"��ֵ�ɹ�\r\n");
			status = PcdRead(addr, g_ucTempbuf);//���� 
			if (status != MI_OK)
			{    
				continue;    
			}
			
//			/* ���߲������� */
//			UsartPrintf( USART1,"��ֵ�ɹ������飺" );//�����ն���ʾ	
//			for(i=0;i<4;i++)
//			{
//				temp=g_ucTempbuf[i];
//				UsartPrintf(USART1,"%X",temp);
//			}
//			UsartPrintf(USART1,"\r\n");
//			UsartPrintf(USART1,"\r\n");		
			return;
		}
		
	}
	
}


/*
************************************************************
*	�������ƣ�	RC522_Read
*
*	�������ܣ�	��ȡ��Ƭ��ֵ
*
*	��ڲ�����	addr[in]: ��Ƭ��ַ
*
*	���ز�����	��
*
*	˵����		
************************************************************
*/
int RC522_Read(unsigned char addr){
	int i;
	unsigned char DefaultKey[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}; 
	unsigned char g_ucTempbuf[20]; 
	unsigned char status;
	unsigned int temp;	
	int read_ret = 0;
	while(1){
		/* ��һ����Ѱ�� */
		status = PcdRequest(PICC_REQALL, g_ucTempbuf);//Ѱ��
		if (status != MI_OK)
		{    
			PcdReset();
			PcdAntennaOff(); 
			PcdAntennaOn(); 
			continue;
		}
		UsartPrintf(USART1, "Ѱ���ɹ�\r\n");
		UsartPrintf(USART1, "���ţ�");
		for(i=0;i<2;i++)
		{
			temp=g_ucTempbuf[i];
			UsartPrintf(USART1, "%x",temp);
		}
		
		UsartPrintf(USART1, "\r\n");
		
		/* �ڶ���������ײ */
		status = PcdAnticoll(g_ucTempbuf);//����ײ
		if (status != MI_OK)
		{    
			continue;    
		}
		UsartPrintf(USART1, "����ײ�ɹ�\r\n");
		UsartPrintf(USART1,"�����кţ�");	//������ʾ,
		for(i=0;i<4;i++)
		{
			temp=g_ucTempbuf[i];
			UsartPrintf(USART1,"%X",temp);
		}
		UsartPrintf( USART1,"\r\n" );
		
		/* ��������ѡ����Ƭ */
		status = PcdSelect(g_ucTempbuf);//ѡ����Ƭ
		if (status != MI_OK)
		{    
			continue;    
		}
		UsartPrintf( USART1,"ѡ����Ƭ�ɹ�\r\n" );
		
		/* ���Ĳ�����֤��Ƭ���� */
		status = PcdAuthState(PICC_AUTHENT1A, addr, DefaultKey, g_ucTempbuf);//��֤��Ƭ����
		if (status != MI_OK)
		{    
			continue;    
		}
		UsartPrintf( USART1,"��֤��Ƭ����ɹ�\r\n" );
		
		/* ������������ */
		status = PcdRead(addr, g_ucTempbuf);//���� 
		if (status != MI_OK)
		{    
			continue;    
		}
		UsartPrintf( USART1,"addr -> %d :",addr);//�����ն���ʾ	
		for(i=0;i<4;i++)
		{
			temp=g_ucTempbuf[i];
			read_ret <<= 8;
			read_ret |= g_ucTempbuf[i];
			UsartPrintf(USART1,"%X",temp);
		}				
		return read_ret;		
	}
}

