
/**
 * @file    HLCD_program.c
 * @author  Aya-A.Toson--Smart_Home_Project_Q9
 * @brief   This file contains logical implementations of LCD Module.
 * @version 1.0
 * @date    16-6-2021
 *
 * @copyright Copyright (c) 2021
 *
 */
 
/************************************************************************/
/*                              Includes                                */
/************************************************************************/
#include "LBIT_MATH.h"
#include "LSTD_TYPES.h"
#include "MDIO_interface.h"
#include "HLCD_private.h"
#include "HLCD_interface.h"

#define F_CPU 16000000UL
#include "util/delay.h"

/************************************************************************/
/*                          Functions' definitions                      */
/************************************************************************/
static void hlcd_latch(void)
{
	/*Trigger writing over the LCD*/
	mdio_setPinValue(HLCD_CONTROL_PORT, HLCD_EN, LOW);
	_delay_us(50);
	mdio_setPinValue(HLCD_CONTROL_PORT, HLCD_EN, HIGH);

	/*Return from this function*/	
	return;
}

static void hlcd_sendCMD(u8_t au8_cmd)
{
	/*Writing over LCD*/
	mdio_setPinValue(HLCD_CONTROL_PORT, HLCD_RW, LOW);
	
	/*Sending command over LCD*/	
	mdio_setPinValue(HLCD_CONTROL_PORT, HLCD_RS, LOW);
	
	/*Transferring the high nibble bits*/
	mdio_setPinValue(HLCD_DATA_PORT, HLCD_DB7, GET_BIT(au8_cmd, 7));
	mdio_setPinValue(HLCD_DATA_PORT, HLCD_DB6, GET_BIT(au8_cmd, 6));
	mdio_setPinValue(HLCD_DATA_PORT, HLCD_DB5, GET_BIT(au8_cmd, 5));
	mdio_setPinValue(HLCD_DATA_PORT, HLCD_DB4, GET_BIT(au8_cmd, 4));
	
	/*Trigger writing over the LCD*/
	hlcd_latch();
	
	/*Transferring the low nibble bits*/	
	mdio_setPinValue(HLCD_DATA_PORT, HLCD_DB7, GET_BIT(au8_cmd, 3));
	mdio_setPinValue(HLCD_DATA_PORT, HLCD_DB6, GET_BIT(au8_cmd, 2));
	mdio_setPinValue(HLCD_DATA_PORT, HLCD_DB5, GET_BIT(au8_cmd, 1));
	mdio_setPinValue(HLCD_DATA_PORT, HLCD_DB4, GET_BIT(au8_cmd, 0));

	/*Trigger writing over the LCD*/	
	hlcd_latch();
	
	/*Return from this function*/
	return;
}

static void hlcd_sendData(u8_t au8_data)
{
	/*Writing over LCD*/
	mdio_setPinValue(HLCD_CONTROL_PORT, HLCD_RW, LOW);
	
	/*Sending display data over LCD*/
	mdio_setPinValue(HLCD_CONTROL_PORT, HLCD_RS, HIGH);
	
	/*Transferring the high nibble bits*/
	mdio_setPinValue(HLCD_DATA_PORT, HLCD_DB7, GET_BIT(au8_data, 7));
	mdio_setPinValue(HLCD_DATA_PORT, HLCD_DB6, GET_BIT(au8_data, 6));
	mdio_setPinValue(HLCD_DATA_PORT, HLCD_DB5, GET_BIT(au8_data, 5));
	mdio_setPinValue(HLCD_DATA_PORT, HLCD_DB4, GET_BIT(au8_data, 4));
	
	/*Trigger writing over the LCD*/
	hlcd_latch();
	
	/*Transferring the low nibble bits*/
	mdio_setPinValue(HLCD_DATA_PORT, HLCD_DB7, GET_BIT(au8_data, 3));
	mdio_setPinValue(HLCD_DATA_PORT, HLCD_DB6, GET_BIT(au8_data, 2));
	mdio_setPinValue(HLCD_DATA_PORT, HLCD_DB5, GET_BIT(au8_data, 1));
	mdio_setPinValue(HLCD_DATA_PORT, HLCD_DB4, GET_BIT(au8_data, 0));

	/*Trigger writing over the LCD*/
	hlcd_latch();
	
	/*Return from this function*/
	return;
}

void hlcd_init(void)
{
	/*LCD data pins initialization as output*/
	mdio_setPinStatus(HLCD_DATA_PORT, (HLCD_DB4 | HLCD_DB5 | HLCD_DB6 | HLCD_DB7), OUTPUT);	
	
	/*LCD control pins initialization as output*/
	mdio_setPinStatus(HLCD_CONTROL_PORT, (HLCD_RS | HLCD_RW | HLCD_EN), OUTPUT);
	mdio_setPinValue(HLCD_CONTROL_PORT, HLCD_EN, HIGH);
	
	/*Wait until Vdd rises to 4.5v*/
	_delay_ms(50);
	
	/*Writing over LCD*/
	mdio_setPinValue(HLCD_CONTROL_PORT, HLCD_RW, LOW);
	
	/*Sending command over LCD*/
	mdio_setPinValue(HLCD_CONTROL_PORT, HLCD_RS, LOW);
	
	/*Transferring the function set instruction header (4-bits)*/
	mdio_setPinValue(HLCD_DATA_PORT, HLCD_DB7, LOW);
	mdio_setPinValue(HLCD_DATA_PORT, HLCD_DB6, LOW);
	mdio_setPinValue(HLCD_DATA_PORT, HLCD_DB5, HIGH);
	mdio_setPinValue(HLCD_DATA_PORT, HLCD_DB4, LOW);
	
	/*Trigger writing over the LCD*/
	hlcd_latch();
		
	/*Sending the function set instruction*/
	hlcd_sendCMD(0x2C);
	
	/*Delay for 1 millisecond*/
	_delay_ms(1);

	/*Sending the display ON/OFF control instruction*/
	hlcd_sendCMD(0x0F);
	
	/*Delay for 1 millisecond*/
	_delay_ms(1);
	
	/*Sending the clearing display instruction*/
	hlcd_sendCMD(0x01);
	
	/*Delay for 2 millisecond*/
	_delay_ms(2);
	
	/*Sending the entry mode set instruction*/
	hlcd_sendCMD(0x06);
	
	/*Delay for 1 millisecond*/
	_delay_ms(1);

	/*Return from this function*/
	return;
}

void hlcd_writeChar(u8_t au8_charData)
{
	/*Sending the character data over LCD*/
	hlcd_sendData(au8_charData);
	
	/*Return from this function*/
	return;
}

void hlcd_writeString(u8_t* pu8_stringData)
{
	/*Looping over string characters*/
	while(*pu8_stringData != '\0')
	{
		/*Sending the character data*/
		hlcd_sendData(*pu8_stringData);
		
		/*Increment the pointer current address*/
		pu8_stringData++;
	}
	
	/*Return from this function*/
	return;
}

void hlcd_clearLCD(void)
{
	/*Sending the clearing display instruction*/
	hlcd_sendCMD(0x01);
		
	/*Delay for 2 millisecond*/
	_delay_ms(2);

	/*Return from this function*/
	return;
}

void hlcd_resetCursor(void)
{
	/* Return cursor home */
	hlcd_sendCMD(0x02);
	
	/*Delay for 2 millisecond*/
	_delay_ms(2);

	/*Return from this function*/
	return;
}

void hlcd_setCursor(u8_t au8_row , u8_t au8_col)
{
	
	u8_t au8_position = 0;
	
	/* in case of wrong input set the cursor to the first position of the LCD*/
	if(au8_row>1||au8_row<0||au8_col>15||au8_col<0)
	{
		/* Return cursor home */
		hlcd_sendCMD(0x02);
	
		/*Delay for 2 millisecond*/
		_delay_ms(2);
	}
	else{
	/* first of all calculate the required position */
	switch (au8_row)
	{
	case 0:
		au8_position = au8_col;
		break;
	case 1:
		au8_position = au8_col + 0x40;
		break;
	}

	/* to write to a specific address in the LCD(write to DDRAM address) *
	 * we need to apply the corresponding command 0b10000000+position    */
	hlcd_sendCMD(au8_position | 0x80);
	
		
	/*Delay for 2 millisecond*/
	_delay_ms(2);
	}
	/*Return from this function*/
	return;
}
