/*-----------------------------------------------------*/
/*              超子说物联网STM32系列开发板            */
/*-----------------------------------------------------*/
/*                     程序结构                        */
/*-----------------------------------------------------*/
/*USER     ：包含程序的main函数，是整个程序的入口      */
/*HARDWARE ：包含开发板各种功能外设的驱动程序          */
/*STM32G0xx_HAL_Driver  ：官方提供的库文件             */
/*-----------------------------------------------------*/
/*                                                     */
/*           程序main函数，入口函数源文件              */
/*                                                     */
/*-----------------------------------------------------*/
//#include "Headfile.h"
#include "stm32f1xx_hal.h"    //包含需要的头文件
#include "delay.h"            //包含需要的头文件
#include "usart.h"            //包含需要的头文件
#include "led.h"              //包含需要的头文件
#include "timer.h"          //包含需要的头文件
#include "iic.h"              //包含需要的头文件
#include "w25qxx.h"           //包含需要的头文件
#include "spi.h"              //包含需要的头文件
#include "main.h"
#include "boot.h"
#include "rtc.h"              //包含需要的头文件
#include "24l01.h"

uint32_t          BootEventFlag;       //发生各种事件的标志变量                                                   
Update_CB         Update;              //本地/OTA更新固件时结构体变量
AliyunInfo_CB     AliInfoCB;           //EEPROM内保存的腾讯云证书信息结构体
uint8_t wdata_buff[16][256];
uint8_t rdata_buff[16*256];
uint8_t wq_buff[256];
Update_WQ    Update_Wq;

u8 send_buf[33];
u8 tmp_buf[33]; 
uint8_t send_flag = 0;
int16_t fun_send_handle()
{
	tmp_buf[0]=0x11;//低位 
	tmp_buf[1]=0x22;//高位
	tmp_buf[2]=0x33;
	tmp_buf[3]= 0;//加入结束符	
	if(NRF24L01_TxPacket(tmp_buf)==TX_OK)
		send_flag=1;
	else {
	send_flag=0;
	}
	return send_flag;
}


int main(void) 
{    		
	HAL_Init();                                                //初始化HAL	
	Delay_CLock_Init();                                        //初始化延迟计数器 配置时钟函数
	U1_Init(115200);                                           //初始化串口1
	U2_Init(115200);                                           //初始化串口1
  U3_Init(115200);                                           //初始化串口1

	
	//LED_Init(); 
  RTC_Init();                                      //初始化RTC 
 // IIC_Init();  	//初始化LED	
	//TIM4_Init(5000,7200);                                      //定时器频率为72M/7200=10K，自动重装载为5000，那么定时器周期就是500ms
	u1_printf("\r\n\r\n-----新的程序 最新-----\r\n\r\n");    //串口输出提示信息					   

/*	if(W25Qxx_Init()!=0){                                              //???W25Qxx,????????0,????,??if
	while(1){
	u1_printf("W25Qxx inti failed \r\n");                         //????????
	Delay_Ms(500);		//??
	}
}
	W25Qxx_Erase_Block(0);                                                                              //????0 
 //W25Qxx_Erase_Block(1);                                                                              //????0 
 //W25Qxx_Erase_Block(2);                                                                              //????0 
	
  Update_Wq.PageNum=0;
	//BootEventFlag |= A_XMODEM ;
*/

  u2_printf("Data2: %s\r\n","2222"); 
  u3_printf("Data3: %s\r\n","3333"); 
	
		NRF24L01_Init(); 										//按键初始化   
	while(NRF24L01_Check())							//检查NRF24L01是否在位
		{
			//OLED_ShowString6x8(0,0,"nrf24l01 error");
			u1_printf("******nrf24l01 error*********\r\n");
	
			Delay_Ms(1000);
		}	
	//OLED_ShowString6x8(0,2,"NRF24L01 OK");
  u1_printf("******nrf24l01 check ok*********\r\n");	
	Delay_Ms(1000);
	NRF24L01_TX_Mode();									//配置NRF24L01模式
	while(1){ 
 
    if(U1_Control.URxDataOutPtr != U1_Control.URxDataInPtr)
		{                                             //如果串口1的 URxDataOutPtr指针 和 URxDataInPtr指针不相等，则if成立，说明串口1有数据接收到了                     					   						                                                                                         
		
			U1_Control.U_Rxdatalen = U1_Control.URxDataOutPtr->EndPtr - U1_Control.URxDataOutPtr->StartPtr;  //计算本次接收的数据量		                                           //清空缓冲区
			memcpy(U1Copy_RxBuff,U1_Control.URxDataOutPtr->StartPtr,U1_Control.U_Rxdatalen);                 //提取数据		
			//u1_printf("Datalen: = 0x%x\r\n",U1_Control.U_Rxdatalen);    			//处理BootLoader命令或事件	
      u1_printf("Data1: %s\r\n",U1Copy_RxBuff); 
		//	BootLoader_Event(U1Copy_RxBuff,U1_Control.U_Rxdatalen);  
     // u1_TxHex(U1Copy_RxBuff[0]);
			//u1_printf("Data: =%s\r\n",U1Copy_RxBuff[0]);    			//处理BootLoader命令或事件	
			memset(U1Copy_RxBuff,0,U1_Control.U_Rxdatalen);
			U1_Control.URxDataOutPtr ++;                                                                     //串口1的 URxDataOutPtr指针 下移
			if(U1_Control.URxDataOutPtr==U1_Control.URxDataEndPtr)                                           //如果到达处理接收数据的结构体数组尾部了
			{
				U1_Control.URxDataOutPtr = &U1_Control.UCB_RxBuffPtrCB[0];                                   //串口1的 URxDataOutPtr指针 回到处理接收数据的结构体数组开头  
	   
			}
		}


  if(U2_Control.URxDataOutPtr != U2_Control.URxDataInPtr)
		{                                             //如果串口1的 URxDataOutPtr指针 和 URxDataInPtr指针不相等，则if成立，说明串口1有数据接收到了                     					   						                                                                                         
		
			U2_Control.U_Rxdatalen = U2_Control.URxDataOutPtr->EndPtr - U2_Control.URxDataOutPtr->StartPtr;  //计算本次接收的数据量		                                           //清空缓冲区
			memcpy(U2Copy_RxBuff,U2_Control.URxDataOutPtr->StartPtr,U2_Control.U_Rxdatalen);                 //提取数据		
			u2_printf("Datalen: = 0x%x\r\n",U2_Control.U_Rxdatalen);    			//处理BootLoader命令或事件	
      u2_printf("Data2: %s\r\n",U2Copy_RxBuff); 
			memset(U2Copy_RxBuff,0,U2_Control.U_Rxdatalen);
			U2_Control.URxDataOutPtr ++;                                                                     //串口1的 URxDataOutPtr指针 下移
			if(U2_Control.URxDataOutPtr==U2_Control.URxDataEndPtr)                                           //如果到达处理接收数据的结构体数组尾部了
			{
				U2_Control.URxDataOutPtr = &U2_Control.UCB_RxBuffPtrCB[0];                                   //串口1的 URxDataOutPtr指针 回到处理接收数据的结构体数组开头  
	   
			}
		}

    if(U3_Control.URxDataOutPtr != U3_Control.URxDataInPtr)
		{                                             //如果串口1的 URxDataOutPtr指针 和 URxDataInPtr指针不相等，则if成立，说明串口1有数据接收到了                     					   						                                                                                         
		
			U3_Control.U_Rxdatalen = U3_Control.URxDataOutPtr->EndPtr - U3_Control.URxDataOutPtr->StartPtr;  //计算本次接收的数据量		                                           //清空缓冲区
			memcpy(U3Copy_RxBuff,U3_Control.URxDataOutPtr->StartPtr,U3_Control.U_Rxdatalen);                 //提取数据		
			u3_printf("Datalen: = 0x%x\r\n",U3_Control.U_Rxdatalen);    			//处理BootLoader命令或事件	
      u3_printf("Data3: %s\r\n",U3Copy_RxBuff); 
			memset(U3Copy_RxBuff,0,U3_Control.U_Rxdatalen);
			U3_Control.URxDataOutPtr ++;                                                                     //串口1的 URxDataOutPtr指针 下移
			if(U3_Control.URxDataOutPtr==U3_Control.URxDataEndPtr)                                           //如果到达处理接收数据的结构体数组尾部了
			{
				U3_Control.URxDataOutPtr = &U3_Control.UCB_RxBuffPtrCB[0];                                   //串口1的 URxDataOutPtr指针 回到处理接收数据的结构体数组开头  
	   
			}
		}
		
					
			if(fun_send_handle())
			{
				//LED0=0;
				u1_printf("send ok\r\n");
			}
			else{
				//LED0=1;
				u1_printf("send failed\r\n");
			}
		
		Delay_Ms(1000);
	}
}
