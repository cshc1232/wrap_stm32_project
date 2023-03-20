/*-------------------------------------------------*/
/*            ����˵������STM32ϵ�п�����          */
/*-------------------------------------------------*/
/*                                                 */
/*            ʵ�ָ������ڹ��ܵ�Դ�ļ�             */
/*                                                 */
/*-------------------------------------------------*/

#include "stm32f1xx_hal.h"    //������Ҫ��ͷ�ļ�
#include "usart.h"            //������Ҫ��ͷ�ļ�

UCB_CB U1_Control;            //���ƴ���1�Ľṹ��
UCB_CB U2_Control;            //���ƴ���1�Ľṹ��
UCB_CB U3_Control;            //���ƴ���1�Ľṹ��

uint8_t  U1_TxBuff[U1_TXBUFF_SIZE];         //����һ�����黺����������1���ͻ����� 
uint8_t  U1_RxBuff[U1_RXBUFF_SIZE];         //����һ�����黺����������1�����ճ��� 
uint8_t  U1Copy_RxBuff[U1_COPYBUFF_SIZE];   //����һ�����黺����������1����������ݵĸ���������

uint8_t  U2_TxBuff[U2_TXBUFF_SIZE];         //����һ�����黺����������1���ͻ����� 
uint8_t  U2_RxBuff[U2_RXBUFF_SIZE];         //����һ�����黺����������1�����ճ��� 
uint8_t  U2Copy_RxBuff[U2_COPYBUFF_SIZE];   //����һ�����黺����������1����������ݵĸ���������

uint8_t  U3_TxBuff[U3_TXBUFF_SIZE];         //����һ�����黺����������1���ͻ����� 
uint8_t  U3_RxBuff[U3_RXBUFF_SIZE];         //����һ�����黺����������1�����ճ��� 
uint8_t  U3Copy_RxBuff[U3_COPYBUFF_SIZE];   //����һ�����黺����������1����������ݵĸ���������




/*-------------------------------------------------*/
/*����������ʼ������1                              */
/*��  ����bound��������                            */
/*����ֵ����                                       */
/*-------------------------------------------------*/
void U1_Init(uint32_t bound)
{	
	U1_Control.UART_Handler.Instance=USART1;					        //����1
	U1_Control.UART_Handler.Init.BaudRate=bound;				        //���ò�����
	U1_Control.UART_Handler.Init.WordLength=UART_WORDLENGTH_8B;         //�����ֳ�Ϊ8λ���ݸ�ʽ
	U1_Control.UART_Handler.Init.StopBits=UART_STOPBITS_1;	            //����һ��ֹͣλ
	U1_Control.UART_Handler.Init.Parity=UART_PARITY_NONE;		        //��������żУ��λ
	U1_Control.UART_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;         //������Ӳ������
	U1_Control.UART_Handler.Init.Mode=UART_MODE_TX_RX;		            //�����շ�ģʽ
	HAL_UART_Init(&U1_Control.UART_Handler);					        //���ô���1
	__HAL_UART_CLEAR_IDLEFLAG(&U1_Control.UART_Handler);                //��������жϱ�־ 
	__HAL_UART_ENABLE_IT(&U1_Control.UART_Handler,UART_IT_IDLE);        //���������ж�	
	U1Rx_Buff_Init();                                                   //��ʼ������1����������ݵĸ�������
	HAL_UART_Receive_DMA(&U1_Control.UART_Handler, U1_RxBuff, U1_DMARX_SIZE);  //����DMA����
}


/*-------------------------------------------------*/
/*����������ʼ������2                              */
/*��  ����bound��������                            */
/*����ֵ����                                       */
/*-------------------------------------------------*/
void U2_Init(uint32_t bound)
{	
	U2_Control.UART_Handler.Instance=USART2;					        //����1
	U2_Control.UART_Handler.Init.BaudRate=bound;				        //���ò�����
	U2_Control.UART_Handler.Init.WordLength=UART_WORDLENGTH_8B;         //�����ֳ�Ϊ8λ���ݸ�ʽ
	U2_Control.UART_Handler.Init.StopBits=UART_STOPBITS_1;	            //����һ��ֹͣλ
	U2_Control.UART_Handler.Init.Parity=UART_PARITY_NONE;		        //��������żУ��λ
	U2_Control.UART_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;         //������Ӳ������
	U2_Control.UART_Handler.Init.Mode=UART_MODE_TX_RX;		            //�����շ�ģʽ
	HAL_UART_Init(&U2_Control.UART_Handler);					        //���ô���1
	__HAL_UART_CLEAR_IDLEFLAG(&U2_Control.UART_Handler);                //��������жϱ�־ 
	__HAL_UART_ENABLE_IT(&U2_Control.UART_Handler,UART_IT_IDLE);        //���������ж�	
	U2Rx_Buff_Init();                                                   //��ʼ������1����������ݵĸ�������
	HAL_UART_Receive_DMA(&U2_Control.UART_Handler, U2_RxBuff, U2_DMARX_SIZE);  //����DMA����
}



/*-------------------------------------------------*/
/*����������ʼ������3                              */
/*��  ����bound��������                            */
/*����ֵ����                                       */
/*-------------------------------------------------*/
void U3_Init(uint32_t bound)
{	
	U3_Control.UART_Handler.Instance=USART3;					        //����1
	U3_Control.UART_Handler.Init.BaudRate=bound;				        //���ò�����
	U3_Control.UART_Handler.Init.WordLength=UART_WORDLENGTH_8B;         //�����ֳ�Ϊ8λ���ݸ�ʽ
	U3_Control.UART_Handler.Init.StopBits=UART_STOPBITS_1;	            //����һ��ֹͣλ
	U3_Control.UART_Handler.Init.Parity=UART_PARITY_NONE;		        //��������żУ��λ
	U3_Control.UART_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;         //������Ӳ������
	U3_Control.UART_Handler.Init.Mode=UART_MODE_TX_RX;		            //�����շ�ģʽ
	HAL_UART_Init(&U3_Control.UART_Handler);					        //���ô���1
	__HAL_UART_CLEAR_IDLEFLAG(&U3_Control.UART_Handler);                //��������жϱ�־ 
	__HAL_UART_ENABLE_IT(&U3_Control.UART_Handler,UART_IT_IDLE);        //���������ж�	
	U3Rx_Buff_Init();                                                   //��ʼ������1����������ݵĸ�������
	HAL_UART_Receive_DMA(&U3_Control.UART_Handler, U3_RxBuff, U3_DMARX_SIZE);  //����DMA����
}




/*-------------------------------------------------*/
/*������������1�ĵײ��ʼ��                        */
/*��  ����huart���������þ��                      */
/*����ֵ����                                       */
/*˵  �����˺����ᱻHAL_UART_Init()�ص�����        */
/*-------------------------------------------------*/
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{  
	GPIO_InitTypeDef GPIO_Initure;                 //GPIO�˿����ñ���
	
	if(huart->Instance==USART1){                   //������õ��Ǵ���1��������if��֧�����д���1�ĵײ��ʼ��
		__HAL_RCC_GPIOA_CLK_ENABLE();			   //ʹ��GPIOAʱ��
		__HAL_RCC_USART1_CLK_ENABLE();			   //ʹ�ܴ���1ʱ��
		__HAL_RCC_DMA1_CLK_ENABLE();               //ʹ��DMA1ʱ��
		
		GPIO_Initure.Pin = GPIO_PIN_9;             //׼������PA9
		GPIO_Initure.Mode = GPIO_MODE_AF_PP;       //���ù���
		GPIO_Initure.Pull = GPIO_PULLUP;           //����
		GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH; //����
		HAL_GPIO_Init(GPIOA, &GPIO_Initure);       //����PA9 10
		
		GPIO_Initure.Pin = GPIO_PIN_10;            //׼������PA10
		GPIO_Initure.Mode = GPIO_MODE_INPUT;       //���ù���
		HAL_GPIO_Init(GPIOA, &GPIO_Initure);       //����PA9 10
		
		HAL_NVIC_SetPriority(USART1_IRQn,0,3);	   //���ô���1�жϵ���ռ���ȼ�Ϊ0�������ȼ���3������Ҫע�⣬G0ϵ���ж������ȼ�������Ч
		HAL_NVIC_EnableIRQ(USART1_IRQn);           //ʹ�ܴ���1���ж�
		
		U1_Control.hdma_rx.Instance                 = DMA1_Channel5;               //DMA1ͨ��5
		U1_Control.hdma_rx.Init.Direction           = DMA_PERIPH_TO_MEMORY;        //���赽�洢��
		U1_Control.hdma_rx.Init.PeriphInc           = DMA_PINC_DISABLE;            //���費����
		U1_Control.hdma_rx.Init.MemInc              = DMA_MINC_ENABLE;             //�洢������
		U1_Control.hdma_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;         //���ֽڴ�ȡ
		U1_Control.hdma_rx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;         //���ֽڴ�ȡ
		U1_Control.hdma_rx.Init.Mode                = DMA_NORMAL;                  //����ģʽ
		U1_Control.hdma_rx.Init.Priority            = DMA_PRIORITY_HIGH;           //�����ȼ�
		HAL_DMA_Init(&U1_Control.hdma_rx);                                         //����

		__HAL_LINKDMA(huart, hdmarx, U1_Control.hdma_rx);                          //�ʹ���1DMA����

		HAL_NVIC_SetPriority(DMA1_Channel5_IRQn, 0, 0);                            //����DMA1ͨ��5���жϣ����ȼ�
		HAL_NVIC_EnableIRQ(DMA1_Channel5_IRQn);                                    //ʹ��DMA1ͨ��5���ж�            
	}
	
		if(huart->Instance==USART2){
	    __HAL_RCC_GPIOA_CLK_ENABLE();			   //ʹ��GPIOAʱ��
		  __HAL_RCC_USART2_CLK_ENABLE();			   //ʹ�ܴ���2ʱ��
		  __HAL_RCC_DMA1_CLK_ENABLE();               //ʹ��DMA1ʱ��
 

		GPIO_Initure.Pin = GPIO_PIN_2;             //׼������PA9
		GPIO_Initure.Mode = GPIO_MODE_AF_PP;       //���ù���
		GPIO_Initure.Pull = GPIO_PULLUP;           //����
		GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH; //����
		HAL_GPIO_Init(GPIOA, &GPIO_Initure);       //����PA9 10
		
		GPIO_Initure.Pin = GPIO_PIN_3;            //׼������PA10
		GPIO_Initure.Mode = GPIO_MODE_INPUT;       //���ù���
		HAL_GPIO_Init(GPIOA, &GPIO_Initure);       //����PA9 10
		
		HAL_NVIC_SetPriority(USART2_IRQn,0,2);	   //���ô���1�жϵ���ռ���ȼ�Ϊ0�������ȼ���3������Ҫע�⣬G0ϵ���ж������ȼ�������Ч
		HAL_NVIC_EnableIRQ(USART2_IRQn);           //ʹ�ܴ���1���ж�
			
			
			
		U2_Control.hdma_rx.Instance                 = DMA1_Channel6;               //DMA1ͨ��5
		U2_Control.hdma_rx.Init.Direction           = DMA_PERIPH_TO_MEMORY;        //���赽�洢��
		U2_Control.hdma_rx.Init.PeriphInc           = DMA_PINC_DISABLE;            //���費����
		U2_Control.hdma_rx.Init.MemInc              = DMA_MINC_ENABLE;             //�洢������
		U2_Control.hdma_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;         //���ֽڴ�ȡ
		U2_Control.hdma_rx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;         //���ֽڴ�ȡ
		U2_Control.hdma_rx.Init.Mode                = DMA_NORMAL;                  //����ģʽ
		U2_Control.hdma_rx.Init.Priority            = DMA_PRIORITY_HIGH;           //�����ȼ�
		HAL_DMA_Init(&U2_Control.hdma_rx);                                         //����

		__HAL_LINKDMA(huart, hdmarx, U2_Control.hdma_rx);                          //�ʹ���2DMA����

		HAL_NVIC_SetPriority(DMA1_Channel6_IRQn, 0, 1);                            //����DMA1ͨ��4���жϣ����ȼ�
		HAL_NVIC_EnableIRQ(DMA1_Channel6_IRQn);          	
		
		}
		
	 if(huart->Instance==USART3){
		 
		  __HAL_RCC_GPIOB_CLK_ENABLE();			   //ʹ��GPIOAʱ��
		  __HAL_RCC_USART3_CLK_ENABLE();			   //ʹ�ܴ���2ʱ��
		  __HAL_RCC_DMA1_CLK_ENABLE();               //ʹ��DMA1ʱ��
		 
		GPIO_Initure.Pin = GPIO_PIN_10;             //׼������PA9
		GPIO_Initure.Mode = GPIO_MODE_AF_PP;       //���ù���
		GPIO_Initure.Pull = GPIO_PULLUP;           //����
		GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH; //����
		HAL_GPIO_Init(GPIOB, &GPIO_Initure);       //����PA9 10
		
		GPIO_Initure.Pin = GPIO_PIN_11;            //׼������PA10
		GPIO_Initure.Mode = GPIO_MODE_INPUT;       //���ù���
		HAL_GPIO_Init(GPIOB, &GPIO_Initure);       //����PA9 10
		
		HAL_NVIC_SetPriority(USART3_IRQn,0,1);	   //���ô���1�жϵ���ռ���ȼ�Ϊ0�������ȼ���3������Ҫע�⣬G0ϵ���ж������ȼ�������Ч
		HAL_NVIC_EnableIRQ(USART3_IRQn);           //ʹ�ܴ���1���ж�
		 
		 
		U3_Control.hdma_rx.Instance                 = DMA1_Channel3;               //DMA1ͨ��5
		U3_Control.hdma_rx.Init.Direction           = DMA_PERIPH_TO_MEMORY;        //���赽�洢��
		U3_Control.hdma_rx.Init.PeriphInc           = DMA_PINC_DISABLE;            //���費����
		U3_Control.hdma_rx.Init.MemInc              = DMA_MINC_ENABLE;             //�洢������
		U3_Control.hdma_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;         //���ֽڴ�ȡ
		U3_Control.hdma_rx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;         //���ֽڴ�ȡ
		U3_Control.hdma_rx.Init.Mode                = DMA_NORMAL;                  //����ģʽ
		U3_Control.hdma_rx.Init.Priority            = DMA_PRIORITY_HIGH;           //�����ȼ�
		HAL_DMA_Init(&U3_Control.hdma_rx);                                         //���� 
		 
		 
		 
		__HAL_LINKDMA(huart, hdmarx, U3_Control.hdma_rx);                          //�ʹ���2DMA����

		HAL_NVIC_SetPriority(DMA1_Channel3_IRQn, 0, 2);                            //����DMA1ͨ��3���жϣ����ȼ�
		HAL_NVIC_EnableIRQ(DMA1_Channel3_IRQn);      
		 
		 
	 }
	
}

/*-------------------------------------------------*/
/*������������1 printf����                         */
/*��  ����fmt,...  ��ʽ������ַ����Ͳ���          */
/*����ֵ����                                       */
/*-------------------------------------------------*/
void u1_printf(char* fmt,...) 
{  
	unsigned int i;    	
	va_list ap;
	va_start(ap,fmt);
	vsprintf((char *)U1_TxBuff,fmt,ap);
	va_end(ap);
	
	U1_Control.U_Txdatalen = strlen((const char*)U1_TxBuff);	                 //���㴮��1��Ҫ���͵�������
	while(__HAL_UART_GET_FLAG(&U1_Control.UART_Handler,UART_FLAG_TC)!=SET);	     //�ȴ�����1���Ϳ��У�Ȼ����ܷ�������	
	for(i = 0;i < U1_Control.U_Txdatalen;i ++){				                     //����forѭ����һ���ֽڣ�һ���ֽڵķ���
		U1_Control.UART_Handler.Instance->DR = U1_TxBuff[i];                     //����Ҫ���͵��ֽڣ���䵽����1����������
		while(__HAL_UART_GET_FLAG(&U1_Control.UART_Handler,UART_FLAG_TC)!=SET);  //�ȴ������ֽڷ��ͽ������ſ��Է�����һ���ֽ�	
	}	
}

/*-------------------------------------------------*/
/*������������2 printf����                         */
/*��  ����fmt,...  ��ʽ������ַ����Ͳ���          */
/*����ֵ����                                       */
/*-------------------------------------------------*/
void u2_printf(char* fmt,...) 
{  
	unsigned int i;    	
	va_list ap;
	va_start(ap,fmt);
	vsprintf((char *)U2_TxBuff,fmt,ap);
	va_end(ap);
	
	U2_Control.U_Txdatalen = strlen((const char*)U2_TxBuff);	                 //���㴮��1��Ҫ���͵�������
	while(__HAL_UART_GET_FLAG(&U2_Control.UART_Handler,UART_FLAG_TC)!=SET);	     //�ȴ�����1���Ϳ��У�Ȼ����ܷ�������	
	for(i = 0;i < U2_Control.U_Txdatalen;i ++){				                     //����forѭ����һ���ֽڣ�һ���ֽڵķ���
		U2_Control.UART_Handler.Instance->DR = U2_TxBuff[i];                     //����Ҫ���͵��ֽڣ���䵽����1����������
		while(__HAL_UART_GET_FLAG(&U2_Control.UART_Handler,UART_FLAG_TC)!=SET);  //�ȴ������ֽڷ��ͽ������ſ��Է�����һ���ֽ�	
	}	
}

/*-------------------------------------------------*/
/*������������3 printf����                         */
/*��  ����fmt,...  ��ʽ������ַ����Ͳ���          */
/*����ֵ����                                       */
/*-------------------------------------------------*/
void u3_printf(char* fmt,...) 
{  
	unsigned int i;    	
	va_list ap;
	va_start(ap,fmt);
	vsprintf((char *)U3_TxBuff,fmt,ap);
	va_end(ap);
	
	U3_Control.U_Txdatalen = strlen((const char*)U3_TxBuff);	                 //���㴮��1��Ҫ���͵�������
	while(__HAL_UART_GET_FLAG(&U3_Control.UART_Handler,UART_FLAG_TC)!=SET);	     //�ȴ�����1���Ϳ��У�Ȼ����ܷ�������	
	for(i = 0;i < U3_Control.U_Txdatalen;i ++){				                     //����forѭ����һ���ֽڣ�һ���ֽڵķ���
		U3_Control.UART_Handler.Instance->DR = U3_TxBuff[i];                     //����Ҫ���͵��ֽڣ���䵽����1����������
		while(__HAL_UART_GET_FLAG(&U3_Control.UART_Handler,UART_FLAG_TC)!=SET);  //�ȴ������ֽڷ��ͽ������ſ��Է�����һ���ֽ�	
	}	
}

/*----------------------------------------------------------*/
/*����������ʼ������������ݵĽṹ������                    */
/*��  ������                                                */
/*����ֵ����                                                */
/*----------------------------------------------------------*/
void U1Rx_Buff_Init(void)
{	
	U1_Control.URxDataInPtr  = &U1_Control.UCB_RxBuffPtrCB[0];           //ָ���ǽ���������ʼλ�ã���ֹλ�õĽṹ�������Ĳ������ݵ�λ�õ�ָ�룬���ʼ��ʱ��ָ��������0�ų�Ա
	U1_Control.URxDataOutPtr =  U1_Control.URxDataInPtr;                 //ָ���ǽ���������ʼλ�ã���ֹλ�õĽṹ����������ȡ���ݵ�λ�õ�ָ�룬���ʼ��ʱ��ָ��������0�ų�Ա
  U1_Control.URxDataEndPtr = &U1_Control.UCB_RxBuffPtrCB[NUM-1];       //ָ���ǽ���������ʼλ�ã���ֹλ�õĽṹ�������Ľ�β���ݵ�λ�õ�ָ�룬���ʼ��ʱ��ָ�����������һ����Ա
	U1_Control.URxDataInPtr->StartPtr = U1_RxBuff;                       //��ʼλ��
	U1_Control.URxDataInPtr->EndPtr = U1_RxBuff;                         //��ʼλ��
	U1_Control.U_RxCounter = 0;                                          //����1�ۼƽ���λ�ñ���������Ϊ0
	HAL_UART_DMAStop(&U1_Control.UART_Handler);		                             //ֹͣDMA
	HAL_UART_Receive_DMA(&U1_Control.UART_Handler, U1_RxBuff, U1_DMARX_SIZE);    //����DMA����
}


/*----------------------------------------------------------*/
/*����������ʼ������������ݵĽṹ������                    */
/*��  ������                                                */
/*����ֵ����                                                */
/*----------------------------------------------------------*/
void U2Rx_Buff_Init(void)
{	
	U2_Control.URxDataInPtr  = &U2_Control.UCB_RxBuffPtrCB[0];           //ָ���ǽ���������ʼλ�ã���ֹλ�õĽṹ�������Ĳ������ݵ�λ�õ�ָ�룬���ʼ��ʱ��ָ��������0�ų�Ա
	U2_Control.URxDataOutPtr =  U2_Control.URxDataInPtr;                 //ָ���ǽ���������ʼλ�ã���ֹλ�õĽṹ����������ȡ���ݵ�λ�õ�ָ�룬���ʼ��ʱ��ָ��������0�ų�Ա
  U2_Control.URxDataEndPtr = &U2_Control.UCB_RxBuffPtrCB[NUM-1];       //ָ���ǽ���������ʼλ�ã���ֹλ�õĽṹ�������Ľ�β���ݵ�λ�õ�ָ�룬���ʼ��ʱ��ָ�����������һ����Ա
	U2_Control.URxDataInPtr->StartPtr = U2_RxBuff;                       //��ʼλ��
	U2_Control.URxDataInPtr->EndPtr = U2_RxBuff;                         //��ʼλ��
	U2_Control.U_RxCounter = 0;                                          //����1�ۼƽ���λ�ñ���������Ϊ0
	HAL_UART_DMAStop(&U2_Control.UART_Handler);		                             //ֹͣDMA
	HAL_UART_Receive_DMA(&U2_Control.UART_Handler, U2_RxBuff, U2_DMARX_SIZE);    //����DMA����
}



/*----------------------------------------------------------*/
/*����������ʼ������������ݵĽṹ������                    */
/*��  ������                                                */
/*����ֵ����                                                */
/*----------------------------------------------------------*/
void U3Rx_Buff_Init(void)
{	
	U3_Control.URxDataInPtr  = &U3_Control.UCB_RxBuffPtrCB[0];           //ָ���ǽ���������ʼλ�ã���ֹλ�õĽṹ�������Ĳ������ݵ�λ�õ�ָ�룬���ʼ��ʱ��ָ��������0�ų�Ա
	U3_Control.URxDataOutPtr =  U3_Control.URxDataInPtr;                 //ָ���ǽ���������ʼλ�ã���ֹλ�õĽṹ����������ȡ���ݵ�λ�õ�ָ�룬���ʼ��ʱ��ָ��������0�ų�Ա
  U3_Control.URxDataEndPtr = &U3_Control.UCB_RxBuffPtrCB[NUM-1];       //ָ���ǽ���������ʼλ�ã���ֹλ�õĽṹ�������Ľ�β���ݵ�λ�õ�ָ�룬���ʼ��ʱ��ָ�����������һ����Ա
	U3_Control.URxDataInPtr->StartPtr = U3_RxBuff;                       //��ʼλ��
	U3_Control.URxDataInPtr->EndPtr = U3_RxBuff;                         //��ʼλ��
	U3_Control.U_RxCounter = 0;                                          //����1�ۼƽ���λ�ñ���������Ϊ0
	HAL_UART_DMAStop(&U3_Control.UART_Handler);		                             //ֹͣDMA
	HAL_UART_Receive_DMA(&U3_Control.UART_Handler, U3_RxBuff, U3_DMARX_SIZE);    //����DMA����
}



/*-------------------------------------------------*/
/*������������1����һ��16��������                  */
/*��  ����data ��Ҫ���͵�����                      */
/*����ֵ����                                       */
/*-------------------------------------------------*/
void u1_TxHex(uint8_t data) 
{  
	while(__HAL_UART_GET_FLAG(&U1_Control.UART_Handler,UART_FLAG_TC)!=SET);	 //�ȴ�����1���Ϳ��У�Ȼ����ܷ�������	
	U1_Control.UART_Handler.Instance->DR = data;                             //����Ҫ���͵��ֽڣ���䵽����1����������
	while(__HAL_UART_GET_FLAG(&U1_Control.UART_Handler,UART_FLAG_TC)!=SET);  //�ȴ������ֽڷ��ͽ���	
}


/*-------------------------------------------------*/
/*������������1����һ��16��������                  */
/*��  ����data ��Ҫ���͵�����                      */
/*����ֵ����                                       */
/*-------------------------------------------------*/
void u2_TxHex(uint8_t data) 
{  
	while(__HAL_UART_GET_FLAG(&U2_Control.UART_Handler,UART_FLAG_TC)!=SET);	 //�ȴ�����3���Ϳ��У�Ȼ����ܷ�������	
	U2_Control.UART_Handler.Instance->DR = data;                             //����Ҫ���͵��ֽڣ���䵽����1����������
	while(__HAL_UART_GET_FLAG(&U2_Control.UART_Handler,UART_FLAG_TC)!=SET);  //�ȴ������ֽڷ��ͽ���	
}


/*-------------------------------------------------*/
/*������������1����һ��16��������                  */
/*��  ����data ��Ҫ���͵�����                      */
/*����ֵ����                                       */
/*-------------------------------------------------*/
void u3_TxHex(uint8_t data) 
{  
	while(__HAL_UART_GET_FLAG(&U3_Control.UART_Handler,UART_FLAG_TC)!=SET);	 //�ȴ�����3���Ϳ��У�Ȼ����ܷ�������	
	U3_Control.UART_Handler.Instance->DR = data;                             //����Ҫ���͵��ֽڣ���䵽����1����������
	while(__HAL_UART_GET_FLAG(&U3_Control.UART_Handler,UART_FLAG_TC)!=SET);  //�ȴ������ֽڷ��ͽ���	
}
