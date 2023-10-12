/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_PBcfg.c
 *
 * Description: Post Build Configuration Source file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Mohamed Khaled
 ******************************************************************************/

#include "Port.h"

/*
 * Module Version 1.0.0
 */
#define PORT_PBCFG_SW_MAJOR_VERSION              (1U)
#define PORT_PBCFG_SW_MINOR_VERSION              (0U)
#define PORT_PBCFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_PBCFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_PBCFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_PBCFG_AR_RELEASE_PATCH_VERSION     (3U)

/* AUTOSAR Version checking between Dio_PBcfg.c and Dio.h files */
#if ((PORT_PBCFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of PBcfg.c does not match the expected version"
#endif

/* Software Version checking between Dio_PBcfg.c and Dio.h files */
#if ((PORT_PBCFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_PBCFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_PBCFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of PBcfg.c does not match the expected version"
#endif

/*
     port_num,pin_num,direction,Direction_Changeable,resistor,initial_Level,Mode_Iint,Mode_Changeable;
*/
/*Initialized structure for Port_Init API*/
const Port_ConfigType Port_Configuration ={{
                                             /*PORT A Initialization*/
                                            {{PORT_A,PORT_A_PIN_0,PORT_PIN_OUT,DIRECTION_CHANGE,OFF,PORT_PIN_LEVEL_LOW,PORT_PIN_MODE_DIO,Mode_CHANGE},
                                            {PORT_A,PORT_A_PIN_1,PORT_PIN_OUT,DIRECTION_CHANGE,OFF,PORT_PIN_LEVEL_LOW,PORT_PIN_MODE_DIO,Mode_CHANGE},
                                            {PORT_A,PORT_A_PIN_2,PORT_PIN_OUT,DIRECTION_CHANGE,OFF,PORT_PIN_LEVEL_LOW,PORT_PIN_MODE_DIO,Mode_CHANGE},
                                            {PORT_A,PORT_A_PIN_3,PORT_PIN_OUT,DIRECTION_CHANGE,OFF,PORT_PIN_LEVEL_LOW,PORT_PIN_MODE_DIO,Mode_CHANGE},
                                            {PORT_A,PORT_A_PIN_4,PORT_PIN_OUT,DIRECTION_CHANGE,OFF,PORT_PIN_LEVEL_LOW,PORT_PIN_MODE_DIO,Mode_CHANGE},
                                            {PORT_A,PORT_A_PIN_5,PORT_PIN_OUT,DIRECTION_CHANGE,OFF,PORT_PIN_LEVEL_LOW,PORT_PIN_MODE_DIO,Mode_CHANGE},
                                            {PORT_A,PORT_A_PIN_6,PORT_PIN_OUT,DIRECTION_CHANGE,OFF,PORT_PIN_LEVEL_LOW,PORT_PIN_MODE_DIO,Mode_CHANGE},
                                            {PORT_A,PORT_A_PIN_7,PORT_PIN_OUT,DIRECTION_CHANGE,OFF,PORT_PIN_LEVEL_LOW,PORT_PIN_MODE_DIO,Mode_CHANGE}},
                                        
                                            /*PORT B Initialization*/
                                            {{PORT_B,PORT_B_PIN_0,PORT_PIN_OUT,DIRECTION_CHANGE,OFF,PORT_PIN_LEVEL_LOW,PORT_PIN_MODE_DIO,Mode_CHANGE},
                                            {PORT_B,PORT_B_PIN_1,PORT_PIN_OUT,DIRECTION_CHANGE,OFF,PORT_PIN_LEVEL_LOW,PORT_PIN_MODE_DIO,Mode_CHANGE},
                                            {PORT_B,PORT_B_PIN_2,PORT_PIN_OUT,DIRECTION_CHANGE,OFF,PORT_PIN_LEVEL_LOW,PORT_PIN_MODE_DIO,Mode_CHANGE},
                                            {PORT_B,PORT_B_PIN_3,PORT_PIN_OUT,DIRECTION_CHANGE,OFF,PORT_PIN_LEVEL_LOW,PORT_PIN_MODE_DIO,Mode_CHANGE},
                                            {PORT_B,PORT_B_PIN_4,PORT_PIN_OUT,DIRECTION_CHANGE,OFF,PORT_PIN_LEVEL_LOW,PORT_PIN_MODE_DIO,Mode_CHANGE},
                                            {PORT_B,PORT_B_PIN_5,PORT_PIN_OUT,DIRECTION_CHANGE,OFF,PORT_PIN_LEVEL_LOW,PORT_PIN_MODE_DIO,Mode_CHANGE},
                                            {PORT_B,PORT_B_PIN_6,PORT_PIN_OUT,DIRECTION_CHANGE,OFF,PORT_PIN_LEVEL_LOW,PORT_PIN_MODE_DIO,Mode_CHANGE},
                                            {PORT_B,PORT_B_PIN_7,PORT_PIN_OUT,DIRECTION_CHANGE,OFF,PORT_PIN_LEVEL_LOW,PORT_PIN_MODE_DIO,Mode_CHANGE}},
                                          
                                            /*PORT C Initialization*/
                                            {{PORT_NOT_AVAILABLE_PIN,PORT_NOT_AVAILABLE_PIN},
                                            {PORT_NOT_AVAILABLE_PIN,PORT_NOT_AVAILABLE_PIN},
                                            {PORT_NOT_AVAILABLE_PIN,PORT_NOT_AVAILABLE_PIN},
                                            {PORT_NOT_AVAILABLE_PIN,PORT_NOT_AVAILABLE_PIN},
                                            {PORT_C,PORT_C_PIN_4,PORT_PIN_OUT,DIRECTION_CHANGE,OFF,PORT_PIN_LEVEL_LOW,PORT_PIN_MODE_DIO,Mode_CHANGE},
                                            {PORT_C,PORT_C_PIN_5,PORT_PIN_OUT,DIRECTION_CHANGE,OFF,PORT_PIN_LEVEL_LOW,PORT_PIN_MODE_DIO,Mode_CHANGE},
                                            {PORT_C,PORT_C_PIN_6,PORT_PIN_OUT,DIRECTION_CHANGE,OFF,PORT_PIN_LEVEL_LOW,PORT_PIN_MODE_DIO,Mode_CHANGE},
                                            {PORT_C,PORT_C_PIN_7,PORT_PIN_OUT,DIRECTION_CHANGE,OFF,PORT_PIN_LEVEL_LOW,PORT_PIN_MODE_DIO,Mode_CHANGE}},
                                           
                                            /*PORT D Initialization*/
                                            { {PORT_D,PORT_D_PIN_0,PORT_PIN_OUT,DIRECTION_CHANGE,OFF,PORT_PIN_LEVEL_LOW,PORT_PIN_MODE_DIO,Mode_CHANGE},
                                            {PORT_D,PORT_D_PIN_1,PORT_PIN_OUT,DIRECTION_CHANGE,OFF,PORT_PIN_LEVEL_LOW,PORT_PIN_MODE_DIO,Mode_CHANGE},
                                            {PORT_D,PORT_D_PIN_2,PORT_PIN_OUT,DIRECTION_CHANGE,OFF,PORT_PIN_LEVEL_LOW,PORT_PIN_MODE_DIO,Mode_CHANGE},
                                            {PORT_D,PORT_D_PIN_3,PORT_PIN_OUT,DIRECTION_CHANGE,OFF,PORT_PIN_LEVEL_LOW,PORT_PIN_MODE_DIO,Mode_CHANGE},
                                            {PORT_D,PORT_D_PIN_4,PORT_PIN_OUT,DIRECTION_CHANGE,OFF,PORT_PIN_LEVEL_LOW,PORT_PIN_MODE_DIO,Mode_CHANGE},
                                            {PORT_D,PORT_D_PIN_5,PORT_PIN_OUT,DIRECTION_CHANGE,OFF,PORT_PIN_LEVEL_LOW,PORT_PIN_MODE_DIO,Mode_CHANGE},
                                            {PORT_D,PORT_D_PIN_6,PORT_PIN_OUT,DIRECTION_CHANGE,OFF,PORT_PIN_LEVEL_LOW,PORT_PIN_MODE_DIO,Mode_CHANGE},
                                            {PORT_D,PORT_D_PIN_LC_7,PORT_PIN_OUT,DIRECTION_CHANGE,OFF,PORT_PIN_LEVEL_LOW,PORT_PIN_MODE_DIO,Mode_CHANGE}},
                                            
                                            /*PORT E Initialization*/
                                            {{PORT_E,PORT_E_PIN_0,PORT_PIN_OUT,DIRECTION_CHANGE,OFF,PORT_PIN_LEVEL_LOW,PORT_PIN_MODE_DIO,Mode_CHANGE},
                                            {PORT_E,PORT_E_PIN_1,PORT_PIN_OUT,DIRECTION_CHANGE,OFF,PORT_PIN_LEVEL_LOW,PORT_PIN_MODE_DIO,Mode_CHANGE},
                                            {PORT_E,PORT_E_PIN_2,PORT_PIN_OUT,DIRECTION_CHANGE,OFF,PORT_PIN_LEVEL_LOW,PORT_PIN_MODE_DIO,Mode_CHANGE},
                                            {PORT_E,PORT_E_PIN_3,PORT_PIN_OUT,DIRECTION_CHANGE,OFF,PORT_PIN_LEVEL_LOW,PORT_PIN_MODE_DIO,Mode_CHANGE},
                                            {PORT_E,PORT_E_PIN_4,PORT_PIN_OUT,DIRECTION_CHANGE,OFF,PORT_PIN_LEVEL_LOW,PORT_PIN_MODE_DIO,Mode_CHANGE},
                                            {PORT_E,PORT_E_PIN_5,PORT_PIN_OUT,DIRECTION_CHANGE,OFF,PORT_PIN_LEVEL_LOW,PORT_PIN_MODE_DIO,Mode_CHANGE},
                                            {PORT_NOT_AVAILABLE_PIN,PORT_NOT_AVAILABLE_PIN},
                                            {PORT_NOT_AVAILABLE_PIN,PORT_NOT_AVAILABLE_PIN}},
                                             
                                            /*PORT F Initialization*/
                                            {{PORT_F,PORT_F_PIN_LC_0,PORT_PIN_OUT,DIRECTION_CHANGE,OFF,PORT_PIN_LEVEL_LOW,PORT_PIN_MODE_DIO,Mode_CHANGE},
                                            {PORT_F,PORT_F_PIN_1,PORT_PIN_OUT,DIRECTION_CHANGE,OFF,PORT_PIN_LEVEL_LOW,PORT_PIN_MODE_DIO,NO_Mode_CHANGE},
                                            {PORT_F,PORT_F_PIN_2,PORT_PIN_OUT,DIRECTION_CHANGE,OFF,PORT_PIN_LEVEL_LOW,PORT_PIN_MODE_DIO,Mode_CHANGE},
                                            {PORT_F,PORT_F_PIN_3,PORT_PIN_OUT,DIRECTION_CHANGE,OFF,PORT_PIN_LEVEL_LOW,PORT_PIN_MODE_DIO,Mode_CHANGE},
                                            {PORT_F,PORT_F_PIN_4,PORT_PIN_IN,DIRECTION_CHANGE,PULL_UP,PORT_PIN_LEVEL_HIGH,PORT_PIN_MODE_DIO,NO_Mode_CHANGE},
                                            {PORT_NOT_AVAILABLE_PIN,PORT_NOT_AVAILABLE_PIN},
                                            {PORT_NOT_AVAILABLE_PIN,PORT_NOT_AVAILABLE_PIN},
                                            {PORT_NOT_AVAILABLE_PIN,PORT_NOT_AVAILABLE_PIN}}
}};