/*-------------------------------------------------*/
/*            ����˵������STM32ϵ�п�����          */
/*-------------------------------------------------*/
/*                                                 */
/*              ʵ��BOOT���ܵ�Դ�ļ�               */
/*                                                 */
/*-------------------------------------------------*/

#include "stm32f1xx_hal.h"    //������Ҫ��ͷ�ļ�
#include "main.h"             //������Ҫ��ͷ�ļ�
#include "boot.h"             //������Ҫ��ͷ�ļ�
#include "delay.h"            //������Ҫ��ͷ�ļ�
#include "usart.h"            //������Ҫ��ͷ�ļ�
#include "timer.h"            //������Ҫ��ͷ�ļ�
#include "stmflash.h"         //������Ҫ��ͷ�ļ�
#include "rtc.h"              //������Ҫ��ͷ�ļ�
#include "24c02.h"            //������Ҫ��ͷ�ļ�
#include "w25qxx.h"           //������Ҫ��ͷ�ļ�

/*-------------------------------------------------*/
/*��������BootLoader��֧����                       */
/*��  ������                                       */
/*����ֵ����                                       */
/*-------------------------------------------------*/
void BootLoader_Branch(void)
{
	if(BootLoader_Enter(20)==0)
		{                                                                      //20*100ms�ڣ�û������Сд��ĸw������if
	    if(AliInfoCB.OTA_flag==BOOT_STA_O){                                                           //�ж��Ƿ���ҪOTA����					
		  u1_printf("OTA*********************\r\n");  
//			u1_printf("OTA����\r\n");                                                                 //����1�����
//			u1_printf("�̼��汾��%s\r\n",AliInfoCB.Version_ABuff);                                    //����1�����Ϣ
//			u1_printf("�̼���С��%d\r\n",AliInfoCB.OTA_firelen);                                      //����1�����Ϣ
//			if(Stm32Flash_Erase(FLASH_A_START_SECTOR,FLASH_A_SECTO_NUM,&stm32FlashCB.PageError)==0){  //����A��Flash���� ִ�в��� ����ɹ� ����if						
//				BootEventFlag |= OTA_MODEM;
//        u1_printf("����A��Flash��  success OTA\r\n"); 				
//			}			
		}else if(HAL_RTCEx_BKUPRead(&MyRtc,RTC_BKP_DR1)==BOOT_STANDBY_KEY){                           //��ȡ�󱸼Ĵ������������BOOT_STANDBY_KEY������͹���,��������								
//			u1_printf("����͹���,��������\r\n");                                                     //���������ʾ��Ϣ
//			HAL_RTCEx_BKUPWrite(&MyRtc,RTC_BKP_DR1,0x0);                                              //�󱸼Ĵ���1,д��
//			HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN1);                                                 //����PA0���ڻ���
//			__HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);                                                        //���PWR_FLAG_WU��־
//			HAL_PWR_EnterSTANDBYMode();                                                               //�������ģʽ						
		}
		else
		Load_APP(FLASH_A_ADDR);
//                                                                 //��֮���������BOOT_STA_O������else����תA��			
	}else{                                                                                            //��֮��20*100ms�ڣ�����Сд��ĸw������else
		//U1Rx_Buff_Init();                                                                             //��ʼ������1����������ݵĸ�������
		//BootLoader_Info();                                                                            //���BootLoader�����б���Ϣ	
	}
	
}
/*-------------------------------------------------*/
/*���������Ƿ����BootLoader                       */
/*��  ����counter:����ʱ����                       */
/*����ֵ��1������BootLoader   0��������BootLoader  */
/*-------------------------------------------------*/
uint8_t BootLoader_Enter(uint8_t counter)
{	
	u1_printf("\r\n2���ڣ����롮w������bootloader\r\n");              //����1�����Ϣ	
	while(counter--){			                                    //whileѭ���ȴ�����ʱ��0
		if(U1_RxBuff[0] == 'w')                                     //������յ��ĵ�һ��������Сд��ĸw���������BootLoader
			return 1;                                               //ֱ�ӷ���1�����ȵ���ʱ�ˣ���ʾ����BootLoader
		Delay_Ms(100);                                              //ÿ��ѭ����ʱ100ms
	}	 
    return 0;                                                       //����0����ʾ������BootLoader
}
/*-------------------------------------------------*/
/*��������BootLoader�����Ϣ                       */
/*��  ������                                       */
/*����ֵ����                                       */
/*-------------------------------------------------*/
void BootLoader_Info(void)
{	                          	
	u1_printf("[1]A������\r\n");                        //����1�����Ϣ                                 
	u1_printf("[2]A�����أ�Xmodem��\r\n");              //����1�����Ϣ
	u1_printf("[3]������Ѷ����Ԫ��֤����Ϣ\r\n");       //����1�����Ϣ
	u1_printf("[4]��ѯ��Ѷ����Ԫ��֤����Ϣ\r\n\r\n");   //����1�����Ϣ
}	
/*-------------------------------------------------*/
/*������������BootLoader�¼�                       */
/*��  ����data ������                              */
/*��  ����datalen �����ݳ���                       */
/*����ֵ����                                       */
/*-------------------------------------------------*/
void BootLoader_Event(uint8_t *data, uint16_t datalen)
{		      
	/*------------------------------------------------------------------------------------------------*/
	/*                                                                                                */
   if(BootEventFlag&A_XMODEM){                                                                                         //���A�����أ�Xmodem���¼�����������if		
		/*--------------------------------------*/
		/*              �յ����ݰ���            */
		/*--------------------------------------*/
		if((datalen==XMODEM_PACK_SIZE)&&(data[0]==XMODEM_SHO))
		{ 
 // u1_printf("\r\n%d",datalen);					//2����������  ��1��XMODEM_PACK_SIZE�ֽ����ݳ���   ��2����1���ֽ���SHO   
			__HAL_TIM_DISABLE(&htim4);                                                                                      //�رն�ʱ��4
		__HAL_TIM_DISABLE(&htim4);
			//	memcpy(&Update.UpdateBuff[(Update.XmodemPackNO%(FLASH_SECTOR_SIZE/XMODEM_PACKDATA_SIZE))*XMODEM_PACKDATA_SIZE],&data[3],XMODEM_PACKDATA_SIZE);//�����̼����ݵ�������
		 memcpy(&Update_Wq.UpdateBuff[(Update_Wq.XmodemPackNO%(256/XMODEM_PACKDATA_SIZE))*XMODEM_PACKDATA_SIZE],&data[3],XMODEM_PACKDATA_SIZE);
		 Update_Wq.XmodemPackNO ++;                                                                                         //���ݰ����	+1		
			
//			if((Update.XmodemPackNO%(FLASH_SECTOR_SIZE/XMODEM_PACKDATA_SIZE)) == 0){			                             //���չ�1�����������ݣ���д��flash															 
//				Stm32Flash_Write(FLASH_A_ADDR + ((Update.XmodemPackNO/(FLASH_SECTOR_SIZE/XMODEM_PACKDATA_SIZE))-1)*FLASH_SECTOR_SIZE,(uint64_t *)Update.UpdateBuff,FLASH_SECTOR_SIZE);// д��FLASH     			
//			}
    
			// write w25q one page 
 			if((Update_Wq.XmodemPackNO%(256/XMODEM_PACKDATA_SIZE)) == 0){			                             //���չ�1�����������ݣ���д��w25q flash															 
			//Stm32Flash_Write(FLASH_A_ADDR + ((Update.XmodemPackNO/(FLASH_SECTOR_SIZE/XMODEM_PACKDATA_SIZE))-1)*FLASH_SECTOR_SIZE,(uint64_t *)Update.UpdateBuff,FLASH_SECTOR_SIZE);// д��FLASH     			
			W25Qxx_Write_Page(Update_Wq.UpdateBuff,Update_Wq.PageNum++);  
			
			
			}
      	
//			for(int j = 0;j<256;j++)
//      u1_printf("%x",Update_Wq.UpdateBuff[j]);			
//			
		 // u1_printf("\r\n%d",datalen);		
			u1_TxHex(XMODEM_ACK);                                                                                            //����һ�ֽ�XMODEM_ACK ׼��������һ�����ݰ�														
		}	
		/*--------------------------------------*/
		/*         �յ����ͽ�����־��           */
		/*--------------------------------------*/		
		else if((datalen==1)&&(data[0]==XMODEM_EOT)){                                                                        //2����������  (1)1�ֽڳ���   (2)ֵ����XMODEM_EOT ���������
			 u1_TxHex(XMODEM_ACK);                                                                                            //����һ�ֽ�XMODEM_ACK ��������			

			 memcpy(&Update_Wq.UpdateBuff[(Update_Wq.XmodemPackNO%(256/XMODEM_PACKDATA_SIZE))*XMODEM_PACKDATA_SIZE],&data[3],XMODEM_PACKDATA_SIZE);
			 W25Qxx_Write_Page(Update_Wq.UpdateBuff,Update_Wq.PageNum++);
			
			 // start wrte epprom
		
//			for(int j = 0;j<256;j++)
//      u1_printf("%x",Update_Wq.UpdateBuff[j]);
//			
			M24C02_WriteOneByte(0x00,0x01); // write flag
	    M24C02_WriteOneByte(0x01,Update_Wq.PageNum&0xff);
			M24C02_WriteOneByte(0x02,Update_Wq.PageNum>>8);
			
		  u1_printf("\r\n******************read data **********%d*******\r\n");
			for(int i=0;i<Update_Wq.PageNum;i++){                                                                          //??????,??????
				W25Qxx_Read(Update_Wq.UpdateBuff,i*256,256); 
			for(int j = 0;j<256;j++)
      //u1_TxHex(Update_Wq.UpdateBuff[j]);
      u1_printf("%x",Update_Wq.UpdateBuff[j]);
				u1_printf("\r\n***********%d************\r\n",i);				
			}
			u1_printf("\r\n**********fdsfdsfdsfdsf*********%d*******\r\n",Update_Wq.PageNum);

			                                                                                  //���A�����أ�Xmodem���¼�
			NVIC_SystemReset();                                                                                              //����	
		} 	
		/*--------------------------------------*/
		/*         �յ�������ֹ��־��           */
		/*--------------------------------------*/
		else if(data[0]==XMODEM_CAN){
	u1_printf("\r\n**********fdsfdsfdsfdsf*********%d*******\r\n",Update_Wq.PageNum);
			//1����������  (1)���յ�������XMODEM_CAN ֹͣ����
			__HAL_TIM_DISABLE(&htim4);                                                                                      //�رն�ʱ��4
			u1_TxHex(XMODEM_EOT);                                                                                            //����һ�ֽ�XMODEM_EOT ��������
			BootEventFlag &=~ A_XMODEM;                                                                                      //���A�����أ�Xmodem���¼�
			Delay_Ms(500);                                                                                                   //�ӳ�
			BootLoader_Info();                                                                                               //���BootLoader�����б���Ϣ
		}
	}
	
}
/*-------------------------------------------------*/
/*�������������¼�                                 */
/*��  ������                                       */
/*����ֵ����                                       */
/*-------------------------------------------------*/
void ActiveEvent(void)
{	
    uint16_t i;	
	/*------------------------------------------------------------------------------------------------*/
	/*                                                                                                */
	/*                                           ����OTA�¼�                                          */
	/*                                                                                                */
	/*------------------------------------------------------------------------------------------------*/	
	if(BootEventFlag&OTA_MODEM){                                                                                         //OTA�¼�����������if
		for(i=0;i<AliInfoCB.OTA_firelen/FLASH_SECTOR_SIZE;i++){        		                                             //һ�ζ���FLASH_SECTOR_SIZE��С����
		    u1_printf("��ȡ%d~%d�ֽڹ̼���д��Flash�������ĵȴ�... ...\r\n",i*FLASH_SECTOR_SIZE,(i+1)*FLASH_SECTOR_SIZE-1);//����1�����Ϣ
			W25Qxx_Read(Update.UpdateBuff,i*FLASH_SECTOR_SIZE,FLASH_SECTOR_SIZE);                                       //��FLASH_SECTOR_SIZE��С����
			Stm32Flash_Write(FLASH_A_ADDR + i*FLASH_SECTOR_SIZE,(uint64_t *)Update.UpdateBuff,FLASH_SECTOR_SIZE);        //д��flash			
		}
		if((AliInfoCB.OTA_firelen%FLASH_SECTOR_SIZE)!=0){                                                                //�Ƿ��в���FLASH_SECTOR_SIZE������������
			u1_printf("��ȡ%d~%d�ֽڹ̼���д��Flash�������ĵȴ�... ...\r\n",i*FLASH_SECTOR_SIZE,AliInfoCB.OTA_firelen);//����1�����Ϣ
			W25Qxx_Read(Update.UpdateBuff,(AliInfoCB.OTA_firelen/FLASH_SECTOR_SIZE)*FLASH_SECTOR_SIZE,AliInfoCB.OTA_firelen%FLASH_SECTOR_SIZE);  //��������			
			Stm32Flash_Write(FLASH_A_ADDR + i*FLASH_SECTOR_SIZE,(uint64_t *)Update.UpdateBuff,FLASH_SECTOR_SIZE);        //д��flash
		} 
		u1_printf("OTA������ϣ�����\r\n");                                                                              //����1�����Ϣ
		AliInfoCB.OTA_flag = 0;                                                                                          //ȡ��OTA������־
		EEprom_WriteData(0,&AliInfoCB,ALIINFO_STRUCT_LEN);                                                               //������Ϣ��EEprom
		NVIC_SystemReset();                                                                                              //����	
	}   	
}
/*-------------------------------------------------*/
/*��������BootLoader��ת��Ӧ����ǰ��������       */
/*��  ������                                       */
/*����ֵ����                                       */
/*-------------------------------------------------*/
void BootLoader_Clear(void)
{
	HAL_UART_DeInit(&U1_Control.UART_Handler);      //����1�ָ�Ĭ��ֵ
	HAL_TIM_Base_DeInit(&htim4);                    //��ʱ��4�ָ�Ĭ��ֵ
	HAL_RTC_DeInit(&MyRtc);                         //RTC�ָ�Ĭ��ֵ
}
/*-------------------------------------------------*/
/*�����������������Ѷ��֤����Ϣ                   */
/*��  ������                                       */
/*����ֵ����                                       */
/*-------------------------------------------------*/
void Printf_AliCer(void)
{			
	u1_printf("--------------------------��Ѷ���豸֤����Ϣ-------------------------\r\n");          //����1�����Ϣ
	u1_printf("ProductKey��%s\r\n",AliInfoCB.ProductKeyBuff);                                        //����1�����Ϣ
	u1_printf("DeviceName��%s\r\n",AliInfoCB.DeviceNameBuff);                                        //����1�����Ϣ
	u1_printf("DeviceSecret��%s\r\n",AliInfoCB.DeviceSecretBuff);                                    //����1�����Ϣ
	u1_printf("�̼��汾��%s\r\n",AliInfoCB.Version_ABuff);                                           //����1�����Ϣ
	u1_printf("---------------------------------------------------------------------\r\n\r\n");      //����1�����Ϣ	
}
/*-------------------------------------------------*/
/*�������������յ�����Ѷ��֤����Ϣ               */
/*��  ������                                       */
/*����ֵ�����㣺���� 0����ȷ                       */
/*-------------------------------------------------*/
uint8_t BootLoader_AliCerInspect(uint8_t *data)
{
	if(sscanf((char *)data,"#%[^#]#%[^#]#%[^#]#%[^#]#",AliInfoCB.ProductKeyBuff,AliInfoCB.DeviceNameBuff,AliInfoCB.DeviceSecretBuff,AliInfoCB.Version_ABuff)==4){     //��ȡ��Ϣ����ȷ����if
		if(strlen((char *)AliInfoCB.ProductKeyBuff)!=PRODUCTKEY_LEN) return 1;           //��ȡ PRODUCTKEY    ���ݺ�������ȴ��� ����1
		if(strlen((char *)AliInfoCB.DeviceNameBuff)>DEVICENAME_LEN) return 2;            //��ȡ DEVICENAME    ���ݺ�������ȴ��� ����2
		if(strlen((char *)AliInfoCB.DeviceSecretBuff)!=DEVICESECRET_LEN) return 3;       //��ȡ DEVICESECRET  ���ݺ�������ȴ��� ����3
	    if(strlen((char *)AliInfoCB.Version_ABuff)!=VERSION_LEN) return 4;               //��ȡ Version_ABuff ���ݺ�������ȴ��� ����4			
	}else return 5;                                                                      //����ĸ�ʽ����  ����5
	
	return 0;                                                                            //��ȷ������0
}
