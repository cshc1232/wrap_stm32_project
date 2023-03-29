/*-------------------------------------------------*/
/*           超子说物联网STM32系列开发板           */
/*-------------------------------------------------*/
/*                                                 */
/*          实现各个SPI接口功能的头文件            */
/*                                                 */
/*-------------------------------------------------*/

#ifndef __SPI_H
#define __SPI_H

extern SPI_HandleTypeDef SPI1_Handler;  //SPI1句柄

void SPI1_Init(void);                          //函数声明，初始化SPI1接口

void SPI1_24l01(void);

uint8_t SPI1_ReadWriteByte(uint8_t);           //函数声明，SPI接口读写数据
void SPI1_SetSpeed(uint8_t SpeedSet); //设置SPI速度 
#endif


