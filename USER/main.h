/*-----------------------------------------------------*/
/*              ����˵������STM32ϵ�п�����            */
/*-----------------------------------------------------*/
/*                                                     */
/*                 �������á���Ϣͷ�ļ�                */
/*                                                     */
/*-----------------------------------------------------*/

#ifndef __MAIN_H
#define __MAIN_H

//--------------------------------------------------------------//
//--------------���ظ��¹̼� Xmodem Э�� �������---------------//
//--------------------------------------------------------------//
#define XMODEM_PACK_SIZE       133                                        //Xmodem Э�� һ��������  �������ݵĴ�С 
#define XMODEM_PACKDATA_SIZE   128                                        //Xmodem Э�� һ��������  �û����ݵĴ�С
#define XMODEM_SHO             0x01                                       //Xmodem Э�� SHOֵ   ����ͷ
#define XMODEM_EOT             0x04                                       //Xmodem Э�� EOTֵ   ���ͽ���
#define XMODEM_ACK             0x06                                       //Xmodem Э�� ACKֵ   Ӧ��
#define XMODEM_NAK             0x15                                       //Xmodem Э�� ACKֵ   ��Ӧ��
#define XMODEM_CAN             0x18                                       //Xmodem Э�� CANֵ   ֹͣ����

//---------------------------------------------------------------//
//---------------BootLoader��Ӧ��A�� Flash����-------------------//
//---------------------------------------------------------------//
#define FLASH_BASE_ADDR        0x08000000 	                                                   //STM32 FLASH����ʼ��ַ
#define FLASH_SECTO_NUM        64                                                              //STM32 FLASH����������
#define FLASH_SECTOR_SIZE      1024                                                            //STM32 FLASH������С
#define FLASH_BOOT_SECTO_NUM   20                                                              //BootLoaderռ�������ĸ���
#define FLASH_A_SECTO_NUM      FLASH_SECTO_NUM - FLASH_BOOT_SECTO_NUM                          //Ӧ�ó���A��ռ�������ĸ���
#define FLASH_A_ADDR		   FLASH_BASE_ADDR + FLASH_BOOT_SECTO_NUM * FLASH_SECTOR_SIZE      //Ӧ�ó���A����ʼλ��
#define FLASH_A_START_SECTOR  (FLASH_A_ADDR - FLASH_BASE_ADDR)/FLASH_SECTOR_SIZE               //Ӧ�ó���A����ʼ����

//---------------------------------------------------------------//
//------------------������Ϣ�ֽڣ���ʾ����-----------------------//
//---------------------------------------------------------------//
#define BOOT_STA_O             0x5AA5C33C                                //��ʾ��ҪOTA����Ӧ�ó���
#define BOOT_STANDBY_KEY       0x2CC2                                    //��ʾ��Ҫ����͹���,��������

//---------------------------------------------------------------//
//-------------------------�¼�������־����----------------------//
//---------------------------------------------------------------//
#define A_XMODEM        0x00000001                                      //A�����أ�Xmodem���¼�
#define ALIYUN_CER      0x00000002                                      //������Ѷ����Ԫ��֤���¼�
#define OTA_MODEM       0x00000004                                      //A�����أ�OTA���¼�

/*---------------------------------------------------------------*/
/*-----------EEPROM�ڱ������Ѷ��֤����Ϣ��Ч����----------------*/
/*---------------------------------------------------------------*/
#define VALID_ALICER_DATA      0xDD                                            //��ʾ��Ԫ��+�̼��汾��Ч
#define PRODUCTKEY_LEN         10                                              //��Ԫ�� ProductKey     �ַ�������        
#define DEVICENAME_LEN         32                                              //��Ԫ�� DeviceName     �ַ�������        
#define DEVICESECRET_LEN       24                                              //��Ԫ�� DeviceSecret   �ַ�������                
#define VERSION_LEN            23                                              //A��Ӧ�ó���̼��汾���ַ�������

/*---------------------------------------------------------------*/
/*--------------EEPROM�ڱ�����Ѷ��֤����Ϣ�Ľṹ��---------------*/
/*---------------------------------------------------------------*/
typedef struct{
	uint8_t  valid_cer;                                                         //������Ч��־���� ������� VALID_CER_DATA ˵����Ϣ��Ч �����ڵĻ� ��Ҫ��������
	uint8_t  ProductKeyBuff[PRODUCTKEY_LEN+1];                                  //����ProductKey�Ļ�����
	uint8_t  DeviceNameBuff[DEVICENAME_LEN+1];                                  //����DeviceName�Ļ�����
	uint8_t  DeviceSecretBuff[DEVICESECRET_LEN+1];                              //����DeviceSecret�Ļ�����
	uint8_t  Version_ABuff[VERSION_LEN+1];                                      //����Ӧ��A������̼��汾�Ļ�����
	uint32_t OTA_firelen;                                                       //OTA�̼���С
	uint32_t OTA_flag;                                                          //�Ƿ���ҪOTA�ı�ʶ
}AliyunInfo_CB;   
#define ALIINFO_STRUCT_LEN        sizeof(AliyunInfo_CB)                         //EEPROM�ڱ�����Ѷ��֤����Ϣ�Ľṹ�� ���� 

//---------------------------------------------------------------//
//----------------�ṹ�壬����/OTA���¹̼�ʱ�ı���---------------//
//---------------------------------------------------------------//
typedef struct{   
  uint8_t     UpdateBuff[FLASH_SECTOR_SIZE];      //����Xmodem/OTA����ʱ���̼����ݵĻ�����
	uint16_t    UpdateCRC16_res;                    //�������xmodemЭ��CRC16�Ľ��
	uint16_t    XmodemPackNO;                       //������յ�xmodem���ݰ����	

}Update_CB;      


//---------------------------------------------------------------//
//----------------�ṹ�壬w25q page���¹̼�ʱ�ı���---------------//
//---------------------------------------------------------------//
typedef struct{   
  uint8_t     UpdateBuff[256];      //����Xmodem/OTA����ʱ���̼����ݵĻ�����
	uint16_t    UpdateCRC16_res;                    //�������xmodemЭ��CRC16�Ľ��
	uint16_t    XmodemPackNO;                       //������յ�xmodem���ݰ����	
  uint16_t    PageNum;
}Update_WQ;      
//---------------------------------------------------------------//
//-------------�����ⲿ������������������Դ�ļ����ñ���----------//
//---------------------------------------------------------------//
extern Update_CB      Update;                      //�ⲿ��������������/OTA���¹̼�ʱ�ṹ�����
extern uint32_t BootEventFlag;                     //�ⲿ�������������������¼��ı�־����
extern AliyunInfo_CB   AliInfoCB;                  //�ⲿ����������EEPROM�ڱ����������Ϣ�ṹ����� 
extern Update_WQ    Update_Wq; 
#endif











