/**
  ***************************************************************************
  * @file      	main.c
  * @author  	Michael Riedel
  * @author  	Marc Kossmann
  * @version   	V0.1
  * @date      	21.10.2014
  * @brief   	Main-Routine for Stepper-Motor-Control
  ***************************************************************************
  * @par History:
  * @details V0.1 Riedel & Kossmann
  *			- first draft for milestone 1b
  ****************************************************************************
  */

#include <sys/alt_irq.h>
#include <stdio.h>
#include <stdint.h>
#include "includes.h"
#include "hardwareAccess.h"
#include "switchesIRQhandler.h"

/** @brief Definition of Task Stacks */
#define   TASK_STACKSIZE       2048

/** @brief Stack for Task 1 */
OS_STK    RedLedtask_stk[TASK_STACKSIZE];
/** @brief Stack for Task 2 */
OS_STK    GreenLedtask_stk[TASK_STACKSIZE];

/** @par Definition of Task Priorities
  * @brief lower numbers mean higher priority
  */
#define GREENLED_TASK_PRIORITY    4  /*!< Priority Task GreenLedIRQ */
#define REDLED_TASK_PRIORITY      5  /*!< Priority Task RedLedSW */

/** @brief Event variable for Key-Events */
OS_FLAG_GRP * KeyEvents;

/** @brief Variable for ISR-Context
  * @details Not used in this program
  */
uint32_t ISRcontext;


/**
  * @brief  Task RedLedSWtask
  * @details copies the position values of the sliding switches to red LEDs
  * @param  pdata : Pointer to parameter structure (not used)
  * @retval None
  */
 void RedLedSWtask(void * pdata)
{
  while (1)
  { 
    OSTimeDlyHMSM(0, 0, 0, 200);
    SetRedLed(getSW());
  }
}

/**
  * @brief  Task GreenLedIRQtask
  * @details Task counts the interrupts and displays
  *          the count value on the green leds. Simultaneously
  *          the value is displayed on JTAG-UART console.
  * @param  pdata : Pointer to parameter structure (not used)
  * @retval None
  */
 void GreenLedIRQtask(void * pdata)
{
  int32_t timeOutCount = 0;
  OS_FLAGS newKeyFlag;
  INT8U err;

  // Interrupt f�r Keys
  // Register ISR
  alt_ic_isr_register(INTERFACE_COMP_0_IRQ_INTERRUPT_CONTROLLER_ID,
		  INTERFACE_COMP_0_IRQ,
                      switchesIRQhandler, (void *) &ISRcontext, NULL);
  alt_ic_irq_enable(INTERFACE_COMP_0_IRQ_INTERRUPT_CONTROLLER_ID,
		  INTERFACE_COMP_0_IRQ);
  // Enable Interrupts in User Component and Reset IRs
  SetKeyReg(INTERFACE_KEY_IE0_MSK |
            INTERFACE_KEY_IE1_MSK |
            INTERFACE_KEY_IE2_MSK);

//  SetGreenLed(0);
  printf("Start of NIOS II - RTX Interface Tutorial Program V5.0.0\n");
  while (1)
  { 
      newKeyFlag = OSFlagPend( KeyEvents,
                              (EVT_KEY_KEY0 | EVT_KEY_KEY1 | EVT_KEY_KEY2),
                               OS_FLAG_WAIT_SET_ANY + OS_FLAG_CONSUME,
                               500, /* Timeout 5 seconds */
                               &err);
      switch(err)
      {
         case OS_TIMEOUT: printf("Key-Timeout Nr: %d\n\n",(int) ++timeOutCount);
                          break;
         case OS_NO_ERR:
                      timeOutCount = 0;
                      printf("-------------------------\n"
                             "New Key-Event\n");
                      if(newKeyFlag & EVT_KEY_KEY0)
                          printf("Interrupt Key 1 detected\n");
                      if(newKeyFlag & EVT_KEY_KEY1)
                          printf("Interrupt Key 2 detected\n");
                      if(newKeyFlag & EVT_KEY_KEY2)
                          printf("Interrupt Key 3 detected\n");
//                      SetGreenLed(GetGreenLed()+1);
                      break;
         default: printf("Error\n");
                  break;
      }
  }
}

/**
  * @brief  Main-Routine
  * @details The main function creates two task and starts multi-tasking
  * @retval Errorcode
  */
int32_t main(void)
{
  INT8U err;
  // -------- Events, Semaphor, Mutex , Mbx  ---------------------------
  // Define Key-Eventvariable
  KeyEvents = OSFlagCreate(0x0000,&err);

  // -------------------- Tasks ----------------------------------------
  OSTaskCreateExt(RedLedSWtask,
                  NULL,
                  (void *)&RedLedtask_stk[TASK_STACKSIZE-1],
                  REDLED_TASK_PRIORITY,
                  REDLED_TASK_PRIORITY,
                  RedLedtask_stk,
                  TASK_STACKSIZE,
                  NULL,
                  0);

  OSTaskCreateExt(GreenLedIRQtask,
                  NULL,
                  (void *)&GreenLedtask_stk[TASK_STACKSIZE-1],
                  GREENLED_TASK_PRIORITY,
                  GREENLED_TASK_PRIORITY,
                  GreenLedtask_stk,
                  TASK_STACKSIZE,
                  NULL,
                  0);
  OSStart();
  return 0;
}