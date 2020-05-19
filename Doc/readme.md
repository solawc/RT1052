<!--
 * @Author: sola
 * @Date: 2019-11-21 11:49:55
 * @FilePath: \RT1052\Doc\readme.md
 * @Drscription: 
 -->


任务要求：
1、开机启动EEPROM读P\I\D三个值的数据，地址分别保存在0x05,0x06,0x07
2、初始化OLED(LCDD代替)，并开始采集6通道的ADC的值，显示依次实时显示在OLED（LCD）上
3、ADC的采集使用PIT_CH0,以中断的方式定时5ms采集一次，采集到的数据保存在一个数组中，adc_collect[6]
4、使用串口，连接到电脑，通过山外的串口助手，显示6个通道的波形，保证OLED(LCD)上的数据跟波形差距不大
5、按键1按下后，保存数据到EEPROM上

系统要求：可以使用裸机或者RTOS，定时器不一定要用PIT，可以用普通定时器
