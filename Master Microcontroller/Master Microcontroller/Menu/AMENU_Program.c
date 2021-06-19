
/**
 * @file    AMENU_program.c
 * @author  Aya-A.Toson--Smart_Home_Project_Q9
 * @brief   This file contains logical implementations of Menu Module.
 * @version 1.0
 * @date    16-6-2021
 *
 * @copyright Copyright (c) 2021
 *
 */
 
/************************************************************************/
/*                              Includes                                */
/************************************************************************/
#include "MSTR_Config.h"
#include "LSTD_MESSAGES.h"
#include "LSTD_Types.h"
#include "HKPD_interface.h"
#include "MSPI_interface.h"
#include "HLCD_interface.h"
#include "AMENU_interface.h"

#define  F_CPU  16000000UL
#include "util/delay.h"

/************************************************************************/
/*                          Functions' definitions                      */
/************************************************************************/
extern volatile u16_t session_counter;//Stores the session time
extern u8_t session_timeout;//stores if the session is still valid or outdated

u8_t ui8ComparePass(const u8_t* pass1,const u8_t* pass2,const u8_t size)
{
	u8_t pin_counter=0;//the offset of the character of the pin
	u8_t ret_value = TRUE;
	while (pin_counter<size)//loop till the pin is fully entered
	{
		if (*(pass1+pin_counter)!=*(pass2+pin_counter))//if the two characters of the entered pin and the stored pin are not equal
		{
			ret_value= FALSE;//returns false that means the two PINs are not equal
			break;//break the loop
		}
		pin_counter++;//increase thee offset by one
	}
	return ret_value;//returns false that means the two PINs are equal since all characters of the PINs are equal
}

void vMenuOption(const u8_t u8SelectedRoom,const u8_t u8LoginMode)
{
	u8_t u8StatusCode  = 0;//demand status code
	u8_t u8TurnOnCode  = 0;//turn on the room or the device code
	u8_t u8TurnOffCode = 0;//turn off the device or room
	u8_t response      = DEFAULT_ACK;//the response of the slave that is sent back based on the command of the master
	u8_t key_pressed   = NOT_PRESSED;//the key that is entered by the user
	
	do
	{
		hlcd_clearLCD();//remove all previously printed characters on the LCD and move the cursor to the first column of the first row
		
		/*********** ****************Set the commands to be sent to the slave based on  the sent room or device ******************************/
		switch(u8SelectedRoom)
		{
			case ROOM1_MENU:
			u8StatusCode = ROOM1_STATUS;
			u8TurnOnCode = ROOM1_TURN_ON;
			u8TurnOffCode = ROOM1_TURN_OFF;
			hlcd_writeString("Room1 S:");
			break;
			case ROOM2_MENU:
			u8StatusCode = ROOM2_STATUS;
			u8TurnOnCode = ROOM2_TURN_ON;
			u8TurnOffCode = ROOM2_TURN_OFF;
			hlcd_writeString("Room2 S:");
			break;
			case ROOM3_MENU:
			u8StatusCode = ROOM3_STATUS;
			u8TurnOnCode = ROOM3_TURN_ON;
			u8TurnOffCode = ROOM3_TURN_OFF;
			hlcd_writeString("Room3 S:");
			break;
			case ROOM4_MENU:
			u8StatusCode = ROOM4_STATUS;
			u8TurnOnCode = ROOM4_TURN_ON;
			u8TurnOffCode = ROOM4_TURN_OFF;
			hlcd_writeString("Room4 S:");
			break;
			case TV_MENU:
			u8StatusCode = TV_STATUS;
			u8TurnOnCode = TV_TURN_ON;
			u8TurnOffCode = TV_TURN_OFF;
			hlcd_writeString("TV S:");
			break;
			case AIRCOND_CTRL_MENU:
			u8StatusCode = AIR_COND_STATUS;
			u8TurnOnCode = AIR_COND_TURN_ON;
			u8TurnOffCode = AIR_COND_TURN_OFF;
			hlcd_writeString("Air Cond. S:");
			break;
		}
		/****************************************************************************************************/
		
		SPI_ui8TransmitRecive(u8StatusCode);//demand the status from the slave
		_delay_ms(100);//Halt the system for the given time in (ms)
		response = SPI_ui8TransmitRecive(DEMAND_RESPONSE);//the master micro controller asks for the status
		if(response == ON_STATUS)//if the response from the slave was on status
		{
			hlcd_writeString("ON");//print the status on
		}
		else//if the response from the slave was off status
		{
			hlcd_writeString("OFF");//print the status off
		}

		hlcd_setCursor(1,0);//move the cursor to the start of the second line
		hlcd_writeString("1-On 2-Off 0-RET");//print the sub menu
		
		/*******************************************************************************/
		
		key_pressed = u8GetKeyPressed(u8LoginMode);//wait for the user till key is pressed or the time is out
		_delay_ms(100);//to avoid the duplication of the pressed key
		
		/*there is no need to take any action in case of the user pressed 0(RET) key
		breaking the loop will be enough since it will be handled in the main*/
		
		if (key_pressed == '1')
		{
			SPI_ui8TransmitRecive(u8TurnOnCode);//Send turn on signal from master to slave
		}
		else if (key_pressed == '2')
		{
			SPI_ui8TransmitRecive(u8TurnOffCode);//Send turn off signal from master to slave
		}
		else if( (key_pressed != NOT_PRESSED) && (key_pressed != '0') )//show wrong input message if the user entered non numeric value
		{
			hlcd_clearLCD();//remove all previously printed characters on the LCD and move the cursor to the first column of the first row
			hlcd_writeString("Wrong input");//print error message
			_delay_ms(500);//Halt the system for the given time in (ms)
		}
	} while ( ( (key_pressed < '0') || (key_pressed > '2') ) && (session_timeout == FALSE));//break the loop in case of valid key or time is out
}

u8_t u8GetKeyPressed(const u8_t u8LoginMode)
{
	u8_t key_pressed = NOT_PRESSED;
	while (key_pressed == NOT_PRESSED)//repeat till the user press any key
	{
		if ( session_counter >= LOGIN_TIMEOUT && u8LoginMode == LOGIN )//check for timeout
		{
			session_timeout = TRUE;//set timeout flag to true
			break;//break the loop that wait for input from the user
		}
		else
		{
		key_pressed = hkpd_getPressed();//if the user pressed any button in keypad save the value in key_pressed
		}
	}
	return key_pressed;
}