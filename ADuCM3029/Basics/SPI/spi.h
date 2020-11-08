/**
 * @brief       SPI.h
 * @details     [todo]ADUCM3029 SPI function libraries.
 *              Header file.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        11/October/2020
 * @version     11/October/2020    The ORIGIN
 * @pre         N/A
 * @warning     This file is ONLY for ADUCM3029 device.
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include <system_ADuCM3029.h>

#ifndef ADUCM3029_SPI_H_
#define ADUCM3029_SPI_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum
{
    SPI_TIMEOUT    =   232323
} spi_timeouts_t;


/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum
{
    SPI_SUCCESS  	     			=   0x00,
    SPI_FAILURE  		 			=   0x01,
	SPI_WRONG_FREQUENCY  			=   0x02,
	SPI_SILICON_ANOMALY_21000011  	=   0x03			/*!<   It applies to revision 1.2	 */
} spi_status_t;


/**
  * @brief   SPI PARAMETERS
  */
typedef struct{
    /* Port for pins: MISO, MOSI, SCLK and CS  */
	ADI_GPIO_TypeDef* misoPort;
	ADI_GPIO_TypeDef* mosiPort;
	ADI_GPIO_TypeDef* sclkPort;
	ADI_GPIO_TypeDef* csPort;

    /* Pin number  */
    uint32_t miso;
    uint32_t mosi;
    uint32_t sclk;
    uint32_t cs;

    /* SPI frequency   */
    uint32_t freq;


    /* SPI instance  */
    ADI_SPI_TypeDef* SPIInstance;

    /* Core clock that drives the SPI peripheral	 */
    uint32_t pclkFrequency;
} spi_parameters_t;




/**
  * @brief   FUNCTION PROTOTYPES
  */
/** SPI write/read function.
  */
spi_status_t	spi_transfer	( spi_parameters_t mySPIparameters, uint8_t* spi_tx_buff, uint32_t spi_tx_length, uint8_t* spi_rx_buff, uint32_t spi_rx_length );

/** SPI init function.
  */
spi_status_t    spi_init        ( spi_parameters_t mySPIparameters );


#ifdef __cplusplus
}
#endif

#endif /* ADUCM3029_SPI_H_ */
