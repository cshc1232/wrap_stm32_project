/*-------------------------------------------------*/
/*            ����˵������STM32ϵ�п�����          */
/*-------------------------------------------------*/
/*                                                 */
/*             ʵ�ֶ�ʱ�����ܵ�Դ�ļ�              */
/*                                                 */
/*-------------------------------------------------*/

#include "stm32f1xx_hal.h"  //������Ҫ��ͷ�ļ�
#include "timer.h"          //������Ҫ��ͷ�ļ�
#include "led.h"            //������Ҫ��ͷ�ļ�

TIM_HandleTypeDef htim1;    //��ʱ��1��� 
TIM_HandleTypeDef htim2;    //��ʱ��2��� 
TIM_HandleTypeDef htim3;    //��ʱ��3��� 
TIM_HandleTypeDef htim4;    //��ʱ��4��� 

/*-------------------------------------------------*/
/*����������ʱ��1��ʼ��                            */
/*��  ����arr���Զ���װֵ                          */
/*��  ����psc��ʱ��Ԥ��Ƶ��                        */
/*��  ����Repe���ظ�������ֵ                       */
/*����ֵ����                                       */
/*-------------------------------------------------*/
void TIM1_Init(uint16_t arr, uint16_t psc, uint16_t Repe)
{
	htim1.Instance = TIM1;                                         //���ö�ʱ��1
	htim1.Init.Prescaler = psc-1;                                  //���ö�ʱ��Ԥ��Ƶ��
	htim1.Init.Period = arr-1;                                     //�����Զ���װ��ֵ
	htim1.Init.CounterMode = TIM_COUNTERMODE_UP;                   //���ϼ���ģʽ
	htim1.Init.RepetitionCounter = Repe;                           //�ظ�������ֵΪRepe
	htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE; //��ʹ��Ԥװ��
	HAL_TIM_Base_Init(&htim1);                                     //����
	__HAL_TIM_CLEAR_IT(&htim1, TIM_IT_UPDATE);                     //����жϱ�־
	HAL_TIM_Base_Start_IT(&htim1);                                 //ʹ�ܶ�ʱ��1�Ͷ�ʱ��1�����жϣ�TIM_IT_UPDATE
}
/*-------------------------------------------------*/
/*����������ʱ��2��ʼ��                            */
/*��  ����arr���Զ���װֵ                          */
/*��  ����psc��ʱ��Ԥ��Ƶ��                        */
/*��  ����Repe���ظ�������ֵ                       */
/*����ֵ����                                       */
/*-------------------------------------------------*/
void TIM2_Init(uint16_t arr, uint16_t psc)
{
	htim2.Instance = TIM2;                                         //���ö�ʱ��2
	htim2.Init.Prescaler = psc-1;                                  //���ö�ʱ��Ԥ��Ƶ��
	htim2.Init.Period = arr-1;                                     //�����Զ���װ��ֵ
	htim2.Init.CounterMode = TIM_COUNTERMODE_UP;                   //���ϼ���ģʽ
	htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE; //��ʹ��Ԥװ��
	HAL_TIM_Base_Init(&htim2);                                     //����
	__HAL_TIM_CLEAR_IT(&htim2, TIM_IT_UPDATE);                     //����жϱ�־
	HAL_TIM_Base_Start_IT(&htim2);                                 //ʹ�ܶ�ʱ��2�Ͷ�ʱ��2�����жϣ�TIM_IT_UPDATE
}
/*-------------------------------------------------*/
/*����������ʱ��3��ʼ��                            */
/*��  ����arr���Զ���װֵ                          */
/*��  ����psc��ʱ��Ԥ��Ƶ��                        */
/*��  ����Repe���ظ�������ֵ                       */
/*����ֵ����                                       */
/*-------------------------------------------------*/
void TIM3_Init(uint16_t arr, uint16_t psc)
{
	htim3.Instance = TIM3;                                         //���ö�ʱ��3
	htim3.Init.Prescaler = psc-1;                                  //���ö�ʱ��Ԥ��Ƶ��
	htim3.Init.Period = arr-1;                                     //�����Զ���װ��ֵ
	htim3.Init.CounterMode = TIM_COUNTERMODE_UP;                   //���ϼ���ģʽ
	htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE; //��ʹ��Ԥװ��
	HAL_TIM_Base_Init(&htim3);                                     //����
	__HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE);                     //����жϱ�־
	HAL_TIM_Base_Start_IT(&htim3);                                 //ʹ�ܶ�ʱ��3�Ͷ�ʱ��3�����жϣ�TIM_IT_UPDATE
}
/*-------------------------------------------------*/
/*����������ʱ��4��ʼ��                            */
/*��  ����arr���Զ���װֵ                          */
/*��  ����psc��ʱ��Ԥ��Ƶ��                        */
/*��  ����Repe���ظ�������ֵ                       */
/*����ֵ����                                       */
/*-------------------------------------------------*/
void TIM4_Init(uint16_t arr, uint16_t psc)
{
	htim4.Instance = TIM4;                                         //���ö�ʱ��4
	htim4.Init.Prescaler = psc-1;                                  //���ö�ʱ��Ԥ��Ƶ��
	htim4.Init.Period = arr-1;                                     //�����Զ���װ��ֵ
	htim4.Init.CounterMode = TIM_COUNTERMODE_UP;                   //���ϼ���ģʽ
	htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE; //��ʹ��Ԥװ��
	HAL_TIM_Base_Init(&htim4);                                     //����
	__HAL_TIM_CLEAR_IT(&htim4, TIM_IT_UPDATE);                     //����жϱ�־
	HAL_TIM_Base_Start_IT(&htim4);                                 //ʹ�ܶ�ʱ��4�Ͷ�ʱ��4�����жϣ�TIM_IT_UPDATE
}
/*-------------------------------------------------*/
/*����������ʱ���ײ�����������ʱ�ӣ������ж����ȼ� */
/*��  ����htim����ʱ�����                         */
/*����ֵ����                                       */
/*˵  �����˺����ᱻHAL_TIM_Base_Init()��������    */
/*-------------------------------------------------*/
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
    if(htim->Instance==TIM1){	                   //��������ö�ʱ��1������if		
		__HAL_RCC_TIM1_CLK_ENABLE();               //ʹ��TIM1ʱ��
		HAL_NVIC_SetPriority(TIM1_UP_IRQn,1,3);    //�����ж����ȼ�����ռ���ȼ�1�������ȼ�3
		HAL_NVIC_EnableIRQ(TIM1_UP_IRQn);          //����ITM1�ж�   
	}
	if(htim->Instance==TIM2){	                   //��������ö�ʱ��2������if		
		__HAL_RCC_TIM2_CLK_ENABLE();               //ʹ��TIM2ʱ��
		HAL_NVIC_SetPriority(TIM2_IRQn,1,3);       //�����ж����ȼ�����ռ���ȼ�1�������ȼ�3
		HAL_NVIC_EnableIRQ(TIM2_IRQn);             //����ITM2�ж�   
	}
	if(htim->Instance==TIM3){	                   //��������ö�ʱ��3������if		
		__HAL_RCC_TIM3_CLK_ENABLE();               //ʹ��TIM3ʱ��
		HAL_NVIC_SetPriority(TIM3_IRQn,1,3);       //�����ж����ȼ�����ռ���ȼ�1�������ȼ�3
		HAL_NVIC_EnableIRQ(TIM3_IRQn);             //����ITM3�ж�   
	}
	if(htim->Instance==TIM4){	                   //��������ö�ʱ��4������if		
		__HAL_RCC_TIM4_CLK_ENABLE();               //ʹ��TIM4ʱ��
		HAL_NVIC_SetPriority(TIM4_IRQn,1,3);       //�����ж����ȼ�����ռ���ȼ�1�������ȼ�3
		HAL_NVIC_EnableIRQ(TIM4_IRQn);             //����ITM4�ж�   
	}
}
/*---------------------------------------------------*/
/*����������ʱ����ʱ���񣬻ص�����                   */
/*��  ����htim����ʱ�����                           */
/*����ֵ����                                         */
/*˵  �����˺����ᱻHAL_TIM_IRQHandler()�жϺ������� */
/*---------------------------------------------------*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance==TIM1)     //����Ƕ�ʱ��1
        LED_ATOGGLE;             //ȫ��LED����״̬�ı�
    if(htim->Instance==TIM2)     //����Ƕ�ʱ��2
        LED_ATOGGLE;             //ȫ��LED����״̬�ı�
	if(htim->Instance==TIM3)     //����Ƕ�ʱ��3
        LED_ATOGGLE;             //ȫ��LED����״̬�ı�
	if(htim->Instance==TIM4)     //����Ƕ�ʱ��4
        LED_ATOGGLE;             //ȫ��LED����״̬�ı�
}
