/*-------------------------------------------------*/
/*            ����˵������STM32ϵ�п�����          */
/*-------------------------------------------------*/
/*                                                 */
/*          ʵ�ָ����жϷ�������Դ�ļ�           */
/*                                                 */
/*-------------------------------------------------*/

#include "stm32f1xx_hal.h"    //������Ҫ��ͷ�ļ�
#include "main.h"             //������Ҫ��ͷ�ļ�
#include "usart.h"            //������Ҫ��ͷ�ļ�
#include "timer.h"            //������Ҫ��ͷ�ļ�

/*-------------------------------------------------*/
/*������������1�жϴ�����                        */
/*��  ������                                       */
/*����ֵ����                                       */
/*-------------------------------------------------*/
void USART1_IRQHandler(void)
{		                              
	if(__HAL_UART_GET_FLAG(&U1_Control.UART_Handler,UART_FLAG_IDLE) != RESET){	                                 //������������ж�      	
		__HAL_UART_CLEAR_IDLEFLAG(&U1_Control.UART_Handler);                                                     //��������жϱ�־ 				
		HAL_UART_DMAStop(&U1_Control.UART_Handler);		                                                         //ֹͣDMA
		U1_Control.U_RxCounter += (U1_DMARX_SIZE - __HAL_DMA_GET_COUNTER(&U1_Control.hdma_rx));                  //���㱾�εĽ�������������λ����λ��
		U1_Control.URxDataInPtr->EndPtr = &U1_RxBuff[U1_Control.U_RxCounter];                                    //��¼���ν��յĽ���λ��		
				
		U1_Control.URxDataInPtr++;                                                                               //����INָ������
		if(U1_Control.URxDataInPtr==U1_Control.URxDataEndPtr)                                                    //���ָ�뵽����������ݵĽṹ������β����
			U1_Control.URxDataInPtr = &U1_Control.UCB_RxBuffPtrCB[0];                                            //ָ���λ������������ݵĽṹ���������ʼλ�ã�Ҳ����0�ų�Ա
		U1_Control.URxDataInPtr->StartPtr = &U1_RxBuff[U1_Control.U_RxCounter];                                  //��¼�´ν��յ���ʼλ��
		
		if(U1_RXBUFF_SIZE - U1_Control.U_RxCounter >= U1_DMARX_SIZE){                                            //���ʣ��ռ���� DMA���յĵ��������� ����if
			HAL_UART_Receive_DMA(&U1_Control.UART_Handler, &U1_RxBuff[U1_Control.U_RxCounter], U1_DMARX_SIZE);   //����DMA����
            U1_Control.URxDataInPtr->StartPtr = &U1_RxBuff[U1_Control.U_RxCounter];                              //��¼�´ν��յ���ʼλ��	
		}else{                                                                                                   //���ʣ��ռ䲻�����ν����� ����else
			U1_Control.U_RxCounter = 0;                                                                          //U1_Control.U_RxCounter ����
			HAL_UART_Receive_DMA(&U1_Control.UART_Handler, U1_RxBuff, U1_DMARX_SIZE);                            //����DMA����
			U1_Control.URxDataInPtr->StartPtr = U1_RxBuff;                                                       //��¼�´ν��յ���ʼλ��
		}
	}
	
}



/*-------------------------------------------------*/
/*������������2�жϴ�����                        */
/*��  ������                                       */
/*����ֵ����                                       */
/*-------------------------------------------------*/
void USART2_IRQHandler(void)
{		                              
	if(__HAL_UART_GET_FLAG(&U2_Control.UART_Handler,UART_FLAG_IDLE) != RESET){	                                 //������������ж�      	
		__HAL_UART_CLEAR_IDLEFLAG(&U2_Control.UART_Handler);                                                     //��������жϱ�־ 				
		HAL_UART_DMAStop(&U2_Control.UART_Handler);		                                                         //ֹͣDMA
		U2_Control.U_RxCounter += (U2_DMARX_SIZE - __HAL_DMA_GET_COUNTER(&U2_Control.hdma_rx));                  //���㱾�εĽ�������������λ����λ��
		U2_Control.URxDataInPtr->EndPtr = &U2_RxBuff[U2_Control.U_RxCounter];                                    //��¼���ν��յĽ���λ��		
				
		U2_Control.URxDataInPtr++;                                                                               //����INָ������
		if(U2_Control.URxDataInPtr==U2_Control.URxDataEndPtr)                                                    //���ָ�뵽����������ݵĽṹ������β����
			U2_Control.URxDataInPtr = &U2_Control.UCB_RxBuffPtrCB[0];                                            //ָ���λ������������ݵĽṹ���������ʼλ�ã�Ҳ����0�ų�Ա
		U2_Control.URxDataInPtr->StartPtr = &U2_RxBuff[U2_Control.U_RxCounter];                                  //��¼�´ν��յ���ʼλ��
		
		if(U2_RXBUFF_SIZE - U2_Control.U_RxCounter >= U2_DMARX_SIZE){                                            //���ʣ��ռ���� DMA���յĵ��������� ����if
			HAL_UART_Receive_DMA(&U2_Control.UART_Handler, &U2_RxBuff[U2_Control.U_RxCounter], U2_DMARX_SIZE);   //����DMA����
            U2_Control.URxDataInPtr->StartPtr = &U2_RxBuff[U2_Control.U_RxCounter];                              //��¼�´ν��յ���ʼλ��	
		}else{                                                                                                   //���ʣ��ռ䲻�����ν����� ����else
			U2_Control.U_RxCounter = 0;                                                                          //U1_Control.U_RxCounter ����
			HAL_UART_Receive_DMA(&U2_Control.UART_Handler, U2_RxBuff, U2_DMARX_SIZE);                            //����DMA����
			U2_Control.URxDataInPtr->StartPtr = U2_RxBuff;                                                       //��¼�´ν��յ���ʼλ��
		}
	}
	
}



/*-------------------------------------------------*/
/*������������3�жϴ�����                        */
/*��  ������                                       */
/*����ֵ����                                       */
/*-------------------------------------------------*/
void USART3_IRQHandler(void)
{		                              
	if(__HAL_UART_GET_FLAG(&U3_Control.UART_Handler,UART_FLAG_IDLE) != RESET){	                                 //������������ж�      	
		__HAL_UART_CLEAR_IDLEFLAG(&U3_Control.UART_Handler);                                                     //��������жϱ�־ 				
		HAL_UART_DMAStop(&U3_Control.UART_Handler);		                                                         //ֹͣDMA
		U3_Control.U_RxCounter += (U3_DMARX_SIZE - __HAL_DMA_GET_COUNTER(&U3_Control.hdma_rx));                  //���㱾�εĽ�������������λ����λ��
		U3_Control.URxDataInPtr->EndPtr = &U3_RxBuff[U3_Control.U_RxCounter];                                    //��¼���ν��յĽ���λ��		
				
		U3_Control.URxDataInPtr++;                                                                               //����INָ������
		if(U3_Control.URxDataInPtr==U3_Control.URxDataEndPtr)                                                    //���ָ�뵽����������ݵĽṹ������β����
			U3_Control.URxDataInPtr = &U3_Control.UCB_RxBuffPtrCB[0];                                            //ָ���λ������������ݵĽṹ���������ʼλ�ã�Ҳ����0�ų�Ա
		U3_Control.URxDataInPtr->StartPtr = &U3_RxBuff[U3_Control.U_RxCounter];                                  //��¼�´ν��յ���ʼλ��
		
		if(U3_RXBUFF_SIZE - U3_Control.U_RxCounter >= U3_DMARX_SIZE){                                            //���ʣ��ռ���� DMA���յĵ��������� ����if
			HAL_UART_Receive_DMA(&U3_Control.UART_Handler, &U3_RxBuff[U3_Control.U_RxCounter], U3_DMARX_SIZE);   //����DMA����
            U3_Control.URxDataInPtr->StartPtr = &U3_RxBuff[U3_Control.U_RxCounter];                              //��¼�´ν��յ���ʼλ��	
		}else{                                                                                                   //���ʣ��ռ䲻�����ν����� ����else
			U3_Control.U_RxCounter = 0;                                                                          //U1_Control.U_RxCounter ����
			HAL_UART_Receive_DMA(&U3_Control.UART_Handler, U3_RxBuff, U3_DMARX_SIZE);                            //����DMA����
			U3_Control.URxDataInPtr->StartPtr = U3_RxBuff;                                                       //��¼�´ν��յ���ʼλ��
		}
	}
	
}













/*-------------------------------------------------*/
/*������������1����DMAͨ��1�жϴ�����            */
/*��  ������                                       */
/*����ֵ����                                       */
/*-------------------------------------------------*/
void DMA1_Channel5_IRQHandler(void)
{
	HAL_DMA_IRQHandler(&U1_Control.hdma_rx);
}

/*-------------------------------------------------*/
/*������������1����DMAͨ��1�жϴ�����            */
/*��  ������                                       */
/*����ֵ����                                       */
/*-------------------------------------------------*/
void DMA1_Channel3_IRQHandler(void)
{
	HAL_DMA_IRQHandler(&U3_Control.hdma_rx);
}

/*-------------------------------------------------*/
/*������������1����DMAͨ��1�жϴ�����            */
/*��  ������                                       */
/*����ֵ����                                       */
/*-------------------------------------------------*/
void DMA1_Channel6_IRQHandler(void)
{
	HAL_DMA_IRQHandler(&U2_Control.hdma_rx);
}
/*-------------------------------------------------*/
/*����������ʱ��4�жϷ�����                      */
/*��  ������                                       */
/*����ֵ����                                       */
/*-------------------------------------------------*/
void TIM4_IRQHandler(void)
{	
	  u1_TxHex('C');
    HAL_TIM_IRQHandler(&htim4);      	
}
/*-------------------------------------------------*/
/*�����������������жϴ�����                     */
/*��  ������                                       */
/*����ֵ����                                       */
/*-------------------------------------------------*/
void NMI_Handler(void)
{

}

/*-------------------------------------------------*/
/*��������Ӳ������������жϴ�����             */
/*��  ������                                       */
/*����ֵ����                                       */
/*-------------------------------------------------*/
void HardFault_Handler(void)
{

}
/*-------------------------------------------------*/
/*�����������жϣ�SWI ָ����õĴ�����           */
/*��  ������                                       */
/*����ֵ����                                       */
/*-------------------------------------------------*/
void SVC_Handler(void)
{
	
}
/*-------------------------------------------------*/
/*���������ɹ����ϵͳ��������                 */
/*��  ������                                       */
/*����ֵ����                                       */
/*-------------------------------------------------*/
void PendSV_Handler(void)
{
	
}
/*-------------------------------------------------*/
/*��������SysTicϵͳ��શ�ʱ��������             */
/*��  ������                                       */
/*����ֵ����                                       */
/*-------------------------------------------------*/
void SysTick_Handler(void)
{  
	HAL_IncTick();	
}
