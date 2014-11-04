/**
 ******************************************************************************
 * @file     auxilaryFunctions.h
 * @author   Michael Riedel
 * @author   Marc Kossmann
 * @version  v0.1
 * @date     22.10.2014
 * @brief    Header file for auxilaryFunctions.c
 * @details  Contains defines, includes, typedefs and declarations needed for
 *           auxilary functions.
 ******************************************************************************
 * @par History:
 * @details  22.10. Kossmann
 *           - first draft for milestone 1b
 * @details  27.10. Riedel & Kossmann
 *           - using lcdDOGM162.h
 * @details  27.10. Riedel & Kossmann
 *           - clear display function added
 * @details  03.11. Kossmann
 *           - finished documentation
 ******************************************************************************
 */

#ifndef __AUXILARY_FUNCTIONS_H__
#define __AUXILARY_FUNCTIONS_H__

#include <stdio.h>
#include <stdarg.h>
#include <system.h>
#include "includes.h"
#include "lcdDOGM162.h"
#include "altera_avalon_lcd_16207_regs.h"

/**
 * @brief  Initializes terminal output
 * @details Opens stream to JTAG-UART-device in write mode.
 * @retval none
 */
void init_term(void);

/**
 * @brief  Initializes lcd output
 * @details Calling specific lcd init functions which sends initializisation
 *           sequence to lcd. Also opens stream to lcd-device in write mode.
 * @retval none
 */
void init_lcd(void);

/**
 * @brief  Clears display
 * @details Sends clear sequence to display.
 * @retval none
 */
void clear_lcd(void);

/**
 * @brief  Writes formated string to terminal.
 * @details Usage like common printf.
 * @retval none
 */
void printf_term(const char *, ...);

/**
 * @brief  Writes formated string to lcd
 * @details Usage like common printf.
 * @retval none
 */
void printf_lcd(const char *, ...);

/**
 * @brief  Writes buffed data to terminal
 * @details Writes any buffed data to terminal stream.
 * @retval none
 */
void fflush_term();

/**
 * @brief  Writes buffed data to lcd
 * @details Writes any buffed data to lcd stream.
 * @retval none
 */
void fflush_lcd();

#endif // __AUXILARY_FUNCTIONS_H__