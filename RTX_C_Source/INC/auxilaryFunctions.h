/**
  ******************************************************************************
  * @file    	auxilaryFunctions.h
  * @author  	Michael Riedel
  * @author  	Marc Kossmann
  * @version  v0.1
  * @date     27.10.2014
  * @brief   	Header file for auxilaryFunctions.c
  * @details 	Contains defines, includes, typedefs and declarations needed for
  *           auxilary functions.
  ******************************************************************************
  * @par History:
  * @details  v0.1 Riedel & Kossmann
  *			      - first draft for milestone 1b
  ******************************************************************************
  */

#ifndef __AUXILARY_FUNCTIONS_H__
#define __AUXILARY_FUNCTIONS_H__

#include <stdio.h>
#include <stdarg.h>
#include <system.h>
#include "../INC/lcdDOGM162.h"

void init_term(void);
void init_lcd(void);
void printf_term(const char *, ...);
void printf_lcd(const char *, ...);
void fflush_term();
void fflush_lcd();

#endif