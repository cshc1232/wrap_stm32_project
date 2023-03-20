/*-------------------------------------------------*/
/*            ����˵������STM32ϵ�п�����              */
/*-------------------------------------------------*/
/*                                                 */
/*              ʵ��BOOT���ܵ�ͷ�ļ�               */
/*                                                 */
/*-------------------------------------------------*/

#ifndef __BOOT_H
#define __BOOT_H

void BootLoader_Branch(void);                 //����������BootLoader��֧����
uint8_t BootLoader_Enter(uint8_t);            //�����������Ƿ����BootLoader
void BootLoader_Info(void);                   //����������BootLoader�����Ϣ 
void BootLoader_Event(uint8_t *, uint16_t);   //��������������BootLoader�¼�
void BootLoader_Clear(void);                  //����������BootLoader��ת��Ӧ����ǰ��������
void Printf_AliCer(void);                     //�������������������Ѷ��֤����Ϣ
uint8_t BootLoader_AliCerInspect(uint8_t *);  //���������������յ�����Ѷ��֤����Ϣ
void ActiveEvent(void);                       //���������������¼�

#endif


