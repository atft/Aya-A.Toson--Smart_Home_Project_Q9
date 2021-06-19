
/**
 * @file    HKPD_program.c
 * @author  Aya-A.Toson--Smart_Home_Project_Q9
 * @brief   This file contains logical implementations of DIO Module.
 * @version 1.0
 * @date    16-6-2021
 *
 * @copyright Copyright (c) 2021
 *
 */
 
/************************************************************************/
/*                              Includes                                */
/************************************************************************/

#include "LSTD_TYPES.h"
#include "LBIT_MATH.h"
#include "MDIO_interface.h"
#include "HKPD_private.h"
#include "HKPD_interface.h"

#define  F_CPU  16000000UL
#include "util/delay.h"

/************************************************************************/
/*                            Important macros                          */
/************************************************************************/

#define HKPD_COL_NUM     (3)
#define HKPD_ROW_NUM     (4)

/************************************************************************/
/*                            Important KPD variables                   */
/************************************************************************/

u8_t gu8_kpd_arr[HKPD_ROW_NUM][HKPD_COL_NUM] = {
											     {'1', '2', '3'},
												 {'4', '5', '6'},
												 {'7', '8', '9'},
												 {'*', '0', '#'}
											   };

/************************************************************************/
/*                          Functions' definitions                      */
/************************************************************************/

void hkpd_init(void)
{
	/*Setting the columns' pins to output*/
	mdio_setPinStatus(HKPD_COLS_PORT, (HKPD_COL0_PIN | HKPD_COL1_PIN | HKPD_COL2_PIN), OUTPUT);

	/*Setting the rows' pins to input and enable pull-up resistor*/
	mdio_setPinStatus(HKPD_ROWS_PORT, (HKPD_ROW0_PIN | HKPD_ROW1_PIN | HKPD_ROW2_PIN | HKPD_ROW3_PIN), INPUT_PULLUP);
	
	/*Setting the columns' pin to output high*/
	mdio_setPinValue(HKPD_COLS_PORT, (HKPD_COL0_PIN | HKPD_COL1_PIN | HKPD_COL2_PIN), HIGH);
	
	/*Return from this function*/
	return;
}

u8_t hkpd_getPressed(void)
{
	/*Local variable used in columns looping operations*/
	u8_t au8_col_looping_var = 0;
	
	/*Local variable used in rows looping operations*/
	u8_t au8_row_looping_var = 0;
	
	/*Local variable used to indicate if there's key pressed or not*/
	u8_t au8_pressedFlag = 0;

	u8_t pu8_pressedKey = NOT_PRESSED; //the variable contain the value which will be returned which will be key pressed or not pressed in case of no key pressed
	
	/*Looping over columns' pins*/
	for(au8_col_looping_var = 0; au8_col_looping_var < HKPD_COL_NUM; au8_col_looping_var++)
	{
		/*Set the selected column pin to LOW*/
		mdio_setPinValue(HKPD_COLS_PORT, (HKPD_COL0_PIN << au8_col_looping_var), LOW);
		
		/*Looping over rows' pins*/
		for(au8_row_looping_var = 0; au8_row_looping_var < HKPD_ROW_NUM; au8_row_looping_var++)
		{
			/*Checking if any row pin value is LOW*/
			if(mdio_getPinValue(HKPD_ROWS_PORT, (HKPD_ROW0_PIN << au8_row_looping_var)) == LOW)
			{
				/*Wait for 30ms to de-bounce the pressed key*/
				_delay_ms(30);
				
				/*Return the pressed key value*/
				pu8_pressedKey = gu8_kpd_arr[au8_row_looping_var][au8_col_looping_var];
				
				/*Set the flag as pressed*/
				au8_pressedFlag = 1;
				
				/*Break from the rows' loop*/
				break;	
			}
			else
			{
				/*Do nothing*/
			}
		}
		
		/*Set the selected column pin to HIGH*/
		mdio_setPinValue(HKPD_COLS_PORT, (HKPD_COL0_PIN << au8_col_looping_var), HIGH);
		
		/*Checking if any key is pressed or not*/
		if(au8_pressedFlag)
		{
			/*Break from columns' loop*/
			break;
		}
		else
		{
			/*Resetting the pressed key variable*/
			pu8_pressedKey = NOT_PRESSED;
		}
	}
			
	/*Return from this function*/
	return pu8_pressedKey;
}