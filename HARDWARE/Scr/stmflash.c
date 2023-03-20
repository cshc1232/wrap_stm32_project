/*-------------------------------------------------*/
/*            ����˵������STM32ϵ�п�����          */
/*-------------------------------------------------*/
/*                                                 */
/*              ʵ��FLASH���ܵ�Դ�ļ�              */
/*                                                 */
/*-------------------------------------------------*/

#include "stm32f1xx_hal.h"    //������Ҫ��ͷ�ļ�
#include "main.h"             //������Ҫ��ͷ�ļ�
#include "stmflash.h"         //������Ҫ��ͷ�ļ�
#include "boot.h"             //������Ҫ��ͷ�ļ�
#include "usart.h"            //������Ҫ��ͷ�ļ�

Flash_CB stm32FlashCB;        //����stm32 flash�Ľṹ��
LoadApp loadapp;              //����һ���������͵Ĳ���,������ת��Ӧ�ó�����

/*-------------------------------------------------*/
/*����������ָ����ַ��ʼд��ָ�����ȵ�32Bit����    */
/*��  ����WriteAddr��д���ַ                      */
/*��  ����pBuffer��д�������                      */
/*��  ����NumToWrite��д������ݳ���               */
/*����ֵ��0 ��ȷ ���� ����                         */
/*-------------------------------------------------*/
uint8_t Stm32Flash_Write(uint32_t WriteAddr, uint64_t *pBuffer,uint32_t NumToWrite)	
{ 
    HAL_FLASH_Unlock();                                                                             //����
	while(NumToWrite){                                                                              //ѭ��д������
		if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, WriteAddr, *pBuffer) != HAL_OK){        //һ��д��8�ֽ����ݣ����ж��Ƿ�д����ȷ������������if
			HAL_FLASH_Lock();                                                                       //����
			return 1;	                                                                            //����1
		}
		WriteAddr += 8;                                                                             //д����ȷ�Ļ�����ַ����8���ֽ�                        
		pBuffer++;                                                                                  //��������8���ֽڣ���������д������ 
		NumToWrite -=8;                                                                             //��д��������-8�ֽ�                   		
	} 
	HAL_FLASH_Lock();                                                                               //����
	return 0;                                                                                       //��ȷ������0
}
/*-------------------------------------------------*/
/*����������������                                 */
/*��  ����StartSector����ʼ����                    */
/*��  ����num��������������                        */
/*����ֵ��0 ��ȷ ���� ����                         */
/*-------------------------------------------------*/
uint8_t Stm32Flash_Erase(uint16_t StartSector, uint16_t num, uint32_t *PageError)   	
{
	
    stm32FlashCB.EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;               //��������
	stm32FlashCB.EraseInitStruct.PageAddress = StartSector * FLASH_SECTOR_SIZE + FLASH_BASE_ADDR;     //��ʼ������������ַ
	stm32FlashCB.EraseInitStruct.NbPages     = num;                                 //������������	
	HAL_FLASH_Unlock();                                                             //����	
	if(HAL_FLASHEx_Erase(&stm32FlashCB.EraseInitStruct, PageError) != HAL_OK){      //��������������������if
		HAL_FLASH_Lock();                                                           //����
		u1_printf("����A��Flashʧ��\r\n");                                          //����1�����Ϣ	
		return 1;                                                                   //����1
	}	
	HAL_FLASH_Lock();                                                               //����
	u1_printf("����A��Flash�ɹ�\r\n");                                              //����1�����Ϣ	
	return 0;                                                                       //����0
}
/*-------------------------------------------------*/
/*������������ջ����ַ                             */
/*��  ����addr:ջ����ַ                            */
/*����ֵ����                                       */
/*-------------------------------------------------*/
__asm void MSR_MSP(uint32_t addr) 
{
	MSR MSP, r0 			
	BX r14
}
/*-------------------------------------------------*/
/*����������ת��Ӧ�ó����                         */
/*��  ����appxaddr:�û�������ʼ��ַ                */
/*����ֵ��0:��ȷ 1������                           */
/*-------------------------------------------------*/
uint8_t Load_APP(uint32_t appxaddr)
{
	if(((*(volatile uint32_t*)appxaddr)&0x2FFE0000)==0x20000000){	    //���ջ����ַ�Ƿ�Ϸ�.	 
     	loadapp=(LoadApp)*(volatile uint32_t*)(appxaddr+4);		        //�û��������ڶ�����Ϊ����ʼ��ַ(��λ��ַ)		
		MSR_MSP(*(volatile uint32_t*)appxaddr);					        //��ʼ��APP��ջָ��(�û��������ĵ�һ�������ڴ��ջ����ַ)
		BootLoader_Clear();                                             //��ת���� 
		loadapp();									                    //��תӦ�ó�����
	}else{
		u1_printf("��ת��A��ʧ�ܣ�����BootLoader\r\n");                 //����1�����Ϣ
		U1Rx_Buff_Init();                                               //��ʼ������1����������ݵĸ�������
		BootLoader_Info();                                              //���BootLoader�����б���Ϣ	
		return 1;                                                       //���󣬷���1
	}
	return 0;                                                           //��ȷ����0
}
