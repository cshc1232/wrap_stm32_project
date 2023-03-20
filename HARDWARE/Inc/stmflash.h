/*-------------------------------------------------*/
/*            ����˵������STM32ϵ�п�����          */
/*-------------------------------------------------*/
/*                                                 */
/*              ʵ��FLASH���ܵ�ͷ�ļ�              */
/*                                                 */
/*-------------------------------------------------*/

#ifndef __STMFLASH_H__
#define __STMFLASH_H__

typedef  void (*LoadApp)(void);	                              //����һ���������͵Ĳ���.

typedef struct{       
	FLASH_EraseInitTypeDef EraseInitStruct;                   //����FLASH�������þ��	
	uint32_t PageError;                                       //����������󷵻�ֵ	
}Flash_CB;                                                    //����stm32 flash�Ľṹ��

extern Flash_CB stm32FlashCB;                                 //�ⲿ��������������stm32 flash�Ľṹ��

uint8_t Stm32Flash_Write(uint32_t, uint64_t *,uint32_t);      //����������дFlash����
uint8_t Stm32Flash_Erase(uint16_t, uint16_t, uint32_t *);	  //��������������Flash����
void MSR_MSP(uint32_t);	   	                                  //��������������ջ����ַ
uint8_t Load_APP(uint32_t);	                                  //������������ת��Ӧ�ó����

#endif

















