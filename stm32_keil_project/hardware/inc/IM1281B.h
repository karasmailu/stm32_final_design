#ifndef _IM1281B_H
#define _IM1281B_H

#include "usart.h"
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include "delay.h"
#include "OLED.h"

extern unsigned char IM1281B_buf[128];
extern unsigned int IM1281B_Data[8];

void IM1281B_Init(unsigned int baud);
void IM1281B_Clear(void);
void IM1281B_Data_Change( const unsigned char *res, unsigned int *dest);

#endif
