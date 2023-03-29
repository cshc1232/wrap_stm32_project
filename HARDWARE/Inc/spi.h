/*-------------------------------------------------*/
/*           ����˵������STM32ϵ�п�����           */
/*-------------------------------------------------*/
/*                                                 */
/*          ʵ�ָ���SPI�ӿڹ��ܵ�ͷ�ļ�            */
/*                                                 */
/*-------------------------------------------------*/

#ifndef __SPI_H
#define __SPI_H

extern SPI_HandleTypeDef SPI1_Handler;  //SPI1���

void SPI1_Init(void);                          //������������ʼ��SPI1�ӿ�

void SPI1_24l01(void);

uint8_t SPI1_ReadWriteByte(uint8_t);           //����������SPI�ӿڶ�д����
void SPI1_SetSpeed(uint8_t SpeedSet); //����SPI�ٶ� 
#endif


