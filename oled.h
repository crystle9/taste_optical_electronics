/******************************************************************************

          版权所有 (C), 2011-2012, 信意电子科技(http://xydz123.taobao.com/)

 ******************************************************************************
  文 件 名   : oled.h
  版 本 号   : v1.0
  作    者   : Guokaiyi
  生成日期   : 2012-11-12
  最近修改   : 
  功能描述   : oled.c 的头文件
  修改历史   :
  1.日    期   : 2012-11-12
    作    者   : Guokaiyi
    修改内容   : 创建文件

******************************************************************************/
#ifndef __OLED_H__
#define __OLED_H__

/*----------------------------------------------------------------------------*
 * 包含头文件                                                                 *
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
 * 宏定义                                                                     *
 *----------------------------------------------------------------------------*/
#define LED_IMAGE_WHITE       1
#define LED_IMAGE_BLACK       0

#define LED_MAX_ROW_NUM      64
#define LED_MAX_COLUMN_NUM  128

/*----------------------------------------------------------------------------*
 * 全局变量                                                                   *
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
 * 内部函数原型                                                               *
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
 * 外部函数原型                                                               *
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

