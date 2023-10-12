 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Mohamed Khaled
 ******************************************************************************/

#include "Port.h"
#include "Port_Regs.h"

/* AUTOSAR Version checking between Det and Port Modules */
#include "Det.h"
/* AUTOSAR Version checking between Det and Port Modules */
#if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 || (DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 || (DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Det.h does not match the expected version"
#endif
   


/*
 * Port_Status : Holds the status of the Port Driver
 * Port_PortChannels : a pointer to structure initialized as a null pointer
 */   
STATIC uint8 Port_Status = PORT_NOT_INITIALIZED;
STATIC const Port_ConfigType * Port_PortChannels = NULL_PTR;
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
              )
{
  boolean Error=FALSE;
/*if the Development Error is enable*/  
#if (PORT_DEV_ERROR_DETECT == STD_ON)
		/* check if the input configuration pointer is not a NULL_PTR */
		if(ConfigPtr == NULL_PTR)
		{
			Det_ReportError(PORT_MODULE_ID, Port_INSTANCE_ID, PORT_INIT_SID, PORT_E_PARAM_CONFIG);
		          Error=TRUE;
                }
		else
		{	
                  /* Do Nothing */	
                }
#endif
                
    /*if ERRoR is True : Do nothing*/
  if(Error==FALSE)
    {
/*
 *Port Status Now initialized 
 */

      Port_Status = PORT_INITIALIZED;
	Port_PortChannels = ConfigPtr;

volatile uint32 * PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */
volatile uint32 delay = 0;

  
/* start initialize the Port Pin*/
  for(Port_PinType Port_Index=ZERO;Port_Index<PORT_NUMBER_OF_PORTS;Port_Index ++)
  {
          PortGpio_Ptr=NULL_PTR;

    for(Port_PinType Pin_Index=ZERO;Pin_Index<PORT_NUMBER_OF_PINS;Pin_Index++)
    {
      switch(Port_Index)
      {
                        case  0: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
			 break;
			case  1: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
			 break;
			case  2: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
			 break;
			case  3: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
			 break;
			case  4: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
			 break;
			case  5: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
			 break;
      }
      /* Enable clock for the Port*/
      SYSCTL_REGCGC2_REG |=(1<<(ConfigPtr->Pins[Port_Index][Pin_Index].Port_Num));
      delay = SYSCTL_REGCGC2_REG;
      
      
          /*if the channel ID in invalid*/
         if(ConfigPtr->Pins[Port_Index][Pin_Index].Pin_Num==PORT_NOT_AVAILABLE_PIN)
         {
           			
                                  Error=TRUE;
         }
         else
         {
           Error=FALSE;
           /*Do Nothing*/
         }
         
             /*if ERRoR is True : Do nothing*/
    if(Error==FALSE)
     {
      /*if the Pin is LOcked by the LOck Register*/
         if( (ConfigPtr->Pins[Port_Index][Pin_Index].Port_Num==PORT_D && ConfigPtr->Pins[Port_Index][Pin_Index].Pin_Num==PORT_D_PIN_LC_7)
            || (ConfigPtr->Pins[Port_Index][Pin_Index].Port_Num==PORT_F && ConfigPtr->Pins[Port_Index][Pin_Index].Pin_Num==PORT_F_PIN_LC_0))
         {
           /*Unlock the commit register*/
           *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = LOCK_REGISTER_UNLOCK_VALUE;
           /*enable the Pin*/
           SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET),(ConfigPtr->Pins[Port_Index][Pin_Index].Pin_Num));
         }
         
         else
         {
          /*Do Nothing*/ 
         }
           /*if the init Mode is DIO*/
           if(ConfigPtr->Pins[Port_Index][Pin_Index].Mode_Iint==PORT_PIN_MODE_DIO)
           {
             /*clear Analog Mode select*/
             CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr +PORT_ANALOG_MODE_SEL_REG_OFFSET),(ConfigPtr->Pins[Port_Index][Pin_Index].Pin_Num));
             /*clear Alternative Function for the Pin*/
             CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr +PORT_ALT_FUNC_REG_OFFSET),(ConfigPtr->Pins[Port_Index][Pin_Index].Pin_Num));
             /* Clear the PMCx bits for this pin*/
             *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr +PORT_CTL_REG_OFFSET) &=~(0x0000000F<<(ConfigPtr->Pins[Port_Index][Pin_Index].Pin_Num * 4));
             /*Set the Enable bit according to this pin*/
             SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr +PORT_DIGITAL_ENABLE_REG_OFFSET),(ConfigPtr->Pins[Port_Index][Pin_Index].Pin_Num));
           }
           /*if the init Mode is ADC*/
           else if (ConfigPtr->Pins[Port_Index][Pin_Index].Mode_Iint==PORT_PIN_MODE_ADC)
           {
                /* Clear the corresponding bit in the GPIODEN register to disable digital functionality on this pin */
		 CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , (ConfigPtr->Pins[Port_Index][Pin_Index].Pin_Num));

	        /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
	         CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , (ConfigPtr->Pins[Port_Index][Pin_Index].Pin_Num));

        	/* Clear the PMCx bits for this pin */
		*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (ConfigPtr->Pins[Port_Index][Pin_Index].Pin_Num * 4));

		/* Set the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
		SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , (ConfigPtr->Pins[Port_Index][Pin_Index].Pin_Num));
           }
           /*Alternative Function from 1 to 9,14 and 15*/
           else
           {
             /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
			CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , (ConfigPtr->Pins[Port_Index][Pin_Index].Pin_Num));

			/* Enable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
			SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , (ConfigPtr->Pins[Port_Index][Pin_Index].Pin_Num));

			/* Set the PMCx bits for this pin */
			*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= ((ConfigPtr->Pins[Port_Index][Pin_Index].Mode_Iint & 0x0000000F) << ((ConfigPtr->Pins[Port_Index][Pin_Index].Pin_Num) * 4));

			/* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
			SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , (ConfigPtr->Pins[Port_Index][Pin_Index].Pin_Num));
		}
           /*Direction Initialization*/
           if(ConfigPtr->Pins[Port_Index][Pin_Index].Direction==PORT_PIN_OUT)
           {
             SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , (ConfigPtr->Pins[Port_Index][Pin_Index].Pin_Num));
             if(ConfigPtr->Pins[Port_Index][Pin_Index].Initial_Level==PORT_PIN_LEVEL_LOW)
             {
               /* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
		CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , (ConfigPtr->Pins[Port_Index][Pin_Index].Pin_Num));
             }
             else if(ConfigPtr->Pins[Port_Index][Pin_Index].Initial_Level==PORT_PIN_LEVEL_HIGH)
             {
               /* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
		SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , (ConfigPtr->Pins[Port_Index][Pin_Index].Pin_Num));
             }
             else
             {
               /*DO nothing*/
             }
           }
           else if(ConfigPtr->Pins[Port_Index][Pin_Index].Direction==PORT_PIN_IN)
           {
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , (ConfigPtr->Pins[Port_Index][Pin_Index].Pin_Num));
          if(ConfigPtr->Pins[Port_Index][Pin_Index].Resistor == PULL_UP)
	      {
	        /* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , (ConfigPtr->Pins[Port_Index][Pin_Index].Pin_Num));
	      }
		else if(ConfigPtr->Pins[Port_Index][Pin_Index].Resistor == PULL_DOWN)
		{
		/* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
		SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , (ConfigPtr->Pins[Port_Index][Pin_Index].Pin_Num));
		}
		else
		{
		/* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
		CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , (ConfigPtr->Pins[Port_Index][Pin_Index].Pin_Num));

		/* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */
		CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , (ConfigPtr->Pins[Port_Index][Pin_Index].Pin_Num));
		}
           }
           else
           {
             /*DO nothing*/
           }
           
          
  
  } /*if ERROR =FALSE*/
  } /*for PIN_INDEX*/
  }/*for PORT_INDEX*/ 
  }/*if ERROR =FALSE*/ 
 
 
  else
  {
    /*if ERROR = TRUE : DO nothing*/
  }
}/*end Port_Init API*/


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
                         )
{

  /*for Error states*/
  boolean Error=FALSE;
  /*for Loop to get the port number and pin number */
  Port_PinType Port_Index=ZERO;
  Port_PinType Pin_Index=ZERO;
  uint8 counter=ZERO;
  
  for(;Port_Index<PORT_NUMBER_OF_PORTS;Port_Index++)
  {
    for(;Pin_Index<PORT_NUMBER_OF_PINS;Pin_Index++)
    {
      counter++;
      if(counter==Pin)
      {
        break;
      }
    }
  }
 
  
/*if the Development Error is enable*/ 
  #if (PORT_DEV_ERROR_DETECT == STD_ON)
		/* Check if the Driver is initialized before using this function */
		if(Port_Status == PORT_NOT_INITIALIZED)
		{
			Det_ReportError(PORT_MODULE_ID, Port_INSTANCE_ID, PORT_SetPinDirection_SID, PORT_E_UNINIT);
                        Error=TRUE;
		}
		else
		{	/* Do Nothing */	}

		/* check if incorrect Port Pin ID passed */
		if(Pin >= PORT_CONFIGURED_PINS)
		{
			Det_ReportError(PORT_MODULE_ID, Port_INSTANCE_ID, PORT_SetPinDirection_SID, PORT_E_PARAM_PIN);
                        Error=TRUE;

		}
		else
		{	/* Do Nothing */	}

		/* check if Port Pin not configured as changeable */
		if(Port_PortChannels->Pins[Port_Index][Pin_Index].Direction_Changeable == STD_OFF)
		{
			Det_ReportError(PORT_MODULE_ID, Port_INSTANCE_ID, PORT_SetPinDirection_SID, PORT_E_DIRECTION_UNCHANGEABLE);
                        Error=TRUE;
	
                 }
		else
		{	
                  /* Do Nothing */	
                }
                /* check if incorrect Port Pin ID passed or JTAG PIN*/
                 if(Port_PortChannels->Pins[Port_Index][Pin_Index].Pin_Num==PORT_NOT_AVAILABLE_PIN)
                 {
                   Det_ReportError(PORT_MODULE_ID, Port_INSTANCE_ID, PORT_SetPinDirection_SID, PORT_E_PARAM_PIN);
                        Error=TRUE;

                 }
                 else
		 {	
                  /* Do Nothing */	
                 }

	#endif

  if(FALSE==Error)
  {
	volatile uint32 * PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */

	switch(Port_PortChannels->Pins[Port_Index][Pin_Index].Port_Num)
	{
		case  0: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
		 break;
		case  1: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
		 break;
		case  2: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
		 break;
		case  3: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
		 break;
		case  4: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
		 break;
		case  5: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
		 break;
	}
        if(Direction == PORT_PIN_OUT)
	{
		/* Set the corresponding bit in the GPIODIR register to configure it as output pin */
		SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_PortChannels->Pins[Port_Index][Pin_Index].Pin_Num);
	}
	else if(Direction == PORT_PIN_IN)
	{
		/* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
		CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_PortChannels->Pins[Port_Index][Pin_Index].Pin_Num);
	}
	else
	{	
          /* Do Nothing */	
        }
  }
}
#endif

/************************************************************************************
* Service Name: Port_RefreshPortDirection
* Service ID[hex]: 0x02
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Refreshes port direction.
************************************************************************************/
void Port_RefreshPortDirection(void)
{
  /*for Error states*/
  boolean Error=FALSE;
	#if (PORT_DEV_ERROR_DETECT == STD_ON)
		/* Check if the Driver is initialized before using this function */
		if(Port_Status == PORT_NOT_INITIALIZED)
		{
			Det_ReportError(PORT_MODULE_ID, Port_INSTANCE_ID, PORT_RefreshPortDirection_SID, PORT_E_UNINIT);
                        Error=TRUE;
		}
		else
		{	
                  /* Do Nothing */	
                }
	#endif
            
        if(FALSE==Error)
        {
          volatile uint32 * PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */
         /* start initialize the Port Pin*/
  for(Port_PinType Port_Index=ZERO;Port_Index<PORT_NUMBER_OF_PORTS;Port_Index ++)
  {
          PortGpio_Ptr=NULL_PTR;

    for(Port_PinType Pin_Index=ZERO;Pin_Index<PORT_NUMBER_OF_PINS;Pin_Index++)
    {
      switch(Port_Index)
      {
                        case  0: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
			 break;
			case  1: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
			 break;
			case  2: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
			 break;
			case  3: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
			 break;
			case  4: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
			 break;
			case  5: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
			 break;
      }
      if(Port_PortChannels->Pins[Port_Index][Pin_Index].Pin_Num==PORT_NOT_AVAILABLE_PIN)
      {
       /* Do Nothing */ 
      }
      else
      {
        if (Port_PortChannels->Pins[Port_Index][Pin_Index].Direction_Changeable == STD_OFF)
	{
				if(Port_PortChannels->Pins[Port_Index][Pin_Index].Direction == PORT_PIN_OUT)
				{
                                  /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
					SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) ,( Port_PortChannels->Pins[Port_Index][Pin_Index].Pin_Num));
                                }
                                else if(Port_PortChannels->Pins[Port_Index][Pin_Index].Direction == PORT_PIN_IN)
                                {
                                   /* clear the corresponding bit in the GPIODIR register to configure it as output pin */
					CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) ,( Port_PortChannels->Pins[Port_Index][Pin_Index].Pin_Num));
                                }
                                else
                                {
                                   /* Do Nothing */ 
                                }
      }
      }}}}
        else
        {
           /* Do Nothing */
        }

}
/************************************************************************************
* Service Name: Port_GetVersionInfo
* Service ID[hex]: 0x03
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): versioninfo - Pointer to where to store the version information of this module.
* Return value: None
* Description: Returns the version information of this module.
************************************************************************************/
#if (PORT_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo(Std_VersionInfoType* versioninfo)
{
	#if (PORT_DEV_ERROR_DETECT == STD_ON)
		/* check if the input configuration pointer is not a NULL_PTR */
		if(versioninfo == NULL_PTR)
		{
			Det_ReportError(PORT_MODULE_ID, Port_INSTANCE_ID, PORT_GetVersionInfo_SID, PORT_E_PARAM_POINTER);
		}
		else
		{	/* Do Nothing */	}

		/* Check if the Driver is initialized before using this function */
		if(Port_Status == PORT_NOT_INITIALIZED)
		{
			Det_ReportError(PORT_MODULE_ID, Port_INSTANCE_ID, PORT_GetVersionInfo_SID, PORT_E_UNINIT);
		}
		else
		{	/* Do Nothing */	}
	#endif

		/* Copy the module Id */
		versioninfo->moduleID = (uint16)PORT_MODULE_ID;
		/* Copy the vendor Id */
		versioninfo->vendorID = (uint16)Port_VENDOR_ID;
		/* Copy Software Major Version */
		versioninfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
		/* Copy Software Minor Version */
		versioninfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
		/* Copy Software Patch Version */
		versioninfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;
}
#endif
/************************************************************************************
* Service Name: Port_SetPinMode
* Service ID[hex]: 0x04
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): Pin - Port Pin ID number, Mode - New Port Pin mode to be set on port pin
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the port pin mode.
************************************************************************************/
#if (PORT_SET_PIN_MODE_API == STD_ON)
void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode)
{
   /*for Error states*/
  boolean Error=FALSE;
  /*for Loop to get the port number and pin number */
  Port_PinType Port_Index=ZERO;
  Port_PinType Pin_Index=ZERO;
  uint8 counter=ZERO;
  
  for(;Port_Index<PORT_NUMBER_OF_PORTS;Port_Index++)
  {
    for(;Pin_Index<PORT_NUMBER_OF_PINS;Pin_Index++)
    {
      counter++;
      if(counter==Pin)
      {
        break;
      }
    }
  }
	#if (PORT_DEV_ERROR_DETECT == STD_ON)
		/* Check if the Driver is initialized before using this function */
		if(Port_Status == PORT_NOT_INITIALIZED)
		{
			Det_ReportError(PORT_MODULE_ID, Port_INSTANCE_ID, PORT_SetPinMode_SID, PORT_E_UNINIT);
                         Error=TRUE;
		}
		else
		{	
                  /* Do Nothing */
                }

		/* check if incorrect Port Pin ID passed */
		if(Pin >= PORT_CONFIGURED_PINS)
		{
			Det_ReportError(PORT_MODULE_ID, Port_INSTANCE_ID, PORT_SetPinMode_SID, PORT_E_PARAM_PIN);
                         Error=TRUE;
		}
		else
		{	
                  /* Do Nothing */
                }
               /* check if incorrect Port Pin ID passed or JTAG PIN*/
                 if(Port_PortChannels->Pins[Port_Index][Pin_Index].Pin_Num==PORT_NOT_AVAILABLE_PIN)
                 {
                   Det_ReportError(PORT_MODULE_ID, Port_INSTANCE_ID, PORT_SetPinMode_SID, PORT_E_PARAM_PIN);
                        Error=TRUE;

                 }
                 else
		 {	
                  /* Do Nothing */	
                 }

		/* check if the Port Pin Mode passed not valid */
		if(Mode > PORT_PIN_MODE_DIO)
		{
			Det_ReportError(PORT_MODULE_ID, Port_INSTANCE_ID, PORT_SetPinMode_SID, PORT_E_PARAM_INVALID_MODE);
                         Error=TRUE;
		}
		else
		{	
                  /* Do Nothing */
                }

		/* check if the API called when the mode is unchangeable */
		if(Port_PortChannels->Pins[Port_Index][Pin_Index].Mode_Changeable == STD_OFF)
		{
			Det_ReportError(PORT_MODULE_ID, Port_INSTANCE_ID, PORT_SetPinMode_SID, PORT_E_MODE_UNCHANGEABLE);
                         Error=TRUE;
		}
		else
		{	
                  /* Do Nothing */	
                }
	#endif

  if(FALSE==Error)
  {
	volatile uint32 * PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */

	switch(Port_PortChannels->Pins[Port_Index][Pin_Index].Port_Num)
	{
		case  0: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
		 break;
		case  1: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
		 break;
		case  2: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
		 break;
		case  3: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
		 break;
		case  4: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
		 break;
		case  5: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
		 break;
	}

	if (Mode == PORT_PIN_MODE_DIO)
	{
		/* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
		CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PortChannels->Pins[Port_Index][Pin_Index].Pin_Num);

		/* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
		CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_PortChannels->Pins[Port_Index][Pin_Index].Pin_Num);

		/* Clear the PMCx bits for this pin */
		*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_PortChannels->Pins[Port_Index][Pin_Index].Pin_Num * 4));

		/* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
		SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PortChannels->Pins[Port_Index][Pin_Index].Pin_Num);
	}
	else if (Mode == PORT_PIN_MODE_ADC)
	{
		/* Clear the corresponding bit in the GPIODEN register to disable digital functionality on this pin */
		CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PortChannels->Pins[Port_Index][Pin_Index].Pin_Num);

		/* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
		CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_PortChannels->Pins[Port_Index][Pin_Index].Pin_Num);

		/* Clear the PMCx bits for this pin */
		*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_PortChannels->Pins[Port_Index][Pin_Index].Pin_Num * 4));

		/* Set the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
		SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PortChannels->Pins[Port_Index][Pin_Index].Pin_Num);
	}
	else /* Another mode */
	{
		/* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
		CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PortChannels->Pins[Port_Index][Pin_Index].Pin_Num);

		/* Enable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
		SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_PortChannels->Pins[Port_Index][Pin_Index].Pin_Num);

		/* Set the PMCx bits for this pin */
		*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (Mode & 0x0000000F << (Port_PortChannels->Pins[Port_Index][Pin_Index].Pin_Num * 4));

		/* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
		SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PortChannels->Pins[Port_Index][Pin_Index].Pin_Num);
	}
  }
}
#endif