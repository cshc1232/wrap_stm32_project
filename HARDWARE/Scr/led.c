/*-------------------------------------------------*/
/*            ����˵������STM32ϵ�п�����          */
/*-------------------------------------------------*/
/*                                                 */
/*              ʵ��LED���ܵ�Դ�ļ�                */
/*                                                 */
/*-------------------------------------------------*/

#include "stm32f1xx_hal.h"  //������Ҫ��ͷ�ļ�
#include "led.h"            //������Ҫ��ͷ�ļ�

/*-------------------------------------------------*/
/*����������ʼ��LED����                            */
/*��  ������                                       */
/*����ֵ����                                       */
/*-------------------------------------------------*/void LED_Init(void)
{    	 
	GPIO_InitTypeDef GPIO_InitStruct;                 //����һ������GPIO�ı���
		
	__HAL_RCC_GPIOA_CLK_ENABLE();			          //ʹ��GPIOBʱ��

	GPIO_InitStruct.Pin = GPIO_PIN_11 | GPIO_PIN_12;  //����PA11 12
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;       //�������
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;      //����
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);           //����
	
	LED_AOFF;                                         //LEDȫ��Ϩ��
}

