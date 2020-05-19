#ifndef __usb_c
#define __usb_c


#include "fsl_common.h"

/*PDIUSBDI CMD*/
#define CMD_SET_MODE											0XF3
#define CMD_READ_ID												0XFD
#define CMD_READ_Interrupt_register				0XF4
#define CMD_READ_buffer										0xf0
#define CMD_Write_buffer									0xf0



/* USB 请求结构体 */
typedef struct
{
	uint8_t bmRequestType;
	uint8_t bRequest;
	uint16_t wValue;
	uint16_t wIndex;
	uint16_t wLength;
	
}USB_request_t;




#endif 
