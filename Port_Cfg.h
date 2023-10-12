/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_Cfg.h
 *
 * Description: Pre-Compile Configuration Header file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Mohamed Khaled
 ******************************************************************************/
/*      Guard         */
#ifndef PORT_CFG_H
#define PORT_CFG_H

#include "Std_Types.h"
/*
 * Module Version 1.0.0
 */
#define PORT_CFG_SW_MAJOR_VERSION              (1U)
#define PORT_CFG_SW_MINOR_VERSION              (0U)
#define PORT_CFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION      (4U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION      (0U)
#define PORT_CFG_AR_RELEASE_PATCH_VERSION      (3U)

/*  Pre-Compile option for DEt Error Detect */
#define PORT_DEV_ERROR_DETECT                   STD_ON

/*  Pre-Compile option for Set Pin Direction API */
#define PORT_SET_PIN_DIRECTION_API              STD_ON

/*  Pre-Compile option for Set Pin Mode API */
#define PORT_SET_PIN_MODE_API                   STD_ON

/*  Pre-Compile option for Get the Version Info API */
#define PORT_VERSION_INFO_API                   STD_ON

/* Magic number for not found pins*/
#define PORT_NOT_AVAILABLE_PIN                  (10U)

/*number of ports*/
#define PORT_NUMBER_OF_PORTS                    (6U)

/*number of Pins*/
#define PORT_NUMBER_OF_PINS                     (8U)

/* Number of configured Pins excluding PC0....PC3 */
#define PORT_CONFIGURED_PINS                    (43U)

/* TIVA_C PORTS */
#define PORT_A                                   (0U)
#define PORT_B                                   (1U)
#define PORT_C                                   (2U)
#define PORT_D                                   (3U)
#define PORT_E                                   (4U)
#define PORT_F                                   (5U)

/* TIVA_C PORT A PINS */
#define PORT_A_PIN_0                              (0U) 
#define PORT_A_PIN_1                              (1U) 
#define PORT_A_PIN_2                              (2U) 
#define PORT_A_PIN_3                              (3U) 
#define PORT_A_PIN_4                              (4U) 
#define PORT_A_PIN_5                              (5U) 
#define PORT_A_PIN_6                              (6U) 
#define PORT_A_PIN_7                              (7U) 

/* TIVA_C PORT B PINS */
#define PORT_B_PIN_0                              (0U) 
#define PORT_B_PIN_1                              (1U) 
#define PORT_B_PIN_2                              (2U) 
#define PORT_B_PIN_3                              (3U) 
#define PORT_B_PIN_4                              (4U) 
#define PORT_B_PIN_5                              (5U) 
#define PORT_B_PIN_6                              (6U) 
#define PORT_B_PIN_7                              (7U) 

/* TIVA_C PORT C PINS (EXCLUDING JTAG PINS PC0 TO PC3 */
#define PORT_C_PIN_4                              (4U) 
#define PORT_C_PIN_5                              (5U) 
#define PORT_C_PIN_6                              (6U) 
#define PORT_C_PIN_7                              (7U) 

/* TIVA_C PORT D PINS 
   LC : FOR LOCK COMMIT ACTIONS
   */
#define PORT_D_PIN_0                              (0U) 
#define PORT_D_PIN_1                              (1U) 
#define PORT_D_PIN_2                              (2U) 
#define PORT_D_PIN_3                              (3U) 
#define PORT_D_PIN_4                              (4U) 
#define PORT_D_PIN_5                              (5U) 
#define PORT_D_PIN_6                              (6U) 
#define PORT_D_PIN_LC_7                           (7U) 

/* TIVA_C PORT E PINS */
#define PORT_E_PIN_0                              (0U) 
#define PORT_E_PIN_1                              (1U) 
#define PORT_E_PIN_2                              (2U) 
#define PORT_E_PIN_3                              (3U) 
#define PORT_E_PIN_4                              (4U) 
#define PORT_E_PIN_5                              (5U) 


/* TIVA_C PORT F PINS 
   LC : FOR LOCK COMMIT ACTIONS  
   */
#define PORT_F_PIN_LC_0                           (0U) 
#define PORT_F_PIN_1                              (1U) 
#define PORT_F_PIN_2                              (2U) 
#define PORT_F_PIN_3                              (3U) 
#define PORT_F_PIN_4                              (4U) 





/*      End Gaurd       */
#endif 