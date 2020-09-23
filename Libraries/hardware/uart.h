/***********************************************************************
*@Date: 2020-05-17 01:12:56
*@LastEditors: SOLA
*@LastEditTime: 2020-05-17 01:19:41
*@FilePath: \RT1052_RT_Thread\Libraries\hardware\uart.h
***********************************************************************/
#ifndef __uart_h
#define __uart_h

#include "main.h"
#include "fsl_lpuart.h"
#include "stdio.h"

void lpuart_send_byte(LPUART_Type *base, uint8_t data);
void send_string(uint8_t *data);
void send_conputer(uint8_t *data);
#endif
