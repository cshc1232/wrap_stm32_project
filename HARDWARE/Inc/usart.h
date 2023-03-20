/*-------------------------------------------------*/
/*           ����˵������STM32ϵ�п�����           */
/*-------------------------------------------------*/
/*                                                 */
/*             ʵ�ָ������ڹ��ܵ�ͷ�ļ�            */
/*                                                 */
/*-------------------------------------------------*/

#ifndef __USART_H
#define __USART_H

#include "stdio.h"            //������Ҫ��ͷ�ļ�
#include "stdarg.h"		      //������Ҫ��ͷ�ļ� 
#include "string.h"           //������Ҫ��ͷ�ļ�

#define NUM  10                                 //��ǽ���������ʼλ�ã���ֹλ�õĽṹ�������Ա����
#define U1_TXBUFF_SIZE     512                  //���崮��1 ���ͻ�������С
#define U1_RXBUFF_SIZE     1024*4               //���崮��1 ���ջ�������С
#define U1_DMARX_SIZE      1024                 //���崮��1 DMA���ν��յ����������
#define U1_COPYBUFF_SIZE   U1_DMARX_SIZE        //���崦����1�������ݵĻ�����������С


#define U2_TXBUFF_SIZE     128                  //���崮��2 ���ͻ�������С
#define U2_RXBUFF_SIZE     128               //���崮��2 ���ջ�������С
#define U2_DMARX_SIZE      128                 //���崮��2 DMA���ν��յ����������
#define U2_COPYBUFF_SIZE   U2_DMARX_SIZE        //���崦����1�������ݵĻ�����������С


#define U3_TXBUFF_SIZE     128                  //���崮��3 ���ͻ�������С
#define U3_RXBUFF_SIZE     128               //���崮��3 ���ջ�������С
#define U3_DMARX_SIZE      128                 //���崮��3 DMA���ν��յ����������
#define U3_COPYBUFF_SIZE   U3_DMARX_SIZE        //���崦����3�������ݵĻ�����������С



typedef struct{       
	uint8_t *StartPtr;                          //��Ǳ��ν������ݵ���ʼλ��
	uint8_t *EndPtr;                            //��Ǳ��ν������ݵĽ�ֹλ��
}UCB_RxBuffPtrCB;                               //��ǽ���������ʼλ�ã���ֹλ�õĽṹ��

typedef struct{       
	uint16_t U_RxCounter;                       //����һ����������¼���ڽ��յ������ڻ����������ڵ�λ��	
	uint16_t U_Rxdatalen;                       //����һ�����������浱�δ��ڽ��յ������ݵĴ�С  
	uint16_t U_Txdatalen;                       //����һ�����������浱�δ�����Ҫ���͵����ݵĴ�С  
	UCB_RxBuffPtrCB  UCB_RxBuffPtrCB[NUM];      //����һ����ǽ���������ʼλ�ã���ֹλ�õĽṹ�������
	UCB_RxBuffPtrCB *URxDataInPtr;              //ָ���ǽ���������ʼλ�ã���ֹλ�õĽṹ�������Ĳ������ݵ�λ��
	UCB_RxBuffPtrCB *URxDataOutPtr;             //ָ���ǽ���������ʼλ�ã���ֹλ�õĽṹ����������ȡ���ݵ�λ��
	UCB_RxBuffPtrCB *URxDataEndPtr;             //ָ���ǽ���������ʼλ�ã���ֹλ�õĽṹ�����������һ�������Ա��λ��		
	UART_HandleTypeDef UART_Handler;            //�������þ��	
	DMA_HandleTypeDef hdma_rx;                  //���ý��� DMA�ľ��
}UCB_CB;                                        //����1���ƽṹ��

extern UCB_CB U1_Control;                       //�����ⲿ���������ƴ���1�Ľṹ��
extern uint8_t  U1_TxBuff[U1_TXBUFF_SIZE];      //�����ⲿ����������һ�����黺����������1���ͻ����� 
extern uint8_t  U1_RxBuff[U1_RXBUFF_SIZE];      //�����ⲿ����������һ�����黺����������1�����ճ��� 
extern uint8_t  U1Copy_RxBuff[U1_COPYBUFF_SIZE];//�����ⲿ����������һ�����黺����������1����������ݵĸ���������

extern UCB_CB U2_Control;                       //�����ⲿ���������ƴ���1�Ľṹ��
extern uint8_t  U2_TxBuff[U2_TXBUFF_SIZE];      //�����ⲿ����������һ�����黺����������1���ͻ����� 
extern uint8_t  U2_RxBuff[U2_RXBUFF_SIZE];      //�����ⲿ����������һ�����黺����������1�����ճ��� 
extern uint8_t  U2Copy_RxBuff[U2_COPYBUFF_SIZE];//�����ⲿ����������һ�����黺����������1����������ݵĸ���������


extern UCB_CB U3_Control;                       //�����ⲿ���������ƴ���1�Ľṹ��
extern uint8_t  U3_TxBuff[U3_TXBUFF_SIZE];      //�����ⲿ����������һ�����黺����������1���ͻ����� 
extern uint8_t  U3_RxBuff[U3_RXBUFF_SIZE];      //�����ⲿ����������һ�����黺����������1�����ճ��� 
extern uint8_t  U3Copy_RxBuff[U3_COPYBUFF_SIZE];//�����ⲿ����������һ�����黺����������1����������ݵĸ���������



void U1_Init(uint32_t);                                          //������������ʼ������1
void u1_printf(char* ,...);                                      //��������������1 printf����
void U1Rx_Buff_Init(void);                                       //������������ʼ������������ݵĽṹ������
void u1_TxHex(uint8_t);                                          //��������������1����һ��16��������

void U2_Init(uint32_t);                                          //������������ʼ������1
void u2_printf(char* ,...);                                      //��������������1 printf����
void U2Rx_Buff_Init(void);                                       //������������ʼ������������ݵĽṹ������
void u2_TxHex(uint8_t);                                          //��������������1����һ��16��������

void U3_Init(uint32_t);                                          //������������ʼ������1
void u3_printf(char* ,...);                                      //��������������1 printf����
void U3Rx_Buff_Init(void);                                       //������������ʼ������������ݵĽṹ������
void u3_TxHex(uint8_t);                                          //��������������1����һ��16��������

#endif


