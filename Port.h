 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Mohamed Khaled
 ******************************************************************************/
/*   Gaurd   */
#ifndef PORT_H
#define PORT_H


/* Id for the company in the AUTOSAR */
#define Port_VENDOR_ID    (1000U)

/* PORT Module Id */
#define PORT_MODULE_ID    (124U)

/* PORT Instance Id */
#define Port_INSTANCE_ID  (0U)

#include "Common_Macros.h"
#include "Std_Types.h"


/*
 * Module Version 1.0.0
 */
#define PORT_SW_MAJOR_VERSION           (1U)
#define PORT_SW_MINOR_VERSION           (0U)
#define PORT_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_AR_RELEASE_PATCH_VERSION   (3U)

/*
 * Macros for Port Status
 */
#define PORT_INITIALIZED                (1U)
#define PORT_NOT_INITIALIZED            (0U)

/* Standard AUTOSAR types */
#include "Std_Types.h"

/* AUTOSAR checking between Std Types and Port Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

/* Port Pre-Compile Configuration Header file */
#include "Port_Cfg.h"

/* AUTOSAR Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Port_Cfg.h does not match the expected version"
#endif

/* Software Version checking between Port_Cfg.h and Dio.h files */
#if ((PORT_CFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_CFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_CFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of Port_Cfg.h does not match the expected version"
#endif

/* Non AUTOSAR files */
#include "Common_Macros.h"
   
/******************************************************************************
*                      API Service Id Macros                                 *
******************************************************************************/
   
/* Port init service ID :0x00 */
#define PORT_INIT_SID                                       ((uint8)0x00)

/* Port SetPinDirection service ID :0x01 */
#define PORT_SetPinDirection_SID                            ((uint8)0x01)

/* Port RefreshPortDirection service ID :0x02 */
#define PORT_RefreshPortDirection_SID                       ((uint8)0x02)

/* Port GetVersionInfo service ID :0x03 */
#define PORT_GetVersionInfo_SID                             ((uint8)0x03)

/* Port SetPinMode service ID :0x04 */
#define PORT_SetPinMode_SID                                 ((uint8)0x04)

   
   
/*******************************************************************************
*                      DET Error Codes                                        *
*******************************************************************************/  

/*Invalid Port Pin ID requested*/
#define PORT_E_PARAM_PIN                                   (0x0A)

/*Port Pin not configured as changeable*/
#define PORT_E_DIRECTION_UNCHANGEABLE                      (0x0B)

/*API Port_Init service called with wrong parameter*/
#define PORT_E_PARAM_CONFIG                                (0x0C)

/*API Port_SetPinMode service called when mode is unchangeable*/
#define PORT_E_PARAM_INVALID_MODE                          (0x0D)

/*API Port_SetPinMode service called when mode is unchangeable*/
#define PORT_E_MODE_UNCHANGEABLE                           (0x0E)

/*API service called without module initialization*/
#define PORT_E_UNINIT                                      (0x0F)

/*APIs called with a Null Pointer*/
#define PORT_E_PARAM_POINTER                                (0x01)


/*******************************************************************************
*                              Module Data Types                              *
*******************************************************************************/
/*Description: Data type for the symbolic name of a port pin*/
typedef uint8 Port_PinType;

/*Description: Different port pin modes*/
typedef uint8 Port_PinModeType;
/*Description: Different port pin Direction*/
typedef uint8 Port_PinDirectionType;
/* Description: Enum to hold PIN direction */
typedef enum
{
    PORT_PIN_IN,
    PORT_PIN_OUT
}Port_PinDirection;

/* Description: Enum to hold internal resistor type for PIN */
typedef enum
{
    OFF,
    PULL_UP,
    PULL_DOWN
}Port_InternalResistor;

/*Description: Enum to Direction changeable ON or OFF*/
typedef enum
{
    NO_DIRECTION_CHANGE,
    DIRECTION_CHANGE
}Port_PinDirectionChangeable;

/*Description: 
 *   Port Pin Level value from Port pin list
 */
typedef enum
{
    PORT_PIN_LEVEL_LOW,
    PORT_PIN_LEVEL_HIGH
}Port_PinLevelValue;

/* Description: 
 *      Port pin mode from mode list for use with Port_Init() function
 */
typedef enum
{
        PORT_PIN_MODE_ADC,
	PORT_PIN_MODE_ALT1,
	PORT_PIN_MODE_ALT2,
	PORT_PIN_MODE_ALT3,
	PORT_PIN_MODE_ALT4,
	PORT_PIN_MODE_ALT5,
	PORT_PIN_MODE_ALT6,
	PORT_PIN_MODE_ALT7,
	PORT_PIN_MODE_ALT8,
	PORT_PIN_MODE_ALT9,
        PORT_PIN_MODE_ALT14=14,
	PORT_PIN_MODE_ALT15=15,
	PORT_PIN_MODE_DIO
}Port_PinInitialMode;

/*
 *    Description: Parameter to indicate if the mode is changeable on a port pin during 
 *         runtime. True: Port Pin mode changeable allowed. False: Port Pin mode 
 *         changeable not permitted
 */
typedef enum
{
    NO_Mode_CHANGE,
    Mode_CHANGE
}Port_PinModeChangeable;

/*   Description: Structure to configure each individual PIN:
 *	1. the PORT Which the pin belongs to. 0, 1, 2, 3, 4 or 5
 *	2. the number of the pin in the PORT.
 *      3. the direction of pin --> INPUT or OUTPUT
 *      4. the internal resistor --> Disable, Pull up or Pull down
 *      5. the Direction changeable --> ON or OFF
 *      6. the initial Level value --> HIGH or LOW
 *      7. the initial Mode --> (DIO,ADC,SPI.....,etc)
 *      8. the Mode Changeable --> ON or OFF
 */
typedef struct 
{
    uint8 Port_Num; 
    uint8 Pin_Num; 
    Port_PinDirection Direction;
    Port_PinDirectionChangeable Direction_Changeable;
    Port_InternalResistor Resistor;
    Port_PinLevelValue Initial_Level;
    Port_PinInitialMode Mode_Iint;
    Port_PinModeChangeable Mode_Changeable;
}Port_ConfigPin;

/**/
typedef struct
{
  Port_ConfigPin  Pins[PORT_NUMBER_OF_PORTS][PORT_NUMBER_OF_PINS];
}Port_ConfigType;
/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/************************************************************************************
* Service Name: Port_Init
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Setup the pin configuration:
*              Initializes the Port Driver module.
************************************************************************************/
void Port_Init( 
                  const Port_ConfigType* ConfigPtr 
              );

/************************************************************************************
* Service Name: Port_SetPinDirection
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Direction     -     Port Pin Direction 
*                  Pin           -     Port Pin ID number
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Setup the pin Direction:
*              Sets the port pin direction.
************************************************************************************/
#if (PORT_SET_PIN_DIRECTION_API==STD_ON)
void Port_SetPinDirection( 
                            Port_PinType Pin, 
                            Port_PinDirectionType Direction 
                         );
#endif
/************************************************************************************
* Service Name: Port_RefreshPortDirection
* Sync/Async: Synchronous
* Reentrancy:Non Reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to  Refreshe port direction.     
************************************************************************************/
void Port_RefreshPortDirection( 
                                 void 
                              );

/************************************************************************************
* Service Name: Port_GetVersionInfo
* Sync/Async: Synchronous
* Reentrancy:Non Reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): versioninfo -  Pointer to where to store the version information of this module.
* Return value: None
* Description: Function to Returns the version information of this module.     
************************************************************************************/
#if (PORT_VERSION_INFO_API==STD_ON)
void Port_GetVersionInfo( 
                           Std_VersionInfoType* versioninfo 
                        );
#endif
/************************************************************************************
* Service Name: Port_SetPinMode
* Sync/Async: Synchronous
* Reentrancy:Reentrant
* Parameters (in): Pin   -     Port Pin ID number 
                   Mode  -     New Port Pin mode to be set on port pin.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to  Sets the port pin mode.     
************************************************************************************/
#if (PORT_SET_PIN_MODE_API==STD_ON)
void Port_SetPinMode( 
                       Port_PinType Pin, 
                       Port_PinModeType Mode 
                    );
#endif


/*configured structure from Port.PBcfg.h*/
extern const Port_ConfigType Port_Configuration;
#endif /* PORT_H */
