#ifndef _ONENET_H_
#define _ONENET_H_

#include "stm32f10x.h"
#include "cJSON.h"
#include "led.h"
#include "time.h"
#include "relays.h"
//��Ƭ��ͷ�ļ�
#include "stm32f10x.h"

//����Э���
#include "onenet.h"

//�����豸
#include "esp8266.h"

//Ӳ������
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

//C��
#include <string.h>
#pragma diag_suppress 177
#pragma diag_suppress 550



#define ONENET_SERVER_INFO  "AT+CIPSTART=\"TCP\",\"mqtts.heclouds.com\",1883\r\n"	//onenet��ַ�Ͷ˿�

#define PROID			"Lu7Lu5L6qP"    //��ƷID

#define ACCESS_KEY		"VDNZWUd4QU5KSmVnRGU4NFkxRGF2VkhCb0pNNFBQbG8="  //��Ʒ��Կ

#define DEVICE_NAME		"test"  //��Ʒ����

#define ET 				1956499200	//unixʱ���

//�����ϱ���topicΪ��$sys/{pid}/{device-name}/thing/property/post
//�ϱ����ݳɹ��󣬶��ĵ������ϱ��᷵��success
//tip 1: dev_ID �� dev_Name ��Ҫ����Լ����豸����
//tip 2: ������ʹ���˴�����ʽ���˺궨��û��ʹ�� --> MqttKit.c -->  MQTT_PacketSaveData();
#define SEND_DATA_TOPIC     "$sys/{dev_ID}/{dev_Name}/thing/property/post"


//�豸����Ҫ�յ�ƽ̨�·������ݣ���Ҫ���ģ�$sys/{pid}/{device-name}/thing/property/set
//tip 1: dev_ID �� dev_Name ��Ҫ����Լ����豸����
//tip 2: ������ʹ���˴�����ʽ���˺궨��û��ʹ�� --> onenet.c -->  OneNET_Subscribe();
#define RECV_DATA_TOPIC     "$sys/{dev_ID}/{device-name}/thing/property/set"


_Bool OneNET_RegisterDevice(void);

_Bool OneNet_DevLink(void);

void OneNet_SendData(void);

void OneNet_SendData_APP_mode(void);

void OneNET_Subscribe(void);

void OneNet_RevPro(unsigned char *cmd);

#endif
