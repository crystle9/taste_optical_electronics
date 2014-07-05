## 舌尖上的光电
___状态：程序框架还要做重大调整，先不要使用___

### 功能模块
1. 速度测量与控制（电机）：motor.c
- 角度测量与控制（舵机）：rudder.c

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
 - Di   数字I/O   漏开   I/O   P2
 - D7	数字I/O	  漏开	 EX6   P3.6
- 激光头1
 - AD	模拟输入  x	 AIN1  P1.1
 - IO	数字I/O	  漏开	 CEX2  P0.6
- 激光头2
 - AD	模拟输入  x	 AIN2  P1.2
 - IO	数字I/O	  漏开	 T1    P1.4
- c8051F020
 - P0.7 CEX3	  推挽   I/O   P1.7
 - P1.7 数字I/O	  漏开   CEX3  P0.7
 
#### 与驱动芯片
1. 电机
 - pin1  OUT1
 - pin2  OUT2
- 舵机
 - VCC   VADJ(6V?)
 - GND	 GND
 - SIG	 DJ1
 
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
1. PCA0溢出中断
- CEX2电平改变触发捕捉
- 计数器0溢出中断
- CEX3电平改变触发捕捉


#### 仅利用中断标置

### 基本思路

	while 1
	  while 弯道模式
	    slow down
	  解除弯道预警
	  while 直道模式
	    if 前方有弯道
	      低速
	    else
	      speed up

#### 电机控制
使用不同的占空比，获得不同的速度。至少能在低速和高速间切换

#### 舵机控制
根据反射式红外感应器的输出状态确定左、右还是不动；根据碰撞时间间隔确定改变的幅度
。
### to_do_list
1. 电机控制
- 舵机控制
- 中断系统设计
- 隧道长度、树木棵数等的测量

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


