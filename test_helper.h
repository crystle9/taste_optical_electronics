#ifndef __TEST_HELPER_H__
#define __TEST_HELPER_H__

#define PUT_LINE(X,Y)				\
  LED_P6x8Str(0, current_line, X);\
  _put_line(Y)
#define UPDATE_VALUE(X,Y)\
  LED_PrintShort(90, X, Y)

extern unsigned char current_line;

void Test_Helper_Init(void);
void _put_line(int digit);
void general_delay(void);

#endif

