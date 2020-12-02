/**
 * @brief       ezPyro_SMD_Sensor.h
 * @details     [TODO] ezPyro SMD I2C Pyroelectric Infrared Sensor. Single element or 2x2 array.
 *              Header file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        13/October/2020
 * @version     13/October/2020    The ORIGIN
 * @pre         N/A
 * @warning     N/A
 * @pre         This code belongs to Nimbus Centre ( http://www.nimbus.cit.ie ).
 */


#include "stdint.h"
#include "stdbool.h"
#include "i2c.h"

#ifndef EZPYRO_SMD_SENSOR_H_
#define EZPYRO_SMD_SENSOR_H_

#ifdef __cplusplus
extern "C" {
#endif


/**
  * @brief   DEFAULT ADDRESSES
  */
typedef enum
{
	EZPYRO_SMD_SENSOR_DEFAULT_ADDRESS =   0b1100101	       /*!<   ADDR: Default			                         	*/
} EZPYRO_SMD_SENSOR_addresses_t;


/**
  * @brief   REGISTER MAPPING
  */
typedef enum
{
    EZPYRO_SMD_SENSOR_TEST		       =   0x00,           /*!<  Verify communication by reading the response packet		*/
    EZPYRO_SMD_SENSOR_VERSION	       =   0x02,           /*!<  Version Packet					    						*/
    EZPYRO_SMD_SENSOR_FIFO_STATUS      =   0x04,           /*!<  FIFO Status Packet				    						*/
    EZPYRO_SMD_SENSOR_FIFO_READ_FULL   =   0x06,           /*!<  Read full data packet (17 bytes) of all channels			*/
    EZPYRO_SMD_SENSOR_FIFO_READ_ACTIVE =   0x08,           /*!<  Read data packet (up to 17 bytes) for only active channel	*/
    EZPYRO_SMD_SENSOR_FIFO_CLEAR       =   0x0A,           /*!<  Clear the current Packet (Read pointer moves on next)		*/
    EZPYRO_SMD_SENSOR_FIFO_RESET       =   0x0C,           /*!<  Clear the entire FIFO (Rd/Wr pointer reset with the Empty)	*/
    EZPYRO_SMD_SENSOR_CH_READ	       =   0x0E,           /*!<  Channel Control Packet										*/
    EZPYRO_SMD_SENSOR_CH_WRITE         =   0x10,           /*!<  Channel Control Packet			        					*/
    EZPYRO_SMD_SENSOR_ANA_READ         =   0x12,           /*!<  Analogue Settings											*/
    EZPYRO_SMD_SENSOR_ANA_WRITE        =   0x14,           /*!<  Analogue Settings											*/
    EZPYRO_SMD_SENSOR_WAKE_READ        =   0x16,           /*!<  Wake-up Packet												*/
    EZPYRO_SMD_SENSOR_WAKE_WRITE       =   0x18,           /*!<  Wake-up Packet												*/
    EZPYRO_SMD_SENSOR_ADDR_WRITE       =   0x1E,           /*!<  I2C Address												*/
    EZPYRO_SMD_SENSOR_GO_TO_SLEEP      =   0x20,           /*!<  Put the device in Sleep Mode								*/
    EZPYRO_SMD_SENSOR_WAKE_UP	       =   0x22,           /*!<  Wake up and resume normal mode								*/
    EZPYRO_SMD_SENSOR_RESET_SOFT       =   0x24,           /*!<  Soft reset													*/
	EZPYRO_SMD_SENSOR_RESET_FULL       =   0x26            /*!<  Full reset													*/
} EZPYRO_SMD_SENSOR_register_list_t;



/* Commands data replay */
typedef enum
{
    CMD_DATA_TEST_OK          =   0b00000001,				/*!<  Command replay TEST Data OK                      			*/
	CMD_DATA_TEST_ERR         =   0b00000010,				/*!<  Command replay TEST Data ERROR                   			*/

	CMD_DATA_FIFO_CLEAR_OK    =   0b00101001,				/*!<  Command replay FIFO_CLEAR Data OK                			*/
	CMD_DATA_FIFO_CLEAR_ERR   =   0b00101010,				/*!<  Command replay FIFO_CLEAR Data ERROR             			*/

	CMD_DATA_FIFO_RESET_OK    =   0b00110001,				/*!<  Command replay FIFO_RESET Data OK                			*/
	CMD_DATA_FIFO_RESET_ERR   =   0b00110010,				/*!<  Command replay FIFO_RESET Data ERROR             			*/

	CMD_DATA_GO_TO_SLEEP_OK   =   0b10000001,				/*!<  Command replay GO_TO_SLEEP Data OK              			*/
	CMD_DATA_GO_TO_SLEEP_ERR  =   0b10000010,				/*!<  Command replay GO_TO_SLEEP Data ERROR            			*/

	CMD_DATA_WAKE_UP_OK   	  =   0b10001001,				/*!<  Command replay WAKE_UP Data OK              				*/
	CMD_DATA_WAKE_UP_ERR      =   0b10001010,				/*!<  Command replay WAKE_UP Data ERROR            				*/

	CMD_DATA_RESET_SOFT_OK    =   0b10010001,				/*!<  Command replay RESET_SOFT Data OK             			*/
	CMD_DATA_RESET_SOFT_ERR   =   0b10010010,				/*!<  Command replay RESET_SOFT Data ERROR          			*/

	CMD_DATA_RESET_FULL_OK    =   0b10011001,				/*!<  Command replay RESET_FULL Data OK             			*/
	CMD_DATA_RESET_FULL_ERR   =   0b10011010				/*!<  Command replay RESET_FULL Data ERROR          			*/
} EZPYRO_SMD_SENSOR_commands_data_ok_err_t;



/* Register: FIFO STATUS PACKET ( FS ). Single byte with the status of the FIFO or wake up algorithm	*/
/**
  * @brief   WAKE_DETECTED <7>.
  *
  *          NOTE: N/A
  */
typedef enum
{
	FS_WAKE_DETECTED_MASK									=   ( 1U << 7U ),    /*!<  WAKE_DETECTED mask                           */
	FS_WAKE_DETECTED_OTHERWISE								=   ( 0U << 7U ),    /*!<  if in Sleep Mode and wake up event detected  */
	FS_WAKE_DETECTED_SLEEP_MODE_AND_WAKEUP_EVENT_DETECTED	=   ( 1U << 7U )     /*!<  if in Sleep Mode and wake up event detected  */
} EZPYRO_SMD_SENSOR_fs_wake_detected_t;


/**
  * @brief   ERROR_STATUS <6:5>. Register address automatically incremented during a multiple byte access with SPI serial interface
  *
  *          NOTE: Error status.
  */
typedef enum
{
	FS_ERROR_STATUS_MASK									=   ( 0b11 << 5U ),   		/*!<  ERROR_STATUS mask                            											*/
	FS_ERROR_STATUS_NO_ERROR								=   ( 0b00 << 5U ),   		/*!<  No error									 											*/
	FS_ERROR_STATUS_WRITE_FIFO_FULL_OR_READ_FIFO_EMPTY		=   ( 0b01 << 5U ),   		/*!<  Write when FIFO is full (FIFO count = 14) or read when FIFO is empty (FIFO count = 0)	*/
	FS_ERROR_STATUS_READ_FIFO_EARLY_TERMINATION				=   ( 0b10 << 5U ),   		/*!<  Detect I2C read FIFO early termination (read less bytes than expected)  				*/
	FS_ERROR_STATUS_READ_FIFO_EXTRA_BYTES					=   ( 0b11 << 5U )    		/*!<  Detect I2C read FIFO extra (read more bytes than expected)  							*/
} EZPYRO_SMD_SENSOR_fs_error_status_t;


/**
  * @brief   FIFO_COUNT <4:1>.
  *
  *          NOTE: Number of data packets available in the FIFO.
  */
typedef enum
{
	FS_WAKE_DETECTED_MASK									=   ( 0b1111 << 1U )	    /*!<  FIFO_COUNT mask                              */
} EZPYRO_SMD_SENSOR_fs_fifo_count_t;


/**
  * @brief   INVERTED_STATUS <0>.
  *
  *          NOTE: It is an inverse of Interrupt pin output (without masking).
  */
typedef enum
{
	FS_INVERTED_STATUS_MASK									=   ( 1U << 0U ),		/*!<  INVERTED_STATUS mask  								                    */
	FS_INVERTED_STATUS_NORMAL_OPERATION_FIFO_NOT_EMPTY		=   ( 1U << 0U ),		/*!<  In Normal Operation Mode, this bit is set (1) when the FIFO is not empty	*/
	FS_INVERTED_STATUS_NORMAL_OPERATION_FIFO_EMPTY			=   ( 0U << 0U ) 		/*!<  Reset(0) when the FIFO is empty								            */
} EZPYRO_SMD_SENSOR_fs_inverted_status_t;



/* Register: CHANNELS CONTROL PACKET ( CCP ). The channel control packet contains 5 bytes, each of which corresponds to a single channel with its individual settings. Note that channel 0 is currently used for internal test purposes only	*/
/**
  * @brief   CH_TC <7:6>.
  *
  *          NOTE: Feedback Transconductance (Ohm)
  */
typedef enum
{
	CCP_CH_TC_MASK											=   ( 0b11 << 6U ),    	/*!<  CH_TC mask    		                       								*/
	CCP_CH_TC_1_2T											=   ( 0b00 << 6U ),		/*!<  Feedback Transconductance: 1.6 Ohm							  [Default] */
	CCP_CH_TC_0_6T											=   ( 0b01 << 6U ),		/*!<  Feedback Transconductance: 0.6 Ohm	   									*/
	CCP_CH_TC_0_3T											=   ( 0b10 << 6U ),		/*!<  Feedback Transconductance: 0.3 Ohm	   									*/
	CCP_CH_TC_0_15T											=   ( 0b11 << 6U )		/*!<  Feedback Transconductance: 0.15 Ohm	   									*/
} EZPYRO_SMD_SENSOR_ccp_ch_tc_t;


/**
  * @brief   CH_HP <5:4>.
  *
  *          NOTE: High-Pass Signal Filter Frequency Selection ( Hz )
  */
typedef enum
{
	CCP_CH_HP_MASK											=   ( 0b11 << 4U ),    	/*!<  CH_HP mask    		                       								*/
	CCP_CH_HP_NORMAL_POWER_MODE_1HZ_LOW_POWER_MODE_0_17HZ	=   ( 0b00 << 4U ),		/*!<  Normal power mode: 1Hz | Low power mode: 0.17Hz				  [Default] */
	CCP_CH_HP_NORMAL_POWER_MODE_2HZ_LOW_POWER_MODE_0_33HZ	=   ( 0b01 << 4U ),		/*!<  Normal power mode: 2Hz | Low power mode: 0.33Hz							*/
	CCP_CH_HP_NORMAL_POWER_MODE_4HZ_LOW_POWER_MODE_0_66HZ	=   ( 0b10 << 4U ),		/*!<  Normal power mode: 4Hz | Low power mode: 0.66Hz							*/
	CCP_CH_HP_NORMAL_POWER_MODE_8HZ_LOW_POWER_MODE_1_30HZ	=   ( 0b11 << 4U )		/*!<  Normal power mode: 8Hz | Low power mode: 1.30Hz							*/
} EZPYRO_SMD_SENSOR_ccp_ch_hp_t;


/**
  * @brief   CH_G <3:1>.
  *
  *          NOTE: Feedback Capacitor Selection ( fF ), Relative gain
  */
typedef enum
{
	CCP_CH_G_MASK											=   ( 0b111 << 1U ),   	/*!<  CH_G mask	    		                       								*/
	CCP_CH_G_FEEDBACK_CAPACITANCE_50_RELATIVE_GAIN_X64		=   ( 0b000 << 1U ),	/*!<  Feedback capacitance:   50fF | Relative gain: 64x				  [Default] */
	CCP_CH_G_FEEDBACK_CAPACITANCE_100_RELATIVE_GAIN_X32		=   ( 0b001 << 1U ),	/*!<  Feedback capacitance:  100fF | Relative gain: 32x							*/
	CCP_CH_G_FEEDBACK_CAPACITANCE_200_RELATIVE_GAIN_X16		=   ( 0b010 << 1U ),	/*!<  Feedback capacitance:  200fF | Relative gain: 16x							*/
	CCP_CH_G_FEEDBACK_CAPACITANCE_400_RELATIVE_GAIN_X8		=   ( 0b011 << 1U ),	/*!<  Feedback capacitance:  400fF | Relative gain: 8x							*/
	CCP_CH_G_FEEDBACK_CAPACITANCE_800_RELATIVE_GAIN_X4		=   ( 0b100 << 1U ),	/*!<  Feedback capacitance:  800fF | Relative gain: 4x							*/
	CCP_CH_G_FEEDBACK_CAPACITANCE_1600_RELATIVE_GAIN_X2		=   ( 0b101 << 1U ),	/*!<  Feedback capacitance: 1600fF | Relative gain: 2x							*/
	CCP_CH_G_FEEDBACK_CAPACITANCE_3200_RELATIVE_GAIN_X1		=   ( 0b110 << 1U )		/*!<  Feedback capacitance: 3200fF | Relative gain: 1x							*/
} EZPYRO_SMD_SENSOR_ccp_ch_g_t;


/**
  * @brief   CH_ST <0>.
  *
  *          NOTE: Channel Status Selection
  */
typedef enum
{
	CCP_CH_ST_MASK											=   ( 1U << 0U ),   	/*!<  CH_ST mask    		                       								*/
	CCP_CH_ST_CHANNEL_DISABLED								=   ( 0U << 0U ),		/*!<  Channel Disabled												  [Default] */
	CCP_CH_ST_CHANNEL_ENABLED								=   ( 1U << 0U )		/*!<  Channel Enabled															*/
} EZPYRO_SMD_SENSOR_ccp_ch_st_t;



/* Register: ANALOGUE FRONT END PACKET ( AFEP_BYTE0 )	*/
/**
  * @brief   S <7:0>.
  *
  *          NOTE: Sampling rate (8 bit) :Sampling Rate = 1000/(N+1). DefauLt: N = 0x00 -> Sampling Rate = 1000/(0+1) = 1000.
  */
typedef enum
{
	AFEP__BYTE0_S_MASK										=   0xFF		    	/*!<  S mask    		                       								*/
} EZPYRO_SMD_SENSOR_afep_byte0_s_t;



/* Register: ANALOGUE FRONT END PACKET ( AFEP_BYTE1 )	*/
/**
  * @brief   LP <7>.
  *
  *          NOTE: Enable Low Power Mode
  */
typedef enum
{
	AFEP_BYTE1_LP_MASK										=   ( 1U << 7U ),    	/*!<  LP mask    		                       								*/
	AFEP_BYTE1_LP_LOW_POWER_DISABLED						=   ( 0U << 7U ),    	/*!<  Low power disabled    		                       		  [Default] */
	AFEP_BYTE1_LP_LOW_POWER_ENABLED							=   ( 1U << 7U )    	/*!<  Low power enabled	                       								*/
} EZPYRO_SMD_SENSOR_afep_byte1_lp_t;


/**
  * @brief   HP <6>.
  *
  *          NOTE: Enable high pass filter
  */
typedef enum
{
	AFEP_BYTE1_HP_MASK										=   ( 1U << 6U ),    	/*!<  HP mask    		                       								*/
	AFEP_BYTE1_HP_HIGH_PASS_FILTER_DISABLED					=   ( 0U << 6U ),    	/*!<  High pass filter disabled 	                       		  [Default] */
	AFEP_BYTE1_HP_HIGH_PASS_FILTER_ENABLED					=   ( 1U << 6U )    	/*!<  High pass filter enabled	               								*/
} EZPYRO_SMD_SENSOR_afep_byte1_hp_t;


/**
  * @brief   C_LP <5:4>.
  *
  *          NOTE: Low-Pass Signal Filter Frequency Selection
  */
typedef enum
{
	AFEP_BYTE1_C_LP_MASK																	=   ( 0b11 << 4U ),	/*!<  C_LP mask    		                       									*/
	AFEP_BYTE1_C_LP_NORMAL_POWER_MODE_LOW_PASS_FREQ_180HZ_LOW_POWER_MODE_LOW_PASS_30HZ		=   ( 0b00 << 4U ), /*!<  Normal Power Mode: 180Hz   | Low Power Mode: 30Hz      		  [Default] */
	AFEP_BYTE1_C_LP_NORMAL_POWER_MODE_LOW_PASS_FREQ_90HZ_LOW_POWER_MODE_LOW_PASS_15HZ		=   ( 0b01 << 4U ), /*!<  Normal Power Mode:  90Hz   | Low Power Mode: 15Hz							*/
	AFEP_BYTE1_C_LP_NORMAL_POWER_MODE_LOW_PASS_FREQ_45HZ_LOW_POWER_MODE_LOW_PASS_7_5HZ		=   ( 0b10 << 4U ), /*!<  Normal Power Mode:  45Hz   | Low Power Mode: 7.5Hz						*/
	AFEP_BYTE1_C_LP_NORMAL_POWER_MODE_LOW_PASS_FREQ_22_5HZ_LOW_POWER_MODE_LOW_PASS_3_75HZ	=   ( 0b11 << 4U )  /*!<  Normal Power Mode:  22.5Hz | Low Power Mode: 3.75Hz						*/
} EZPYRO_SMD_SENSOR_afep_byte1_c_lp_t;


/**
  * @brief   CLK_OUT <3>.
  *
  *          NOTE: Enable internal clock output on Clk pin ( only apply for Master. For Slave, this is ignored, because the Clk pin is used as input ).
  */
typedef enum
{
	AFEP_BYTE1_CLK_OUT_MASK									=   ( 1U << 3U ),    	/*!<  CLK_OUT mask    	                       								*/
	AFEP_BYTE1_CLK_OUT_DISABLED								=   ( 0U << 3U ),    	/*!<  Disable internal clock output on the Clk pin                     		*/
	AFEP_BYTE1_CLK_OUT_ENABLED								=   ( 1U << 3U )    	/*!<  Enable internal clock output on Clk pin            		  [Default] */
} EZPYRO_SMD_SENSOR_afep_byte1_clk_out_t;


/**
  * @brief   SYNC <2>.
  *
  *          NOTE: Sync & Clk Pin option.
  */
typedef enum
{
	AFEP_BYTE1_SYNC_MASK									=   ( 1U << 2U ),    	/*!<  SYNC mask    	                       									*/
	AFEP_BYTE1_SYNC_MASTER									=   ( 0U << 2U ),    	/*!<  Master									                  [Default] */
	AFEP_BYTE1_SYNC_SLAVE									=   ( 1U << 2U )    	/*!<  Slave									            		  			*/
} EZPYRO_SMD_SENSOR_afep_byte1_sync_t;


/**
  * @brief   INT <0>.
  *
  *          NOTE: Interrupt output ( only apply at Normal Operation Mode and not in Sleep Mode ).
  */
typedef enum
{
	AFEP_BYTE1_INT_MASK										=   ( 1U << 0U ),    	/*!<  INT mask    	                       									*/
	AFEP_BYTE1_INT_DISABLED									=   ( 0U << 0U ),    	/*!<  INT disabled								                  [Default] */
	AFEP_BYTE1_INT_ENABLED									=   ( 1U << 0U )    	/*!<  INT enabled							            		  			*/
} EZPYRO_SMD_SENSOR_afep_byte1_int_t;







#ifndef EZPYRO_SMD_SENSOR_VECTOR_STRUCT_H
#define EZPYRO_SMD_SENSOR_VECTOR_STRUCT_H
/* EZPYRO_SMD_SENSOR DATA */
typedef struct
{
    int8_t      f_wake;                  /*!<  False wakeup register                */
    uint8_t     patt2b;                  /*!<  Wakeup pattern PATT2B ( Manchester ) */
    uint8_t     patt1b;                  /*!<  Wakeup pattern PATT1B ( Manchester ) */
    uint8_t     rssi1;                   /*!<  RSSI1 Channel 1                      */
    uint8_t     rssi2;                   /*!<  RSSI2 Channel 2                      */
    uint8_t     rssi3;                   /*!<  RSSI3 Channel 3                      */

    uint32_t    data;                    /*!<  Data                                 */
} EZPYRO_SMD_SENSOR_data_t;
#endif



/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum
{
    EZPYRO_SMD_SENSOR_SUCCESS     =       0,
    EZPYRO_SMD_SENSOR_FAILURE     =       1
} EZPYRO_SMD_SENSOR_status_t;





/**
  * @brief   FUNCTION PROTOTYPES
  */
/** It configures the SPI peripheral.
    */
EZPYRO_SMD_SENSOR_status_t  EZPYRO_SMD_SENSOR_Init                            ( I2C_parameters_t myI2C_parameters                                                                                                                         );



#ifdef __cplusplus
}
#endif

#endif /* EZPYRO_SMD_SENSOR_H_ */
