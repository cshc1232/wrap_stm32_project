/*-------------------------------------------------*/
/*            ����˵������STM32ϵ�п�����            */
/*-------------------------------------------------*/
/*                                                 */
/*            ʵ�ֶ�ʱ�����ܵ�ͷ�ļ�                */
/*                                                 */
/*-------------------------------------------------*/

#ifndef _TIMER_H
#define _TIMER_H

extern TIM_HandleTypeDef htim1;                   //�ⲿ������������ʱ��1���
extern TIM_HandleTypeDef htim2;                   //�ⲿ������������ʱ��2���
extern TIM_HandleTypeDef htim3;                   //�ⲿ������������ʱ��3���
extern TIM_HandleTypeDef htim4;                   //�ⲿ������������ʱ��4���

void TIM1_Init(uint16_t, uint16_t, uint16_t);     //������������ʱ��1��ʼ��
void TIM2_Init(uint16_t, uint16_t);               //������������ʱ��2��ʼ��
void TIM3_Init(uint16_t, uint16_t);               //������������ʱ��3��ʼ��
void TIM4_Init(uint16_t, uint16_t);               //������������ʱ��4��ʼ��

#endif
