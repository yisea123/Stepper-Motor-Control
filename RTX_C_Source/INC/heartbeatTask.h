/**
 *****************************************************************************
 * @file       heartbeatTask.h
 * @author     Michael Riedel
 * @author     Marc Kossmann
 * @version    v2.0.0
 * @date       18.11.2014
 * @brief      Header file for heartbeatTask.c
 * @details    Contains defines, includes, typedefs and declarations needed
 *             for this task.
 *****************************************************************************
 * @par History:
 * @details    v0.1.0 22.10.2014 Kossmann
 *             - first draft for milestone 1b
 * @details    v0.1.1 30.10.2014 Riedel
 *             - moved DEBUG_ON_EVENT to events.h
 * @details    v0.1.2 31.10.2014 Riedel
 *             - added defines for HEX-segments
 *             - added declaration and documentation for sub-functions
 * @details    v0.1.3 31.10.2014 Riedel & Kossmann
 *             - finilized heartbeat functionality
 * @details    v0.1.4 02.11.2014 Riedel
 *             - corrected documentation
 * @details    v1.0.0 03.11.2014 Kossmann
 *             - fixed some minor syntax mistakes to get flawless compile
 * @details    v1.0.1 13.11. Kossmann
 *             - moved all own data types to dataTypes.h
 * @details    v2.0.0 18.11.2014 Riedel & Kossmann
 *             - verified functionality -> release MS2
 *****************************************************************************
 */

#ifndef __HEARTBEAT_TASK_H__
#define __HEARTBEAT_TASK_H__

#include <stdbool.h>
#include "includes.h"
#include "events.h"
#include "hardwareAccess.h"
#include "registerAccess.h"
#include "debugAndErrorOutput.h"
#include "dataTypes.h"

#define LOWER_O (0b1011100) //!< represents the letter **o** in the **lower** HEX-segments
#define UPPER_O (0b1100011) //!< represents the letter **o** in the **upper** HEX-segments
#define LINE    (0b1000000) //!< represents a centered **bar** in the HEX-segments
#define LED_ON	(0x1)		//!< turn the led on
#define LED_OFF (0x0)		//!< turn the led off

/**
 * @brief   The task for the hearbeat and the debug-mode.
 * @details This task is doing a heartbeat to show scheduling is working.
 *          Therefore changes its state every second via the
 *          nextHeartbeatStep()-function. When the UserInputTask detects,
 *          that the user activated the Debug-Mode, it sends the
 *          DEBUG_ON_EVENT. The task then calls the
 *          debugAndHeartbeat()-function.
 * 
 * @param   pdata : Pointer to parameter structure (not used)
 */
void HeartbeatTask(void *pdata);

/**
 * @brief   State machine for the heartbeat.
 * @details The state machine activates and deactivates the red LED9 and
 *          shows the defined HEX-values (LOWER_O, UPPER_O and LINE) on
 *          HEX3 accordingly after 1 second.
 *
 * @param   heartbeatStatePtr Points to the state-structure containing the
 *          actual state.
 */
void nextHeartbeatStep(heartbeatState_t *heartbeatStatePtr);

/**
 * @brief   This function implements the debug-logic
 * @details In Debug-mode, the **registers are read and set** in predefined
 *          intervals. It automatically calls the
 *          nextHeartbeatStep()-function to change the states.
 *          | subfunction              | state  | 
 *          | ------------------------ | :----: |
 *          | next heartbeat-step      | every  |
 *          | check Run-Bit in ctrlReg | every  |
 *          | check Dir-Bit in ctrlReg | every  |
 *          | set stepsReg (+10 / -10) | every  |
 *          | set IR-Bit in ctrlReg    | FOURTH |
 * 
 * @param   heartbeatStatePtr Points to the state-structure containing the
 *          actual state.
 */
void debugAndHeartbeat(heartbeatState_t *heartbeatStatePtr);

#endif // __HEARTBEAT_TASK_H__
