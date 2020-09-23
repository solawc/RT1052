/***********************************************************************
*@Date: 2020-05-17 01:12:50
*@LastEditors: SOLA
*@LastEditTime: 2020-06-02 00:10:36
*@FilePath: \RT1052\Libraries\hardware\uart.c
***********************************************************************/
#include "uart.h"

#define HEAD_CMD    0X0A
#define TAIL_CMD    0XA0
/***********************************************************************
*@Date: 2020-05-17 01:16:13
*@Function: lpuart_send_byte
*@Input: 
*@Return: 
*@Drscription: 
***********************************************************************/
void lpuart_send_byte(LPUART_Type *base, uint8_t data)
{
    LPUART_WriteByte(base,data);
    
    while (!(base->STAT & LPUART_STAT_TDRE_MASK));
}

void send_string(uint8_t *data)
{   
    int k=0;
    do
    {
        lpuart_send_byte(LPUART1,data[k]);
        k++;
    }while(data[k++]=='\0');
}

int fputc(int ch,FILE *f)
{
    lpuart_send_byte(LPUART1,(uint8_t )ch);
    
    return ch;
}

void send_conputer(uint8_t *data)
{
    lpuart_send_byte(LPUART1,HEAD_CMD);
    lpuart_send_byte(LPUART1,TAIL_CMD);
    send_string(data);
    lpuart_send_byte(LPUART1,TAIL_CMD);
    lpuart_send_byte(LPUART1,HEAD_CMD);
}

