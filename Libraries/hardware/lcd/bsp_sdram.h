/*
 * @Author: your name
 * @Date: 2020-06-29 19:23:36
 * @LastEditTime: 2020-08-13 16:57:49
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: \RT1052\Libraries\hardware\lcd\bsp_sdram.h
 */
#ifndef __BSP_SDRAM_H
#define	__BSP_SDRAM_H

#include "fsl_common.h"

/* SEMC_CLK_ROOTÆµÂÊ */
#define EXAMPLE_SEMC_CLK_FREQ         CLOCK_GetFreq(kCLOCK_SemcClk)

/*******************************************************************************
 * º¯ÊýÉùÃ÷
 ******************************************************************************/
int32_t SDRAM_Init(void);

#endif /* __BSP_SDRAM_H */
