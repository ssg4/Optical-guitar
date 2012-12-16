/*******************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only 
* intended for use with Renesas products. No other uses are authorized. This 
* software is owned by Renesas Electronics Corporation and is protected under
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE 
* AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS 
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE 
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software
* and to discontinue the availability of this software. By using this software,
* you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*******************************************************************************/
/*******************************************************************************
* Copyright (C) 2010 Renesas Electronics Corporation. All rights reserved.    */ 
/*******************************************************************************
* File Name    : main.c
* Version      : 1.00
* Device       : R5F562N8
* Tool Chain   : RX Family C Compiler
* H/W Platform : YRDKRX62N
* Description  : Empty application project.
*******************************************************************************/
/*******************************************************************************
* History	   : 27.08.2010 Ver. 1.00 First Release
*******************************************************************************/

/*******************************************************************************
* Outline      : main
* Description  : Main program function
* Argument     : none
* Return value : none
*******************************************************************************/
/******************************************************************************
* Project Includes
******************************************************************************/
#include <stdbool.h>

#include "lcd.h"

/* IO Port RPDL function definitions */
#include "r_pdl_io_port.h"

/* CGC RPDL function definitions */
#include "r_pdl_cgc.h"

/* CMT RPDL function definitions */
#include "r_pdl_cmt.h"

/* General RPDL function definitions */
#include "r_pdl_definitions.h"

/* RSPI API library support */
#include "YRDKRX62N_RSPI_API.h"

/* Board specific definitions */
#include "YRDKRX62N.h"

#define ON 					0
#define OFF					1

#define HIGH				1
#define LOW					0

#define LED4io	 			PORTD.DR.BIT.B5
#define LED6io	 			PORTD.DR.BIT.B2
#define LED8io 				PORTD.DR.BIT.B4
#define LED10io 			PORTD.DR.BIT.B1
#define LED12io 			PORTD.DR.BIT.B3
#define LED14io		 		PORTD.DR.BIT.B0
#define LED15io		 		PORTD.DR.BIT.B6

#define LED4io_DDR			PORTD.DDR.BIT.B5
#define LED6io_DDR			PORTD.DDR.BIT.B2
#define LED8io_DDR			PORTD.DDR.BIT.B4
#define LED10io_DDR			PORTD.DDR.BIT.B1
#define LED12io_DDR			PORTD.DDR.BIT.B3
#define LED14io_DDR			PORTD.DDR.BIT.B0
#define LED15io_DDR			PORTD.DDR.BIT.B6

#define SWITCH1				PORT4.PORT.BIT.B0
#define SWITCH1_DDR			PORT4.DDR.BIT.B0
#define SWITCH2				PORT4.PORT.BIT.B1
#define SWITCH2_DDR			PORT4.DDR.BIT.B1

#define ENABLE_LEDS			{LED4io_DDR = LED6io_DDR = LED8io_DDR = LED10io_DDR = LED12io_DDR = LED14io_DDR = LED15io_DDR = 1;}
#define ALL_LEDS_ON			{LED4io = LED6io = LED8io = LED10io = LED12io = LED14io = ON;}
#define ALL_LEDS_OFF		{LED4io = LED6io = LED8io = LED10io = LED12io = LED14io = OFF;}
#define ALL_LEDS_TOGGLE		{LED4io = LED6io = LED8io = LED10io = LED12io = LED14io = !LED4io;}
#define SWITCH_INIT			{SWITCH1_DDR = SWITCH2_DDR = 0;}

unsigned long int gTimerCount = 0;

/* Clock tick timer callback function prototype declaration */
void CB_TimerClockTick(void);
/*******************************************************************************
* Outline       : Init_TimerCapture
*
* Description   : This function initialises a CMT timer to run at 1KHz, and call
*                 the callback function CB_TimerClockTick. The function then
*                 configures the callback functions 
*
* Argument      : none
* Return value  : none
*******************************************************************************/
void Init_TimerCapture(void)
{
  /* Declare error flag */
  bool err = true;

  /* Timer is configure */
  err &=  R_CMT_Create
          (
          2,
          PDL_CMT_FREQUENCY,
          1000,
          CB_TimerClockTick,
          1
          );


  /* Halt in while loop when RPDL errors detected */  
  while (!err);
}
/*******************************************************************************
* End of function Init_TimerCapture
*******************************************************************************/

/*******************************************************************************
* Outline       : CB_TimerClockTick
* Description   : This function is called every millisecond by the CMT period
*                 interrupt. The function increments the gTimerCount variable
*                 each time it is called, which acts as a clock tick pulse used 
*                 to count the switch press duration.
* Argument      : none
* Return value  : none
*******************************************************************************/
void CB_TimerClockTick(void)
{
  /* Increment the timer count value */
  gTimerCount++;
  
  if (gTimerCount % 500 == 0)
  {
	 LED4io = !LED4io;
  }
  
}

void main(void)
{
	int mode;
	bool init;
	
	//Init_TimerCapture();
	
	/* Initialise the LCD on the RSPI bus */
    YRDKRX62N_RSPI_Init(RSPI_CHANNEL_0);
    InitialiseLCD();

	/* Display instructions onto the LCD */
	DisplayLCD(LCD_LINE1, "Mode 0");
    DisplayLCD(LCD_LINE3, "Initialised");
	DisplayLCD(LCD_LINE5, "SW1-Optical");
	DisplayLCD(LCD_LINE6, "Guitar");
	
	ENABLE_LEDS;
	LED4io = ON;
	SWITCH_INIT;
	mode = 0;
	init = true;

	while (1)
	{

		if (mode == 0)
		{
			if(init == true)
			{
				if(SWITCH1 == ON)
				{
					mode = 1;
					init = false;
				}
			}
		}
		
		if(mode == 1)
		{
			if(init == false)
			{
				ClearLCD();
				DisplayLCD(LCD_LINE1, "Mode 1");
    			DisplayLCD(LCD_LINE3, "Optical");
				DisplayLCD(LCD_LINE4, "Guitar");
				Init_TimerCapture();
				init = true;
			}
				
		}
		
	}	
	
}
/*******************************************************************************
* End of function main
*******************************************************************************/

