/***********************************************************************
*@Date: 2020-05-22 02:12:38
*@LastEditors: SOLA
*@LastEditTime: 2020-06-09 18:03:44
*@FilePath: \RT1052\Libraries\hardware\systick.h
***********************************************************************/

#ifndef __systick_h
#define __systick_h

#include "fsl_common.h"

void systick_delay_init(void);
void delay_us(uint32_t tick);
void delay_ms(uint32_t tick);

#endif
