/*-------------------------------------------------*/
/*            超子说物联网STM32系列开发板          */
/*-------------------------------------------------*/
/*                                                 */
/*          使用SysTick实现延时功能的源文件        */
/*                                                 */
/*-------------------------------------------------*/

#include "stm32f1xx_hal.h"  //包含需要的头文件
#include "delay.h"          //包含需要的头文件

extern __IO uint32_t uwTick;

/*-------------------------------------------------*/
/*函数名：初始化延迟计数器 配置时钟函数            */
/*参  数：无                                       */
/*返回值：无                                       */
/*-------------------------------------------------*/
void Delay_CLock_Init(void)
{  
	RCC_OscInitTypeDef RCC_OscInitStruct;
    RCC_ClkInitTypeDef RCC_ClkInitStruct;
	
	SysTick->CTRL &=~ (SysTick_CTRL_TICKINT_Msk|SysTick_CTRL_ENABLE_Msk);               		 //HAL_Init函数开启了SysTick和中断 在此关闭SysTick和关闭中断   	
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK_DIV8);                           		 //设置SysTick频率为HCLK 8分频++++
	
	RCC_OscInitStruct.OscillatorType      = RCC_OSCILLATORTYPE_HSE;                              //使用外部高速主晶振8M
	RCC_OscInitStruct.HSEState            = RCC_HSE_ON;                                          //开外部高速晶振
	RCC_OscInitStruct.PLL.PLLState        = RCC_PLL_ON;                                          //开启PLL
	RCC_OscInitStruct.PLL.PLLSource       = RCC_PLLSOURCE_HSE;                                   //PLL时钟源选择HSE 外部晶振
	RCC_OscInitStruct.PLL.PLLMUL          = RCC_PLL_MUL9;                                        //9倍频 8*9=72
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)                               			 //配置，如果失败进入if，重启
		NVIC_SystemReset();                         
	
	RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;                                    //SYSCLK时钟源选择PLL   8*12/3=32MHz
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;                                           //AHB  1分频  72/1=72MHz
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;                                            //APB1 2分频  72/2=36MHz
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;                                            //APB2 1分频  72/1=72MHz
	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)                      //配置，如果失败进入if，重启
		NVIC_SystemReset();                                                                      //重启
}
/*-------------------------------------------------*/
/*函数名：延迟微秒函数                             */
/*参  数：us：延时多少微秒                         */
/*返回值：无                                       */
/*-------------------------------------------------*/
void Delay_Us(uint16_t us)
{		
	SysTick->LOAD=us*US_UNIT;                             //计数器的重载值，要注意SysTick是倒数计数的
	SysTick->VAL=0x00;                                    //清空当前计数器的值
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;              //使能SysTick计数器，重载值加载到计数器中，开始倒数计数
	while(!(SysTick->CTRL&SysTick_CTRL_COUNTFLAG_Msk));   //等待时间到达
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;              //关闭计数器 
}
/*-------------------------------------------------*/
/*函数名：延迟毫秒函数                             */
/*参  数：ms：延时多少毫秒                         */
/*返回值：无                                       */
/*-------------------------------------------------*/
void Delay_Ms(uint16_t ms)
{
	//我们首先注意一个问题SysTick时钟计数器是24位的，单次延时不能超过最大值MS_UNIT
	//所有我们以MS_UNIT为界限，小于MS_UNIT的延时一次计数就行，大于MS_UNIT的多次计数		
	/*-----------if判断，小于MS_UNIT延时的情况，执行if分支------------------*/
	if(ms<=MS_UNIT){                                   
		SysTick->LOAD=ms*US_UNIT*1000;                           //计数器的重载值，要注意SysTick是倒数计数的        
		SysTick->VAL=0x00;                                       //清空当前计数器的值
		SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;                  //使能SysTick计数器，重载值加载到计数器中，开始倒数
		while(!(SysTick->CTRL&SysTick_CTRL_COUNTFLAG_Msk));      //等待时间到达
		SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;                 //关闭计数器 	
	}  
	/*--------------大于MS_UNIT延时的情况，执行else分支-------------------*/
	else{ 
		while(ms/MS_UNIT){                                       //先取整数部分，每次延时MS_UNIT
			SysTick->LOAD=MS_UNIT*US_UNIT*1000;                  //计数器的重载值，要注意SysTick是倒数计数的        
			SysTick->VAL=0x00;                                   //清空当前计数器的值
			SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;             //使能SysTick计数器，重载值加载到计数器中，开始倒数
			while(!(SysTick->CTRL&SysTick_CTRL_COUNTFLAG_Msk));  //等待时间到达
			SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;             //关闭计数器 
			ms-=MS_UNIT;                                         //重新计算剩余延时值
		} 	
		if(ms%MS_UNIT){                                          //如果还有余数，再计算余数
			SysTick->LOAD=(ms%MS_UNIT)*US_UNIT*1000;             //计数器的重载值，要注意SysTick是倒数计数的  
			SysTick->VAL =0x00;                                  //清空当前计数器的值
			SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;             //使能SysTick计数器，重载值加载到计数器中，开始倒数  
			while(!(SysTick->CTRL&SysTick_CTRL_COUNTFLAG_Msk));  //等待时间到达
			SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;             //关闭计数器
		}
	}
} 
/*-------------------------------------------------*/
/*函数名：重定义HAL_GetTick函数                    */
/*参  数：无                                       */
/*返回值：延时毫秒值                               */
/*-------------------------------------------------*/
uint32_t HAL_GetTick(void)
{
	Delay_Ms(1);       //延时1ms
	return ++uwTick;   //返回全局延时值
}
/*-------------------------------------------------*/
/*函数名：重定义HAL_InitTick函数                   */
/*参  数：无                                       */
/*返回值：HAL_OK                                   */
/*-------------------------------------------------*/
HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority)
{
	return HAL_OK;    //什么也不用做，直接返回HAL_OK
}
