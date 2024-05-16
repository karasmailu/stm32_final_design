# stm32_final_design
本工程两个工程文件，一个为APP软件工程，一个为stm32工程

APP软件工程：stm32_hbuilderx_project
stm32硬件工程：stm32_keil_project

描述：
1、APP软件工程
    软件工程采用Hbuilderx软件编程，分为两个页面存放与pages/index目录下，一个为主页面，一个为支付页面，主页面显示硬件参数的各种信息外加一个控制电路通断开关，开关仅在APP模式下可以控制，页面的核心逻辑为采用HTTP协议与onenet云平台进行数据交互
2、stm32 keil工程
    stm32工程采用stm32c8t6为主控芯片，使用外设为time定时器、usart、gpio，使用到的硬件为esp8266、IM1281B、RC522、0.96寸OLED显示屏、按键、蜂鸣器、继电器。其中esp8266为网络通信模块，与onenet云平台进行通信；IM1281B为电流电压检测模块，采集电流电压信息电压量程在0-380v，电流量程为0-50A，采用的通信协议为usart + Modbus协议；RC522为刷卡IC模块，采用的协议为SPI，本设计采用软件SPI；OLED为显示模块，采用的软件IIC，
