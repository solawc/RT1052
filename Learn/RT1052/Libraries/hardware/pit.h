#ifndef __pit_h 
#define __pit_h
 
#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "fsl_gpio.h"
#include "fsl_pit.h"

#define PIT_SOURCE_CLOCK        CLOCK_GetFreq(kCLOCK_OscClk)
#define PIT_Ch_0				0U
#define PIT_Ch_1				1U

#define TIME_0                  1000000U   
#define TIME_1                  500000U   
void Pit_init(uint8_t PIT_CHn,uint32_t reload);
#endif /* __pit_h */
