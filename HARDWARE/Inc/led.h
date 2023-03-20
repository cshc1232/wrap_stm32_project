/*-------------------------------------------------*/
/*            ����˵������STM32ϵ�п�����          */
/*-------------------------------------------------*/
/*                                                 */
/*              ʵ��LED���ܵ�ͷ�ļ�                */
/*                                                 */
/*-------------------------------------------------*/

#ifndef __LED_H
#define __LED_H

/*--------------------------------------------------------------------------*/
/*                      ����LED��IO���� �� ʱ��ʹ��                         */
/*                        ���Ը�����Ҫ�޸ĺ�����                            */
/*--------------------------------------------------------------------------*/
#define LED1_GROUP             GPIOA                                               //��Ӧ��IO����
#define LED1_PIN               GPIO_PIN_11                                         //��Ӧ��IO

#define LED2_GROUP             GPIOA                                               //��Ӧ��IO����
#define LED2_PIN               GPIO_PIN_12                                         //��Ӧ��IO                                       
/*--------------------------------------------------------------------------*/

#define LED1_TOGGLE    HAL_GPIO_TogglePin(LED1_GROUP,  LED1_PIN)                   //��ӦIO��ƽ��ת��LED����״̬�ı�
#define LED2_TOGGLE    HAL_GPIO_TogglePin(LED2_GROUP,  LED2_PIN)                   //��ӦIO��ƽ��ת��LED����״̬�ı�

#define LED1_IN_STA    HAL_GPIO_ReadPin(LED1_GROUP,  LED1_PIN)                     //��ȡLED��ǰ��ƽ״̬
#define LED2_IN_STA    HAL_GPIO_ReadPin(LED2_GROUP,  LED2_PIN)                     //��ȡLED��ǰ��ƽ״̬

#define LED1_ON        HAL_GPIO_WritePin(LED1_GROUP, LED1_PIN, GPIO_PIN_RESET)     //���Ͷ�ӦIO������LED
#define LED1_OFF       HAL_GPIO_WritePin(LED1_GROUP, LED1_PIN, GPIO_PIN_SET)       //���߶�ӦIO��Ϩ��LED

#define LED2_ON        HAL_GPIO_WritePin(LED2_GROUP, LED2_PIN, GPIO_PIN_RESET)     //���Ͷ�ӦIO������LED
#define LED2_OFF       HAL_GPIO_WritePin(LED2_GROUP, LED2_PIN, GPIO_PIN_SET)       //���߶�ӦIO��Ϩ��LED

#define LED_AON       {LED1_ON;LED2_ON;}                                           //ȫ��LED����
#define LED_AOFF      {LED1_OFF;LED2_OFF;}                                         //ȫ��LEDϨ��
#define LED_ATOGGLE   {LED1_TOGGLE;LED2_TOGGLE;}                                   //ȫ��LED����״̬�ı�

void LED_Init(void);                                                               //������������ʼ��LED����

#endif
