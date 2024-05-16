#ifndef _ONENET_H_
#define _ONENET_H_

#include "stm32f10x.h"
#include "cJSON.h"
#include "led.h"
#include "time.h"
#include "relays.h"
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
#pragma diag_suppress 177
#pragma diag_suppress 550



#define ONENET_SERVER_INFO  "AT+CIPSTART=\"TCP\",\"mqtts.heclouds.com\",1883\r\n"	//onenet网址和端口

#define PROID			"Lu7Lu5L6qP"    //产品ID

#define ACCESS_KEY		"VDNZWUd4QU5KSmVnRGU4NFkxRGF2VkhCb0pNNFBQbG8="  //产品密钥

#define DEVICE_NAME		"test"  //产品名称

#define ET 				1956499200	//unix时间戳

//属性上报的topic为：$sys/{pid}/{device-name}/thing/property/post
//上报数据成功后，订阅的属性上报会返回success
//tip 1: dev_ID 和 dev_Name 需要结合自己的设备来填
//tip 2: 本代码使用了传参形式，此宏定义没有使用 --> MqttKit.c -->  MQTT_PacketSaveData();
#define SEND_DATA_TOPIC     "$sys/{dev_ID}/{dev_Name}/thing/property/post"


//设备侧需要收到平台下发的数据，需要订阅：$sys/{pid}/{device-name}/thing/property/set
//tip 1: dev_ID 和 dev_Name 需要结合自己的设备来填
//tip 2: 本代码使用了传参形式，此宏定义没有使用 --> onenet.c -->  OneNET_Subscribe();
#define RECV_DATA_TOPIC     "$sys/{dev_ID}/{device-name}/thing/property/set"


_Bool OneNET_RegisterDevice(void);

_Bool OneNet_DevLink(void);

void OneNet_SendData(void);

void OneNet_SendData_APP_mode(void);

void OneNET_Subscribe(void);

void OneNet_RevPro(unsigned char *cmd);

#endif
