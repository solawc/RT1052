/***********************************************************************
*@Author: sola
*@Date: 2019-11-20 20:57:48
*@FilePath: \RT1052\Libraries\hardware\spi.c
*@Drscription: 
***********************************************************************/
#include "spi.h"


#define SPI_PAD_CONFIG_DATA            (IOMUXC_SW_PAD_CTL_PAD_SRE(1) | \
                                        IOMUXC_SW_PAD_CTL_PAD_DSE(6) | \
                                        IOMUXC_SW_PAD_CTL_PAD_SPEED(3) | \
                                        IOMUXC_SW_PAD_CTL_PAD_ODE(0) | \
                                        IOMUXC_SW_PAD_CTL_PAD_PKE(1) | \
                                        IOMUXC_SW_PAD_CTL_PAD_PUE(0) | \
                                        IOMUXC_SW_PAD_CTL_PAD_PUS(0) | \
                                        IOMUXC_SW_PAD_CTL_PAD_HYS(0))


/***********************************************************************
*@Function: 
*@Input: 
*@Return: none
*@Author: sola
*@Date: 2019-11-20 21:03:03
*@Drscription: 
***********************************************************************/
bool Spi_Init(void)
{
    flexspi_config_t config;
    const clock_usb_pll_config_t g_ccmConfigUsbPll = {.loopDivider = 0U};

    IOMUXC_SetPinMux(QSPI_IO0_MUX,1U);
    IOMUXC_SetPinMux(QSPI_IO1_MUX,1U);
    IOMUXC_SetPinMux(QSPI_IO2_MUX,1U);
    IOMUXC_SetPinMux(QSPI_IO3_MUX,1U);
    IOMUXC_SetPinMux(QSPI_SCK_MUX,1U);
    IOMUXC_SetPinMux(QSPI_CE_MUX,1U);

    IOMUXC_SetPinConfig(QSPI_IO0_MUX,SPI_PAD_CONFIG_DATA);
    IOMUXC_SetPinConfig(QSPI_IO1_MUX,SPI_PAD_CONFIG_DATA);
    IOMUXC_SetPinConfig(QSPI_IO2_MUX,SPI_PAD_CONFIG_DATA);
    IOMUXC_SetPinConfig(QSPI_IO3_MUX,SPI_PAD_CONFIG_DATA);
    IOMUXC_SetPinConfig(QSPI_SCK_MUX,SPI_PAD_CONFIG_DATA);
    IOMUXC_SetPinConfig(QSPI_CE_MUX,SPI_PAD_CONFIG_DATA);

    CLOCK_InitUsb1Pll(&g_ccmConfigUsbPll);
    CLOCK_InitUsb1Pfd(kCLOCK_Pfd0,24);
    CLOCK_SetMux(kCLOCK_FlexspiMux, 0x3); 
    CLOCK_SetDiv(kCLOCK_FlexspiDiv, 2);  

    /* ¹Ø±ÕDCache¹¦ÄÜ */
    SCB_DisableDCache();

    FLEXSPI_GetDefaultConfig(&config);

    config.ahbConfig.enableAHBPrefetch = true;
    FLEXSPI_Init(FLEXSPI, &config);
    return true;
}

/***********************************************************************
*@Function: 
*@Input: 
*@Return: none
*@Author: sola
*@Date: 2019-11-20 21:04:21
*@Drscription: 
***********************************************************************/
void Spi_SendByte()
{


}

/***********************************************************************
*@Function: 
*@Input: 
*@Return: none
*@Author: sola
*@Date: 2019-11-20 21:04:27
*@Drscription: 
***********************************************************************/
void Spi_SendBuffer()
{


}


