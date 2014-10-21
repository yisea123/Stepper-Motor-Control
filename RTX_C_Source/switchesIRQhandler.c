/**
  ***************************************************************************
  * @file      	switchesIRQhandler
  * @author  	Michael Riedel
  * @author  	Marc Kossmann
  * @version   	V0.1
  * @date      	21.10.2014
  * @brief  	IRQ-handler for switches
  ***************************************************************************
  * @par History:
  * @details V0.1 Riedel & Kossmann
  *			- first draft for milestone 1b
  ****************************************************************************
  */

#include <system.h>
#include <sys/alt_irq.h>
#include <stdint.h>
#include "includes.h"
#include "hardwareAccess.h"

extern OS_FLAG_GRP * KeyEvents;

/**
  * @brief  IRQ-Handler for keys
  * @details set an event, depending on pressed key
  * @param  context : pointer to context variable (not used)
  * @retval none
  */
 void switchesIRQhandler(void * context)
{
   uint32_t isrsignals;
   INT8U err;

   OSIntEnter();
   isrsignals =  GetKeyReg();
   // Clear Request
   SetKeyReg(isrsignals & ~(INTERFACE_KEY_IR0_MSK |
                            INTERFACE_KEY_IR1_MSK |
                            INTERFACE_KEY_IR2_MSK));

   isrsignals = isrsignals & (INTERFACE_KEY_IR0_MSK |
                              INTERFACE_KEY_IR1_MSK |
                              INTERFACE_KEY_IR2_MSK);
   // Send Event
   OSFlagPost(KeyEvents, isrsignals, OS_FLAG_SET, &err);
   OSIntExit();
}

