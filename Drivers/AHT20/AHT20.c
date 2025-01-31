/**
 * @brief       AHT20.h
 * @details     Humidity and Temperature Sensor.
 *              Functions file.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        31/January/2022
 * @version     31/January/2022    The ORIGIN
 * @pre         N/A
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

 #include "AHT20.h"


 /**
 * @brief       AHT20_Init ( I2C_parameters_t )
 *
 * @details     It configures the I2C peripheral.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of AHT20_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        03/February/2022
 * @version     03/February/2022   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
AHT20_status_t  AHT20_Init ( I2C_parameters_t myI2Cparameters )
{
	i2c_status_t aux;

    aux  =   i2c_init ( myI2Cparameters );



    if ( aux == I2C_SUCCESS )
    {
        return   AHT20_SUCCESS;
    }
    else
    {
        return   AHT20_FAILURE;
    }
}



/**
 * @brief       AHT20_Calibrate    ( I2C_parameters_t )
 * @details     It calibrates the device.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return      Status of AHT20_Calibrate
 *
 * @author      Manuel Caballero
 * @date        03/February/2022
 * @version     03/February/2022        The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
AHT20_status_t  AHT20_Calibrate ( I2C_parameters_t myI2Cparameters )
{
    uint8_t      cmd[]	=	{ 0, 0, 0 };
    i2c_status_t aux;


    /* Update the register	*/
    cmd[0]	 =	 AHT20_INITIALIZATION;
    cmd[1]	 =	 INITIALIZATION_DATA_1;
    cmd[2]	 =	 INITIALIZATION_DATA_2;
    aux 	 =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );




    if ( aux == I2C_SUCCESS )
    {
        return   AHT20_SUCCESS;
    }
    else
    {
        return   AHT20_FAILURE;
    }
}



/**
 * @brief       AHT20_SoftReset    ( I2C_parameters_t )
 * @details     It performs a soft-reset.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return      Status of AHT20_SoftReset
 *
 * @author      Manuel Caballero
 * @date        03/February/2022
 * @version     03/February/2022        The ORIGIN
 * @pre         The user must consider that the time required for soft-reset does not exceed 20 ms.
 * @warning     N/A.
 */
AHT20_status_t  AHT20_SoftReset ( I2C_parameters_t myI2Cparameters )
{
    uint8_t      cmd	=	0U;
    i2c_status_t aux;


    /* Update the register	*/
    cmd	 =	 AHT20_SOFTRESET;
    aux	 =   i2c_write ( myI2Cparameters, (uint8_t*)&cmd, 1U, I2C_STOP_BIT );




    if ( aux == I2C_SUCCESS )
    {
        return   AHT20_SUCCESS;
    }
    else
    {
        return   AHT20_FAILURE;
    }
}



/**
 * @brief       AHT20_TriggerMeasurement ( I2C_parameters_t )
 * @details     It triggers a new measurement data (raw data).
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return      Status of AHT20_TriggerMeasurement
 *
 * @author      Manuel Caballero
 * @date        04/February/2022
 * @version     04/February/2022        The ORIGIN
 * @pre         The user must consider to wait for 80ms for the measurement to be completed.
 * @warning     N/A.
 */
AHT20_status_t  AHT20_TriggerMeasurement ( I2C_parameters_t myI2Cparameters )
{
    uint8_t      cmd[]	=	{0U, 0U, 0U};
    i2c_status_t aux;


    /* Update the register	*/
    cmd[0]	 =	 AHT20_TRIGGER_MEASUREMENT;
    cmd[1]	 =	 TRIGGER_MEASUREMENT_DATA_1;
    cmd[2]	 =	 TRIGGER_MEASUREMENT_DATA_2;
    aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_NO_STOP_BIT );



    if ( aux == I2C_SUCCESS )
    {
        return   AHT20_SUCCESS;
    }
    else
    {
        return   AHT20_FAILURE;
    }
}



/**
 * @brief       AHT20_TriggerStatus ( I2C_parameters_t )
 * @details     It triggers the state byte.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return      Status of AHT20_TriggerStatus
 *
 * @author      Manuel Caballero
 * @date        07/February/2022
 * @version     07/February/2022        The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
AHT20_status_t  AHT20_TriggerStatus ( I2C_parameters_t myI2Cparameters )
{
    uint8_t      cmd	=	0U;
    i2c_status_t aux;

    /* Update the register	 */
    cmd	 =	 AHT20_STATUS;
    aux	 =   i2c_write ( myI2Cparameters, (uint8_t*)&cmd, 1U, I2C_NO_STOP_BIT );



    if ( aux == I2C_SUCCESS )
    {
        return   AHT20_SUCCESS;
    }
    else
    {
        return   AHT20_FAILURE;
    }
}



/**
 * @brief       AHT20_GetStatus ( I2C_parameters_t , uint8_t* )
 * @details     It gets the state byte.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myState:			State byte.
 *
 *
 * @return      Status of AHT20_GetStatus
 *
 * @author      Manuel Caballero
 * @date        04/February/2022
 * @version     07/February/2022        AHT20_TriggerStatus function must be called first.
 * 				04/February/2022        The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
AHT20_status_t  AHT20_GetStatus ( I2C_parameters_t myI2Cparameters, uint8_t* myState )
{
    uint8_t      cmd	=	0U;
    i2c_status_t aux;

    /* Read the register	 */
    aux	 =   i2c_read ( myI2Cparameters, &(*myState), 1U );


    if ( aux == I2C_SUCCESS )
    {
        return   AHT20_SUCCESS;
    }
    else
    {
        return   AHT20_FAILURE;
    }
}



/**
 * @brief       AHT20_GetAllData ( I2C_parameters_t , AHT20_user_data_t* )
 * @details     It gets all the raw data.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myAllData:			All the data.
 *
 *
 * @return      Status of AHT20_GetAllData
 *
 * @author      Manuel Caballero
 * @date        04/February/2022
 * @version     04/February/2022        The ORIGIN
 * @pre         AHT20_TriggerMeasurement function must be called before using AHT20_GetAllData function.
 * @pre         The user must consider to wait for 80ms for the measurement to be completed.
 * @warning     N/A.
 */
AHT20_status_t  AHT20_GetAllData ( I2C_parameters_t myI2Cparameters, AHT20_user_data_t* myAllData )
{
    uint8_t      cmd[7]	=	{0U};
    i2c_status_t aux;


    /* Read the register	 */
    aux	 =   i2c_read ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

    /* Parse the data	 */
    myAllData->state	 				 	 =	 cmd[0];

    myAllData->humidity.raw_humidity	 	 =	 cmd[1];
    myAllData->humidity.raw_humidity   	   <<=	 8U;
    myAllData->humidity.raw_humidity		|=	 cmd[2];
    myAllData->humidity.raw_humidity   	   <<=	 8U;
    myAllData->humidity.raw_humidity		|=	 ( cmd[3] & 0b11110000 );
    myAllData->humidity.raw_humidity	   >>=	 4U;

    myAllData->temperature.raw_temperature	 =	 ( cmd[3] & 0b00001111 );
    myAllData->temperature.raw_temperature <<=	 8U;
    myAllData->temperature.raw_temperature	|=	 cmd[4];
    myAllData->temperature.raw_temperature <<=	 8U;
    myAllData->temperature.raw_temperature	|=	 cmd[5];

    myAllData->crc	 				 		 =	 cmd[6];



    if ( aux == I2C_SUCCESS )
    {
        return   AHT20_SUCCESS;
    }
    else
    {
        return   AHT20_FAILURE;
    }
}



/**
 * @brief       AHT20_ProcessTemperature ( uint32_t myRawTemperature )
 * @details     It processes the temperature data.
 *
 * @param[in]    myRawTemperature:   Raw temperature data.
 *
 * @param[out]   N/A.
 *
 *
 * @return      Temperature data is processed
 *
 * @author      Manuel Caballero
 * @date        04/February/2022
 * @version     04/February/2022        The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
float  AHT20_ProcessTemperature ( uint32_t myRawTemperature )
{
    /* Calculate the temperature	 */
    return  ( ( myRawTemperature * 200.0 )/1048576.0 - 50.0 );
}



/**
 * @brief       AHT20_ProcessHumidity ( uint32_t myRawHumidity )
 * @details     It processes the humidity data.
 *
 * @param[in]    myRawHumidity:   Raw humidity data.
 *
 * @param[out]   N/A.
 *
 *
 * @return      Humidity data is processed
 *
 * @author      Manuel Caballero
 * @date        04/February/2022
 * @version     04/February/2022        The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
float  AHT20_ProcessHumidity ( uint32_t myRawHumidity )
{
    /* Calculate the humidity	 */
    return  ( myRawHumidity * 100.0 )/1048576.0;
}
