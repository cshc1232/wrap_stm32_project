/*-------------------------------------------------*/
/*            超子说物联网STM32系列开发板            */
/*-------------------------------------------------*/
/*                                                 */
/*            实现定时器功能的头文件                */
/*                                                 */
/*-------------------------------------------------*/

#ifndef _TIMER_H
#define _TIMER_H

extern TIM_HandleTypeDef htim1;                   //外部变量声明，定时器1句柄
extern TIM_HandleTypeDef htim2;                   //外部变量声明，定时器2句柄
extern TIM_HandleTypeDef htim3;                   //外部变量声明，定时器3句柄
extern TIM_HandleTypeDef htim4;                   //外部变量声明，定时器4句柄

void TIM1_Init(uint16_t, uint16_t, uint16_t);     //函数声明，定时器1初始化
void TIM2_Init(uint16_t, uint16_t);               //函数声明，定时器2初始化
void TIM3_Init(uint16_t, uint16_t);               //函数声明，定时器3初始化
void TIM4_Init(uint16_t, uint16_t);               //函数声明，定时器4初始化

#endif
