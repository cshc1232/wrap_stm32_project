/*-----------------------------------------------------*/
/*              ����˵������STM32ϵ�п�����            */
/*-----------------------------------------------------*/
/*                     ����ṹ                        */
/*-----------------------------------------------------*/
/*USER     �����������main��������������������      */
/*HARDWARE ��������������ֹ����������������          */
/*STM32G0xx_HAL_Driver  ���ٷ��ṩ�Ŀ��ļ�             */
/*-----------------------------------------------------*/
/*                                                     */
/*           ����main��������ں���Դ�ļ�              */
/*                                                     */
/*-----------------------------------------------------*/
//#include "Headfile.h"
#include "stm32f1xx_hal.h"    //������Ҫ��ͷ�ļ�
#include "delay.h"            //������Ҫ��ͷ�ļ�
#include "usart.h"            //������Ҫ��ͷ�ļ�
#include "led.h"              //������Ҫ��ͷ�ļ�
#include "timer.h"          //������Ҫ��ͷ�ļ�
#include "iic.h"              //������Ҫ��ͷ�ļ�
#include "w25qxx.h"           //������Ҫ��ͷ�ļ�
#include "spi.h"              //������Ҫ��ͷ�ļ�
#include "main.h"
#include "boot.h"
#include "rtc.h"              //������Ҫ��ͷ�ļ�
#include "24l01.h"

uint32_t          BootEventFlag;       //���������¼��ı�־����                                                   
Update_CB         Update;              //����/OTA���¹̼�ʱ�ṹ�����
AliyunInfo_CB     AliInfoCB;           //EEPROM�ڱ������Ѷ��֤����Ϣ�ṹ��
uint8_t wdata_buff[16][256];
uint8_t rdata_buff[16*256];
uint8_t wq_buff[256];
Update_WQ    Update_Wq;

u8 send_buf[33];
u8 tmp_buf[33]; 
uint8_t send_flag = 0;
int16_t fun_send_handle()
{
	tmp_buf[0]=0x11;//��λ 
	tmp_buf[1]=0x22;//��λ
	tmp_buf[2]=0x33;
	tmp_buf[3]= 0;//���������	
	if(NRF24L01_TxPacket(tmp_buf)==TX_OK)
		send_flag=1;
	else {
	send_flag=0;
	}
	return send_flag;
}


int main(void) 
{    		
	HAL_Init();                                                //��ʼ��HAL	
	Delay_CLock_Init();                                        //��ʼ���ӳټ����� ����ʱ�Ӻ���
	U1_Init(115200);                                           //��ʼ������1
	U2_Init(115200);                                           //��ʼ������1
  U3_Init(115200);                                           //��ʼ������1

	
	//LED_Init(); 
  RTC_Init();                                      //��ʼ��RTC 
 // IIC_Init();  	//��ʼ��LED	
	//TIM4_Init(5000,7200);                                      //��ʱ��Ƶ��Ϊ72M/7200=10K���Զ���װ��Ϊ5000����ô��ʱ�����ھ���500ms
	u1_printf("\r\n\r\n-----�µĳ��� ����-----\r\n\r\n");    //���������ʾ��Ϣ					   

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
	
		NRF24L01_Init(); 										//������ʼ��   
	while(NRF24L01_Check())							//���NRF24L01�Ƿ���λ
		{
			//OLED_ShowString6x8(0,0,"nrf24l01 error");
			u1_printf("******nrf24l01 error*********\r\n");
	
			Delay_Ms(1000);
		}	
	//OLED_ShowString6x8(0,2,"NRF24L01 OK");
  u1_printf("******nrf24l01 check ok*********\r\n");	
	Delay_Ms(1000);
	NRF24L01_TX_Mode();									//����NRF24L01ģʽ
	while(1){ 
 
    if(U1_Control.URxDataOutPtr != U1_Control.URxDataInPtr)
		{                                             //�������1�� URxDataOutPtrָ�� �� URxDataInPtrָ�벻��ȣ���if������˵������1�����ݽ��յ���                     					   						                                                                                         
		
			U1_Control.U_Rxdatalen = U1_Control.URxDataOutPtr->EndPtr - U1_Control.URxDataOutPtr->StartPtr;  //���㱾�ν��յ�������		                                           //��ջ�����
			memcpy(U1Copy_RxBuff,U1_Control.URxDataOutPtr->StartPtr,U1_Control.U_Rxdatalen);                 //��ȡ����		
			//u1_printf("Datalen: = 0x%x\r\n",U1_Control.U_Rxdatalen);    			//����BootLoader������¼�	
      u1_printf("Data1: %s\r\n",U1Copy_RxBuff); 
		//	BootLoader_Event(U1Copy_RxBuff,U1_Control.U_Rxdatalen);  
     // u1_TxHex(U1Copy_RxBuff[0]);
			//u1_printf("Data: =%s\r\n",U1Copy_RxBuff[0]);    			//����BootLoader������¼�	
			memset(U1Copy_RxBuff,0,U1_Control.U_Rxdatalen);
			U1_Control.URxDataOutPtr ++;                                                                     //����1�� URxDataOutPtrָ�� ����
			if(U1_Control.URxDataOutPtr==U1_Control.URxDataEndPtr)                                           //������ﴦ��������ݵĽṹ������β����
			{
				U1_Control.URxDataOutPtr = &U1_Control.UCB_RxBuffPtrCB[0];                                   //����1�� URxDataOutPtrָ�� �ص�����������ݵĽṹ�����鿪ͷ  
	   
			}
		}


  if(U2_Control.URxDataOutPtr != U2_Control.URxDataInPtr)
		{                                             //�������1�� URxDataOutPtrָ�� �� URxDataInPtrָ�벻��ȣ���if������˵������1�����ݽ��յ���                     					   						                                                                                         
		
			U2_Control.U_Rxdatalen = U2_Control.URxDataOutPtr->EndPtr - U2_Control.URxDataOutPtr->StartPtr;  //���㱾�ν��յ�������		                                           //��ջ�����
			memcpy(U2Copy_RxBuff,U2_Control.URxDataOutPtr->StartPtr,U2_Control.U_Rxdatalen);                 //��ȡ����		
			u2_printf("Datalen: = 0x%x\r\n",U2_Control.U_Rxdatalen);    			//����BootLoader������¼�	
      u2_printf("Data2: %s\r\n",U2Copy_RxBuff); 
			memset(U2Copy_RxBuff,0,U2_Control.U_Rxdatalen);
			U2_Control.URxDataOutPtr ++;                                                                     //����1�� URxDataOutPtrָ�� ����
			if(U2_Control.URxDataOutPtr==U2_Control.URxDataEndPtr)                                           //������ﴦ��������ݵĽṹ������β����
			{
				U2_Control.URxDataOutPtr = &U2_Control.UCB_RxBuffPtrCB[0];                                   //����1�� URxDataOutPtrָ�� �ص�����������ݵĽṹ�����鿪ͷ  
	   
			}
		}

    if(U3_Control.URxDataOutPtr != U3_Control.URxDataInPtr)
		{                                             //�������1�� URxDataOutPtrָ�� �� URxDataInPtrָ�벻��ȣ���if������˵������1�����ݽ��յ���                     					   						                                                                                         
		
			U3_Control.U_Rxdatalen = U3_Control.URxDataOutPtr->EndPtr - U3_Control.URxDataOutPtr->StartPtr;  //���㱾�ν��յ�������		                                           //��ջ�����
			memcpy(U3Copy_RxBuff,U3_Control.URxDataOutPtr->StartPtr,U3_Control.U_Rxdatalen);                 //��ȡ����		
			u3_printf("Datalen: = 0x%x\r\n",U3_Control.U_Rxdatalen);    			//����BootLoader������¼�	
      u3_printf("Data3: %s\r\n",U3Copy_RxBuff); 
			memset(U3Copy_RxBuff,0,U3_Control.U_Rxdatalen);
			U3_Control.URxDataOutPtr ++;                                                                     //����1�� URxDataOutPtrָ�� ����
			if(U3_Control.URxDataOutPtr==U3_Control.URxDataEndPtr)                                           //������ﴦ��������ݵĽṹ������β����
			{
				U3_Control.URxDataOutPtr = &U3_Control.UCB_RxBuffPtrCB[0];                                   //����1�� URxDataOutPtrָ�� �ص�����������ݵĽṹ�����鿪ͷ  
	   
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
