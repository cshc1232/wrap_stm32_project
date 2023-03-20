/*-------------------------------------------------*/
/*            ����˵������STM32ϵ�п�����          */
/*-------------------------------------------------*/
/*                                                 */
/*          ʵ�ָ���SPI�ӿڹ��ܵ�Դ�ļ�            */
/*                                                 */
/*-------------------------------------------------*/

#include "stm32f1xx_hal.h"    //������Ҫ��ͷ�ļ�
//#include "stm32f1xx_spi.h"
#include "spi.h"              //������Ҫ��ͷ�ļ�

SPI_HandleTypeDef SPI1_Handler;  //SPI1���

/*-------------------------------------------------*/
/*����������ʼ��SPI1�ӿ�                           */
/*��  ������                                       */
/*����ֵ����                                       */
/*-------------------------------------------------*/
void SPI1_Init(void)
{
    SPI1_Handler.Instance=SPI1;                                  //SPI1
    SPI1_Handler.Init.Mode=SPI_MODE_MASTER;                      //����SPI����ģʽ������Ϊ��ģʽ
    SPI1_Handler.Init.Direction=SPI_DIRECTION_2LINES;            //����SPI�������˫�������ģʽ:SPI����Ϊ˫��ģʽ
    SPI1_Handler.Init.DataSize=SPI_DATASIZE_8BIT;                //����SPI�����ݴ�С:SPI���ͽ���8λ֡�ṹ
    SPI1_Handler.Init.CLKPolarity=SPI_POLARITY_HIGH;             //����ͬ��ʱ�ӵĿ���״̬Ϊ�ߵ�ƽ
    SPI1_Handler.Init.CLKPhase=SPI_PHASE_2EDGE;                  //����ͬ��ʱ�ӵĵڶ��������أ��������½������ݱ�����
    SPI1_Handler.Init.NSS=SPI_NSS_SOFT;                          //NSS�ź���Ӳ����NSS�ܽţ����������ʹ��SSIλ������:�ڲ�NSS�ź���SSIλ����
    SPI1_Handler.Init.BaudRatePrescaler=SPI_BAUDRATEPRESCALER_2; //���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ2
    SPI1_Handler.Init.FirstBit=SPI_FIRSTBIT_MSB;                 //ָ�����ݴ����MSBλ����LSBλ��ʼ:���ݴ����MSBλ��ʼ
    SPI1_Handler.Init.TIMode=SPI_TIMODE_DISABLE;                 //�ر�TIģʽ
    SPI1_Handler.Init.CRCCalculation=SPI_CRCCALCULATION_DISABLE; //�ر�Ӳ��CRCУ��
    SPI1_Handler.Init.CRCPolynomial=7;                           //CRCֵ����Ķ���ʽ
    HAL_SPI_Init(&SPI1_Handler);                                 //��ʼ��
	__HAL_SPI_ENABLE(&SPI1_Handler);                             //ʹ��SPI1
	SPI1_ReadWriteByte(0xFF);
}

/*-------------------------------------------------*/
/*��������SPI�ӿڵĵײ��ʼ��                      */
/*��  ����hspi��SPI�ӿ����þ��                    */
/*����ֵ����                                       */
/*˵  �����˺����ᱻHAL_SPI_Init()�ص�����         */
/*-------------------------------------------------*/
void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
{
    GPIO_InitTypeDef GPIO_Initure;
    
	if(hspi->Instance==SPI1){     
		__HAL_RCC_GPIOA_CLK_ENABLE();                        //�����˿�Aʱ��  
		__HAL_RCC_SPI1_CLK_ENABLE();                         //����SPI1�ӿ�ʱ��
		
		GPIO_Initure.Pin=GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;   //����PA5 6 7
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;                   //����ģʽ
		GPIO_Initure.Pull=GPIO_PULLUP;                       //����
		GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;             //HIGHģʽ
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);                  //����	
	}
}
/*-------------------------------------------------*/
/*��������SPI�ӿڶ�д����                          */
/*��  ����TxData�����͵�����                       */
/*����ֵ����ȡ������                               */
/*-------------------------------------------------*/
uint8_t SPI1_ReadWriteByte(uint8_t TxData)
{
    uint8_t Rxdata;                                                    //����һ������������յ�������
    
	HAL_SPI_TransmitReceive(&SPI1_Handler,&TxData,&Rxdata,1, 1000);    //���Ͳ�����һ�ֽ�����     
 	return Rxdata;          		                                   //�����յ�������		
}
