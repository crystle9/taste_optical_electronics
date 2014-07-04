/******************************************************************************

          ��Ȩ���� (C), 2011-2012, ������ӿƼ�(http://xydz123.taobao.com/)

 ******************************************************************************
  �� �� ��   : oled.h
  �� �� ��   : v1.0
  ��    ��   : Guokaiyi
  ��������   : 2012-11-12
  ����޸�   : 
  ��������   : oled.c ��ͷ�ļ�
  �޸���ʷ   :
  1.��    ��   : 2012-11-12
    ��    ��   : Guokaiyi
    �޸�����   : �����ļ�

******************************************************************************/
#ifndef __OLED_H__
#define __OLED_H__

/*----------------------------------------------------------------------------*
 * ����ͷ�ļ�                                                                 *
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
 * �궨��                                                                     *
 *----------------------------------------------------------------------------*/
#define LED_IMAGE_WHITE       1
#define LED_IMAGE_BLACK       0

#define LED_MAX_ROW_NUM      64
#define LED_MAX_COLUMN_NUM  128

/*----------------------------------------------------------------------------*
 * ȫ�ֱ���                                                                   *
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
 * �ڲ�����ԭ��                                                               *
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
 * �ⲿ����ԭ��                                                               *
 *----------------------------------------------------------------------------*/
 void LED_Init(void);
 void LED_SetPos(unsigned char ucIdxX, unsigned char ucIdxY); 
 void LED_P6x8Char(unsigned char ucIdxX,unsigned char ucIdxY,unsigned char ucData);
 void LED_P6x8Str(unsigned char ucIdxX,unsigned char ucIdxY,unsigned char ucDataStr[]);
 void LED_P8x16Str(unsigned char ucIdxX,unsigned char ucIdxY,unsigned char ucDataStr[]);
 void LED_P14x16Str(unsigned char ucIdxX,unsigned char ucIdxY,unsigned char ucDataStr[]);
 void LED_PXx16MixStr(unsigned char ucIdxX, unsigned char ucIdxY, unsigned char ucDataStr[]);
 void LED_Fill(unsigned char ucData);
 void LED_PrintChar(unsigned char ucIdxX, unsigned char ucIdxY, char cData);
 void LED_PrintShort(unsigned char ucIdxX, unsigned char ucIdxY, int sData);
 void LED_PrintImage(unsigned char *pucTable, unsigned int usRowNum, unsigned int usColumnNum);

#endif

