## 舌尖上的光电
___状态：在做ADC，遇到问题。PWM可以边做___

### 功能模块
1. 电机控制：motor.c
- 舵机控制：rudder.c
- 传感器：sensors.c
- 显示：oled.c
- 调试：test_helper.c
- 晶振：osi.c

### 硬件连接

#### 与c8051F020
1. OLED
 - D0   数字I/O   推挽   CLK   P0.0
 - D1	数字I/O	  推挽	 MOSI  P0.2
 - RST	数字I/O	  推挽	 I/O   P1.5
 - DC	数字I/O	  推挽	 I/O   P1.6
- 驱动芯片
 - IN1  数字I/O   推挽   CEX0  P0.4
 - DJ1  数字I/O   推挽   CEX1  P0.5
- 欧姆龙
 - 黑   数字I/O   漏开   T0    P1.3
- 八路循迹、防撞与起停
 - D3-6 数字I/O   漏开   I/O   P2.[0:3]
 - D7	数字I/O	  漏开	 EX7   P3.7
- 激光头0
 - AD	模拟输入  x	 AIN1  P1.0
- 激光头1
 - IO	数字I/O	  漏开	 T2EX  P1.4
 - IO	数字I/O	  漏开	 EX6   P3.6
- 激光头2
 - IO	数字I/O	  漏开	 T1    P1.2

#### 与驱动芯片
1. 电机
 - pin1  OUT1
 - pin2  OUT2
- 舵机
 - VCC   VIN(8.4V)
 - GND	 GND
 - SIG	 DJ3
 
#### 电源、地与悬空
1. 驱动芯片
 - VIN   8.4V
- c8051F020
 - VIN   5V
- 欧姆龙
 - VCC   5V
- 八路循迹、防撞与起停
 - VCC   5V
- 激光头1
 - VCC   5V
- 激光头2
 - VCC   5V
- OLED
 - VCC   3.3V
 - CS	 悬空

### 中断系统

#### 开中断
- 外部中断6：LD1上升沿：进入隧道标志
- 外部中断7：前方有障碍物，停止运行

### 基本思路

#### 动力系统
1. 舵机：PCA0_CEX0，PWM（50Hz）
-  直流电机：PCA0_CEX1，PWM

#### 感应系统
1. LD0：AIN0
-  红外：P2
-  LD1：外部中断6（上升沿，定时/计数器2启动计数），T2EX（下降沿，停止计数并存储隧道长度）
-  LD2：定时/计数器1，测量树木棵数
-  OMRON：T2，定时/计数器2的外部时钟源

#### 测量系统

### 资料汇总

#### 器件淘宝链接
1. [车模](http://item.taobao.com/item.htm?spm=a1z09.2.9.32.xyVWia&id=37831038260&_u=4ocfa01f1f9)
- [电池](http://item.taobao.com/item.htm?spm=a1z09.2.9.42.xyVWia&id=19199306231&_u=4ocfa011478)
- [驱动芯片](http://item.taobao.com/item.htm?spm=a1z09.2.9.54.xyVWia&id=18861889688&_u=4ocfa0144ec)
- [八路循迹模块](http://item.taobao.com/item.htm?spm=a230r.1.14.11.DwZlrA&id=21707631841&ns=1&_u=3g3nju4062#detail)
- [欧姆龙](http://item.taobao.com/item.htm?spm=a230r.1.0.0.v1lzQp&id=14911559769)
- [激光头](http://item.taobao.com/item.htm?spm=a1z0k.6846101.1130973605.d4915205.3kuB8E&id=14898953905&_u=4ocfa01d25c)
- [OLED显示屏](http://item.taobao.com/item.htm?spm=a1z0k.6846101.1130973605.d4915205.3kuB8E&id=17345035506&_u=4ocfa01fcf2)

#### 其它
1. [百度网盘](http://pan.baidu.com/s/1hqDYqMg)
- [V型前支架安装视频](http://v.youku.com/v_show/id_XNzI3Nzc4NTA0.html)
- [540后支架安装视频](http://v.youku.com/v_show/id_XNzI3OTI0MTM2.html)


