/*-------------------------------------------------*/
/*            超子说物联网STM32系列开发板          */
/*-------------------------------------------------*/
/*                                                 */
/*             实现定时器功能的源文件              */
/*                                                 */
/*-------------------------------------------------*/

#include "stm32f1xx_hal.h"  //包含需要的头文件
#include "timer.h"          //包含需要的头文件
#include "led.h"            //包含需要的头文件

TIM_HandleTypeDef htim1;    //定时器1句柄 
TIM_HandleTypeDef htim2;    //定时器2句柄 
TIM_HandleTypeDef htim3;    //定时器3句柄 
TIM_HandleTypeDef htim4;    //定时器4句柄 

/*-------------------------------------------------*/
/*函数名：定时器1初始化                            */
/*参  数：arr：自动重装值                          */
/*参  数：psc：时钟预分频数                        */
/*参  数：Repe：重复计数器值                       */
/*返回值：无                                       */
/*-------------------------------------------------*/
void TIM1_Init(uint16_t arr, uint16_t psc, uint16_t Repe)
{
	htim1.Instance = TIM1;                                         //设置定时器1
	htim1.Init.Prescaler = psc-1;                                  //设置定时器预分频数
	htim1.Init.Period = arr-1;                                     //设置自动重装载值
	htim1.Init.CounterMode = TIM_COUNTERMODE_UP;                   //向上计数模式
	htim1.Init.RepetitionCounter = Repe;                           //重复计数器值为Repe
	htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE; //不使用预装载
	HAL_TIM_Base_Init(&htim1);                                     //设置
	__HAL_TIM_CLEAR_IT(&htim1, TIM_IT_UPDATE);                     //清除中断标志
	HAL_TIM_Base_Start_IT(&htim1);                                 //使能定时器1和定时器1更新中断：TIM_IT_UPDATE
}
/*-------------------------------------------------*/
/*函数名：定时器2初始化                            */
/*参  数：arr：自动重装值                          */
/*参  数：psc：时钟预分频数                        */
/*参  数：Repe：重复计数器值                       */
/*返回值：无                                       */
/*-------------------------------------------------*/
void TIM2_Init(uint16_t arr, uint16_t psc)
{
	htim2.Instance = TIM2;                                         //设置定时器2
	htim2.Init.Prescaler = psc-1;                                  //设置定时器预分频数
	htim2.Init.Period = arr-1;                                     //设置自动重装载值
	htim2.Init.CounterMode = TIM_COUNTERMODE_UP;                   //向上计数模式
	htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE; //不使用预装载
	HAL_TIM_Base_Init(&htim2);                                     //设置
	__HAL_TIM_CLEAR_IT(&htim2, TIM_IT_UPDATE);                     //清除中断标志
	HAL_TIM_Base_Start_IT(&htim2);                                 //使能定时器2和定时器2更新中断：TIM_IT_UPDATE
}
/*-------------------------------------------------*/
/*函数名：定时器3初始化                            */
/*参  数：arr：自动重装值                          */
/*参  数：psc：时钟预分频数                        */
/*参  数：Repe：重复计数器值                       */
/*返回值：无                                       */
/*-------------------------------------------------*/
void TIM3_Init(uint16_t arr, uint16_t psc)
{
	htim3.Instance = TIM3;                                         //设置定时器3
	htim3.Init.Prescaler = psc-1;                                  //设置定时器预分频数
	htim3.Init.Period = arr-1;                                     //设置自动重装载值
	htim3.Init.CounterMode = TIM_COUNTERMODE_UP;                   //向上计数模式
	htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE; //不使用预装载
	HAL_TIM_Base_Init(&htim3);                                     //设置
	__HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE);                     //清除中断标志
	HAL_TIM_Base_Start_IT(&htim3);                                 //使能定时器3和定时器3更新中断：TIM_IT_UPDATE
}
/*-------------------------------------------------*/
/*函数名：定时器4初始化                            */
/*参  数：arr：自动重装值                          */
/*参  数：psc：时钟预分频数                        */
/*参  数：Repe：重复计数器值                       */
/*返回值：无                                       */
/*-------------------------------------------------*/
void TIM4_Init(uint16_t arr, uint16_t psc)
{
	htim4.Instance = TIM4;                                         //设置定时器4
	htim4.Init.Prescaler = psc-1;                                  //设置定时器预分频数
	htim4.Init.Period = arr-1;                                     //设置自动重装载值
	htim4.Init.CounterMode = TIM_COUNTERMODE_UP;                   //向上计数模式
	htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE; //不使用预装载
	HAL_TIM_Base_Init(&htim4);                                     //设置
	__HAL_TIM_CLEAR_IT(&htim4, TIM_IT_UPDATE);                     //清除中断标志
	HAL_TIM_Base_Start_IT(&htim4);                                 //使能定时器4和定时器4更新中断：TIM_IT_UPDATE
}
/*-------------------------------------------------*/
/*函数名：定时器底层驱动，开启时钟，设置中断优先级 */
/*参  数：htim：定时器句柄                         */
/*返回值：无                                       */
/*说  明：此函数会被HAL_TIM_Base_Init()函数调用    */
/*-------------------------------------------------*/
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
    if(htim->Instance==TIM1){	                   //如果是配置定时器1，进入if		
		__HAL_RCC_TIM1_CLK_ENABLE();               //使能TIM1时钟
		HAL_NVIC_SetPriority(TIM1_UP_IRQn,1,3);    //设置中断优先级，抢占优先级1，子优先级3
		HAL_NVIC_EnableIRQ(TIM1_UP_IRQn);          //开启ITM1中断   
	}
	if(htim->Instance==TIM2){	                   //如果是配置定时器2，进入if		
		__HAL_RCC_TIM2_CLK_ENABLE();               //使能TIM2时钟
		HAL_NVIC_SetPriority(TIM2_IRQn,1,3);       //设置中断优先级，抢占优先级1，子优先级3
		HAL_NVIC_EnableIRQ(TIM2_IRQn);             //开启ITM2中断   
	}
	if(htim->Instance==TIM3){	                   //如果是配置定时器3，进入if		
		__HAL_RCC_TIM3_CLK_ENABLE();               //使能TIM3时钟
		HAL_NVIC_SetPriority(TIM3_IRQn,1,3);       //设置中断优先级，抢占优先级1，子优先级3
		HAL_NVIC_EnableIRQ(TIM3_IRQn);             //开启ITM3中断   
	}
	if(htim->Instance==TIM4){	                   //如果是配置定时器4，进入if		
		__HAL_RCC_TIM4_CLK_ENABLE();               //使能TIM4时钟
		HAL_NVIC_SetPriority(TIM4_IRQn,1,3);       //设置中断优先级，抢占优先级1，子优先级3
		HAL_NVIC_EnableIRQ(TIM4_IRQn);             //开启ITM4中断   
	}
}
/*---------------------------------------------------*/
/*函数名：定时器定时任务，回调函数                   */
/*参  数：htim：定时器句柄                           */
/*返回值：无                                         */
/*说  明：此函数会被HAL_TIM_IRQHandler()中断函数调用 */
/*---------------------------------------------------*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance==TIM1)     //如果是定时器1
        LED_ATOGGLE;             //全部LED亮灭状态改变
    if(htim->Instance==TIM2)     //如果是定时器2
        LED_ATOGGLE;             //全部LED亮灭状态改变
	if(htim->Instance==TIM3)     //如果是定时器3
        LED_ATOGGLE;             //全部LED亮灭状态改变
	if(htim->Instance==TIM4)     //如果是定时器4
        LED_ATOGGLE;             //全部LED亮灭状态改变
}
