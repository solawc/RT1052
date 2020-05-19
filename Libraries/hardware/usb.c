#include "usb.h"



void write_cmd(uint8_t cmd)
{
}

void write_data(uint8_t data)
{
}

void connect(void)
{
	write_cmd(CMD_SET_MODE);
	write_data(0X10);
	write_data(0X40);
	delay_ms(1000);
}

void dis_connect(void)
{
	write_cmd(CMD_SET_MODE);
	write_data(0X00);
	write_data(0X40);
	delay_ms(1000);
}

