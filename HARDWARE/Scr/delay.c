/*-------------------------------------------------*/
/*            ����˵������STM32ϵ�п�����          */
/*-------------------------------------------------*/
/*                                                 */
/*          ʹ��SysTickʵ����ʱ���ܵ�Դ�ļ�        */
/*                                                 */
/*-------------------------------------------------*/

#include "stm32f1xx_hal.h"  //������Ҫ��ͷ�ļ�
#include "delay.h"          //������Ҫ��ͷ�ļ�

extern __IO uint32_t uwTick;

/*-------------------------------------------------*/
/*����������ʼ���ӳټ����� ����ʱ�Ӻ���            */
/*��  ������                                       */
/*����ֵ����                                       */
/*-------------------------------------------------*/
void Delay_CLock_Init(void)
{  
	RCC_OscInitTypeDef RCC_OscInitStruct;
    RCC_ClkInitTypeDef RCC_ClkInitStruct;
	
	SysTick->CTRL &=~ (SysTick_CTRL_TICKINT_Msk|SysTick_CTRL_ENABLE_Msk);               		 //HAL_Init����������SysTick���ж� �ڴ˹ر�SysTick�͹ر��ж�   	
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK_DIV8);                           		 //����SysTickƵ��ΪHCLK 8��Ƶ++++
	
	RCC_OscInitStruct.OscillatorType      = RCC_OSCILLATORTYPE_HSE;                              //ʹ���ⲿ����������8M
	RCC_OscInitStruct.HSEState            = RCC_HSE_ON;                                          //���ⲿ���پ���
	RCC_OscInitStruct.PLL.PLLState        = RCC_PLL_ON;                                          //����PLL
	RCC_OscInitStruct.PLL.PLLSource       = RCC_PLLSOURCE_HSE;                                   //PLLʱ��Դѡ��HSE �ⲿ����
	RCC_OscInitStruct.PLL.PLLMUL          = RCC_PLL_MUL9;                                        //9��Ƶ 8*9=72
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)                               			 //���ã����ʧ�ܽ���if������
		NVIC_SystemReset();                         
	
	RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;                                    //SYSCLKʱ��Դѡ��PLL   8*12/3=32MHz
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;                                           //AHB  1��Ƶ  72/1=72MHz
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;                                            //APB1 2��Ƶ  72/2=36MHz
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;                                            //APB2 1��Ƶ  72/1=72MHz
	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)                      //���ã����ʧ�ܽ���if������
		NVIC_SystemReset();                                                                      //����
}
/*-------------------------------------------------*/
/*���������ӳ�΢�뺯��                             */
/*��  ����us����ʱ����΢��                         */
/*����ֵ����                                       */
/*-------------------------------------------------*/
void Delay_Us(uint16_t us)
{		
	SysTick->LOAD=us*US_UNIT;                             //������������ֵ��Ҫע��SysTick�ǵ���������
	SysTick->VAL=0x00;                                    //��յ�ǰ��������ֵ
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;              //ʹ��SysTick������������ֵ���ص��������У���ʼ��������
	while(!(SysTick->CTRL&SysTick_CTRL_COUNTFLAG_Msk));   //�ȴ�ʱ�䵽��
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;              //�رռ����� 
}
/*-------------------------------------------------*/
/*���������ӳٺ��뺯��                             */
/*��  ����ms����ʱ���ٺ���                         */
/*����ֵ����                                       */
/*-------------------------------------------------*/
void Delay_Ms(uint16_t ms)
{
	//��������ע��һ������SysTickʱ�Ӽ�������24λ�ģ�������ʱ���ܳ������ֵMS_UNIT
	//����������MS_UNITΪ���ޣ�С��MS_UNIT����ʱһ�μ������У�����MS_UNIT�Ķ�μ���		
	/*-----------if�жϣ�С��MS_UNIT��ʱ�������ִ��if��֧------------------*/
	if(ms<=MS_UNIT){                                   
		SysTick->LOAD=ms*US_UNIT*1000;                           //������������ֵ��Ҫע��SysTick�ǵ���������        
		SysTick->VAL=0x00;                                       //��յ�ǰ��������ֵ
		SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;                  //ʹ��SysTick������������ֵ���ص��������У���ʼ����
		while(!(SysTick->CTRL&SysTick_CTRL_COUNTFLAG_Msk));      //�ȴ�ʱ�䵽��
		SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;                 //�رռ����� 	
	}  
	/*--------------����MS_UNIT��ʱ�������ִ��else��֧-------------------*/
	else{ 
		while(ms/MS_UNIT){                                       //��ȡ�������֣�ÿ����ʱMS_UNIT
			SysTick->LOAD=MS_UNIT*US_UNIT*1000;                  //������������ֵ��Ҫע��SysTick�ǵ���������        
			SysTick->VAL=0x00;                                   //��յ�ǰ��������ֵ
			SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;             //ʹ��SysTick������������ֵ���ص��������У���ʼ����
			while(!(SysTick->CTRL&SysTick_CTRL_COUNTFLAG_Msk));  //�ȴ�ʱ�䵽��
			SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;             //�رռ����� 
			ms-=MS_UNIT;                                         //���¼���ʣ����ʱֵ
		} 	
		if(ms%MS_UNIT){                                          //��������������ټ�������
			SysTick->LOAD=(ms%MS_UNIT)*US_UNIT*1000;             //������������ֵ��Ҫע��SysTick�ǵ���������  
			SysTick->VAL =0x00;                                  //��յ�ǰ��������ֵ
			SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;             //ʹ��SysTick������������ֵ���ص��������У���ʼ����  
			while(!(SysTick->CTRL&SysTick_CTRL_COUNTFLAG_Msk));  //�ȴ�ʱ�䵽��
			SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;             //�رռ�����
		}
	}
} 
/*-------------------------------------------------*/
/*���������ض���HAL_GetTick����                    */
/*��  ������                                       */
/*����ֵ����ʱ����ֵ                               */
/*-------------------------------------------------*/
uint32_t HAL_GetTick(void)
{
	Delay_Ms(1);       //��ʱ1ms
	return ++uwTick;   //����ȫ����ʱֵ
}
/*-------------------------------------------------*/
/*���������ض���HAL_InitTick����                   */
/*��  ������                                       */
/*����ֵ��HAL_OK                                   */
/*-------------------------------------------------*/
HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority)
{
	return HAL_OK;    //ʲôҲ��������ֱ�ӷ���HAL_OK
}
