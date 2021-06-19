/*
 * Master Microcontroller.c
 *
 * Created : 6/16/2021 4:04:21 AM
 *
 * Author : Aya-A.Toson--Smart_Home_Project_Q9
 *
 * Description : This is the main code for the master micro-controller 
 */ 


 
 /************************************************************************/
 /*                              Includes                                */
 /************************************************************************/

#include "MSTR_Config.h"
#include "LBIT_MATH.h"
#include "LSTD_TYPES.h"
#include "LSTD_MESSAGES.h"
#include "MDIO_interface.h"
#include "MEEPROM_interface.h"
#include "HKPD_interface.h"
#include "HLCD_interface.h"
#include "HLED_interface.h"
#include "AMENU_interface.h"
#include "MTIMER_interface.h"
#include "MSPI_interface.h"
#include <avr/io.h>

#define  F_CPU  16000000UL
#include "util/delay.h"



volatile u16_t session_counter = 0;//Counts session time
u8_t session_timeout = FALSE;//Indicates session status


int main(void)
{
	u8_t temperature = 0;//The average temperature of the room
	u8_t temp_ones = NOT_SET;//The entered right number of the temperature
	u8_t temp_tens = NOT_SET;//The entered left number of the temperature
	
	u8_t login_mode = LOGOUT; //Initialize login mode as not logged in
	u8_t block_mode = FALSE;//Is true if the login is blocked or false if not blocked
	u8_t key_pressed = NOT_PRESSED;//


	/*****************  INITIALIZE  ***********************/
	LED_vInit(HLED_PORT,HLED_LOGIN);//initializes the led of login
	LED_vInit(HLED_PORT,HLED_BLOCK);//initializes the led of block
	hlcd_init();//initializes the LCD screen
	hkpd_init();//initializes the keypad
	SPI_vInitMaster();//initializes the communication protocol of SPI
	/******************************************************/		
	/* Printing Welcome screen */
	hlcd_writeString("Welcome to smart");
	hlcd_setCursor(1,0);
	hlcd_writeString("home system");
	_delay_ms(1000);//Halt the system for the given time in (ms)
	hlcd_clearLCD();//remove all previously printed characters on the LCD and move the cursor to the first column of the first row
	/***************************/
	/*Setting Passwords if not set */
	//read the state of the the passwords if set or not set
	if ( (EEPROM_ui8ReadByteFromAddress(PASS_STATUS_ADDRESS)!=PASS_SET) ) 
	{
		hlcd_writeString("Login for");//printing login menu
		hlcd_setCursor(1,0);//move the cursor to the second line
		hlcd_writeString("first time");
		_delay_ms(1000);//Halt the system for the given time in (ms)
		hlcd_clearLCD();//remove all previously printed characters on the LCD and move the cursor to the first column of the first row
		hlcd_writeString("Set Password");//printing the set password menu
		hlcd_setCursor(1,0);
		hlcd_writeString("Password:");

		/********************************* setting password **********************************************/
		u8_t pass_counter=0;//the counter of the characters of the password
		u8_t pass[PASS_SIZE]={NOT_STORED,NOT_STORED,NOT_STORED,NOT_STORED};//the array where it stored the password
		while (pass_counter<PASS_SIZE)//loop till the user finish inserting the pass
		{
			key_pressed = NOT_PRESSED;//return the variable that holds the pressed key from keypad to its initial value
			while (key_pressed == NOT_PRESSED)//repeat till the user press any key
			{
				key_pressed = hkpd_getPressed();//if the user pressed any button in keypad save the value in key_pressed
			}

			pass[pass_counter]=key_pressed;//add the entered character to the pass array
			hlcd_writeChar(key_pressed);//print the entered character
			_delay_ms(PASS_SHOW_TIME);//Halt the system for the given time in (ms)
			hlcd_setCursor(1,9+pass_counter);//move the lcd cursor to the previous location to write the password symbol over the character
			hlcd_writeChar(PASS_HIDE); // to display (Password sign *)
			_delay_ms(100);//Halt the system for the given time in (ms)
			pass_counter++;//increase the characters count
		}
		EEPROM_vWriteBlockToAddress(EEPROM_PASS_ADDRESS,pass,PASS_SIZE);//save the entire password as a block to the EEPROM
		EEPROM_vWriteByteToAddress(PASS_STATUS_ADDRESS,PASS_SET);//write the status of pass as it is set
		hlcd_clearLCD();//remove all previously printed characters on the LCD and move the cursor to the first column of the first row
		hlcd_writeString("Pass Saved");// show pass saved message
		_delay_ms(500);//Halt the system for the given time in (ms)
		hlcd_clearLCD();//remove all previously printed characters on the LCD and move the cursor to the first column of the first row

		EEPROM_vWriteByteToAddress(LOGIN_BLOCKED_ADDRESS,FALSE);
	}//The end of if password is set
	else//this code of else run only if the system is not running for the first time (passwords is set)
	{
		block_mode = EEPROM_ui8ReadByteFromAddress(LOGIN_BLOCKED_ADDRESS); //read the blocked location from EEPROM
	}
	while (1)//The start of the periodic code
	{
		key_pressed = NOT_PRESSED;//return the variable that holds the pressed key from keypad to its initial value
		u8_t pass_tries_count=0;//stores how many times the user tried to log in to the system and failed
		
		if ( session_timeout==TRUE )//check for timeout
		{//if timeout flag was raised
			timer0_stop();//stop the timer that increase the session counter
			session_counter = 0;//clear session counter
			session_timeout=FALSE;//clear time out flag
			login_mode=LOGOUT;//log the user out
			key_pressed = NOT_PRESSED;//clear the key_pressed to avoid unwanted selection in the menu switch
			LED_vTurnOff(HLED_PORT,HLED_LOGIN);//turnoff the led of the LOGIN
			hlcd_clearLCD();//remove all previously printed characters on the LCD and move the cursor to the first column of the first row
			hlcd_writeString("Session Timeout");//print session timeout message
			_delay_ms(1000);//Halt the system for the given time in (ms)
		}
		while (login_mode==LOGOUT)//The user can only leave the loop only in case of he was logged in
		{
			if(block_mode==TRUE)//if the login process was blocked wait till the end of the block period
			{
				hlcd_clearLCD();//remove all previously printed characters on the LCD and move the cursor to the first column of the first row
				hlcd_writeString("Login blocked");
				hlcd_setCursor(1,0);
				hlcd_writeString("wait 20 seconds");
				LED_vTurnOn(HLED_PORT,HLED_BLOCK);//Turn on the led of Blocked
				_delay_ms(BLOCK_MODE_TIME);//Halt the system for the given time in (ms)
				pass_tries_count = 0; //Clear the count on number of wrong tries
				block_mode = FALSE;//Disable block of runtime
				LED_vTurnOff(HLED_PORT,HLED_BLOCK);//Turn off the led of Blocked
				EEPROM_vWriteByteToAddress(LOGIN_BLOCKED_ADDRESS,FALSE);//write false at blocked location in EEPROM
			}

			/************************************* login **********************************************/
			u8_t pass_counter=0;//counts the entered key of the password from the keypad
			u8_t pass[PASS_SIZE]={NOT_STORED,NOT_STORED,NOT_STORED,NOT_STORED};//temporarily hold the entire password that will be entered by the user to be check
			u8_t stored_pass[PASS_SIZE]={NOT_STORED,NOT_STORED,NOT_STORED,NOT_STORED};//temporarily hold the entire stored password that is written by the user for the first time
					
			while(login_mode!=LOGIN)//this loop is to repeat the login in case of wrong password
			{
				key_pressed = NOT_PRESSED;//return the variable that holds the pressed key from keypad to its initial value
				hlcd_clearLCD();//remove all previously printed characters on the LCD and move the cursor to the first column of the first row
				hlcd_writeString("Login mode");
				hlcd_setCursor(1,0);
				hlcd_writeString("Enter Pass:");
				_delay_ms(200);//Halt the system for the given time in (ms)
				pass_counter=0;//counts the number of entered characters
				while(pass_counter<PASS_SIZE)
				{
					while (key_pressed == NOT_PRESSED)//repeat till the user press any key
					{
						key_pressed = hkpd_getPressed();//if the user pressed any button in keypad save the value in key_pressed
					}
					pass[pass_counter]=key_pressed;//add the entered character to the pass array
					hlcd_writeChar(key_pressed);//print the entered character
					_delay_ms(PASS_SHOW_TIME);//Halt the system for the given time in (ms)
					hlcd_setCursor(1,11+pass_counter);//move the cursor of the lcd screen to the previous location
					hlcd_writeChar(PASS_HIDE);// to display (Password sign *)
					_delay_ms(100);//Halt the system for the given time in (ms)
					pass_counter++;//increase the password counter that count the characters of the pass
					key_pressed = NOT_PRESSED;//return the variable that holds the pressed key from keypad to its initial value
				}
				EEPROM_vReadBlockFromAddress(EEPROM_PASS_ADDRESS,stored_pass,PASS_SIZE);//read the stored pass from the EEPROM

				/*compare passwords*/
				if ((ui8ComparePass(pass,stored_pass,PASS_SIZE)) == TRUE)//in case of right password
				{
					login_mode = LOGIN;//set the mode to login
					pass_tries_count=0;//clear the counter of wrong tries
					hlcd_clearLCD();//remove all previously printed characters on the LCD and move the cursor to the first column of the first row
					hlcd_writeString("Right pass");
					hlcd_setCursor(1,0);
					hlcd_writeString("Login Success");
					_delay_ms(500);//Halt the system for the given time in (ms)
					LED_vTurnOn(HLED_PORT,HLED_LOGIN);//turn on the led of login
					timer0_initializeCTC();//start the timer that counts the session time
					hlcd_clearLCD();//remove all previously printed characters on the LCD and move the cursor to the first column of the first row
				}
				else//in case of wrong password
				{
					pass_tries_count++;//increase the number of wrong tries to block login if it exceeds the allowed tries
					login_mode = LOGOUT;//set the mode as not logged in
					hlcd_clearLCD();//remove all previously printed characters on the LCD and move the cursor to the first column of the first row
					hlcd_writeString("Wrong Pass");
					hlcd_setCursor(1,0);
					hlcd_writeString("Tries left:");
					hlcd_writeChar(TRIES_ALLOWED-pass_tries_count+ASCII_ZERO);//print the number of tries left before block mode to be activated
					_delay_ms(1000);//Halt the system for the given time in (ms)
					hlcd_clearLCD();//remove all previously printed characters on the LCD and move the cursor to the first column of the first row
					if (pass_tries_count>=TRIES_ALLOWED)//if the condition of the block mode is true
					{
						EEPROM_vWriteByteToAddress(LOGIN_BLOCKED_ADDRESS,TRUE);//write to the EEPROM TRUE to the the block mode address
						block_mode = TRUE;//turn on block mode
						break;//break the loop of LOGIN login #while(login_mode!=LOGIN)# at line 169
					}
				}
			}
		}
			
		/*************************************************************************************************/
		u8_t show_menu = MAIN_MENU;
		
		
		while(session_timeout!=TRUE)//Show the menu in case of the time is not out
		{
			key_pressed = NOT_PRESSED;//Set the key pressed by the user to its default value
			switch (show_menu)
			{
				case MAIN_MENU:
				do
				{
					/******************** print main Menu ******************/
					hlcd_clearLCD();
					hlcd_writeString("1:Room1 2:Room5");
					hlcd_setCursor(1,0);
					hlcd_writeString("3:Room3 4:More ");
					/*******************************************************/
					
					key_pressed = u8GetKeyPressed(login_mode);//wait for the user till key is pressed or the time is out
					_delay_ms(200);//to avoid the duplication of the pressed key
					
					if (key_pressed == SELECT_ROOM1)//If key pressed is 1
					{
						show_menu = ROOM1_MENU;//Set the next menu to be shown to room1 menu
					}
					else if (key_pressed == SELECT_ROOM2)//If key pressed is 2
					{
						show_menu = ROOM2_MENU;//Set the next menu to be shown to room2 menu
					}
					else if (key_pressed == SELECT_ROOM3)//If key pressed is 3
					{
						show_menu = ROOM3_MENU;//Set the next menu to be shown to room3 menu
					}
					else if (key_pressed == MORE_OPTION)//If key pressed is 4
					{
						show_menu = MORE_MENU;//Set the next menu to be shown to more menu
					}
					else if(key_pressed != NOT_PRESSED)//show wrong input message if the user pressed wrong key
					{
						hlcd_clearLCD();//remove all previously printed characters on the LCD and move the cursor to the first column of the first row
						hlcd_writeString("Wrong input");//print error message
						_delay_ms(500);//Halt the system for the given time in (ms)
					}
				} while ( ((key_pressed < '1') || (key_pressed > '4') ) && (session_timeout == FALSE) );//break the loop in case of valid key or time is out
				
				break;//End of main menu case
				
				case MORE_MENU:
				do
				{
					/******************** print more Menu ******************/
					hlcd_clearLCD();//remove all previously printed characters on the LCD and move the cursor to the first column of the first row
					hlcd_writeString("1:Room4    2:TV   ");
					hlcd_setCursor(1,0);
					hlcd_writeString("3:Air Cond.4:RET");
					/*******************************************************/
					key_pressed = u8GetKeyPressed(login_mode);//wait for the user till key is pressed or the time is out
					_delay_ms(200);//to avoid the duplication of the pressed key
					
					if (key_pressed == SELECT_ROOM4)//If key pressed is 1
					{
						show_menu = ROOM4_MENU;//Set the next menu to be shown to room4 menu
					}
					else if (key_pressed == SELECT_TV)//If key pressed is 2
					{
						show_menu = TV_MENU;//Set the next menu to be shown to TV menu
					}
					else if (key_pressed == SELECT_AIR_CONDITIONING)//If key pressed is 3
					{
						show_menu = AIRCONDITIONING_MENU;//Set the next menu to be shown to Air conditioning menu
					}
					else if (key_pressed == RET_OPTION)//If key pressed is 4 (RET)
					{
						show_menu = MAIN_MENU;//Set the next menu to be shown to main menu
					}
					else if(key_pressed != NOT_PRESSED)//show wrong input message if the user pressed wrong key
					{
						hlcd_clearLCD();//remove all previously printed characters on the LCD and move the cursor to the first column of the first row
						hlcd_writeString("Wrong input");//print error message
						_delay_ms(500);//Halt the system for the given time in (ms)
					}
				} while (( (key_pressed < '1') || (key_pressed > '4') ) && (session_timeout == FALSE));//break the loop in case of valid key or time is out
				
				break;//End of more menu case
				
				case AIRCONDITIONING_MENU:
				do
				{
					/******************** print more Menu ******************/
					hlcd_clearLCD();//remove all previously printed characters on the LCD and move the cursor to the first column of the first row
					hlcd_writeString("1:Set temperature ");
					hlcd_setCursor(1,0);
					hlcd_writeString("2:Control  0:RET");
					/*******************************************************/
					key_pressed = u8GetKeyPressed(login_mode);//wait for the user till key is pressed or the time is out
					_delay_ms(200);//to avoid the duplication of the pressed key
					
					if (key_pressed == SELECT_SET_TEMPERATURE)//If key pressed is 1
					{
						show_menu = TEMPERATURE_MENU;//Set the next menu to be shown to set temperature menu
					}
					else if (key_pressed == SELECT_AIR_COND_CTRL)//If key pressed is 2
					{
						show_menu = AIRCOND_CTRL_MENU;//Set the next menu to be shown to air conditioning control menu
					}
					else if (key_pressed == SELECT_AIR_COND_RET)//If key pressed is 0
					{
						show_menu = MORE_MENU;//Set the next menu to be shown to more menu
					}
					else if(key_pressed != NOT_PRESSED)//show wrong input message if the user pressed wrong key
					{
						hlcd_clearLCD();//remove all previously printed characters on the LCD and move the cursor to the first column of the first row
						hlcd_writeString("Wrong input");//print error message
						_delay_ms(500);//Halt the system for the given time in (ms)
					}
				} while (( (key_pressed < '0') || (key_pressed > '2') ) && (session_timeout == FALSE));//break the loop in case of valid key or time is out
				break;//End of air conditioning menu case
				
				case ROOM1_MENU:
				vMenuOption(ROOM1_MENU,login_mode);//call the function that show the menu of room 1
				show_menu = MAIN_MENU;//Set the next menu to be shown to main menu
				break;//End of room1 menu case
				
				case ROOM2_MENU:
				vMenuOption(ROOM2_MENU,login_mode);//call the function that show the menu of room 2
				show_menu = MAIN_MENU;//Set the next menu to be shown to main menu
				break;//End of room2 menu case
				
				case ROOM3_MENU:
				vMenuOption(ROOM3_MENU,login_mode);//call the function that show the menu of room 3
				show_menu = MAIN_MENU;//Set the next menu to be shown to main menu
				break;//End of room3 menu case
				
				case ROOM4_MENU:
				vMenuOption(ROOM4_MENU,login_mode);//call the function that show the menu of room 4
				show_menu = MORE_MENU;//Set the next menu to be shown to more menu
				break;//End of room4 menu case
				
				case TV_MENU:
				vMenuOption(TV_MENU,login_mode);//call the function that show the menu of tv
				show_menu = MORE_MENU;//Set the next menu to be shown to more menu
				break;//End of TV menu case
				
				case AIRCOND_CTRL_MENU:
				vMenuOption(AIRCOND_CTRL_MENU,login_mode);//call the function that show the menu of Air conditioning control
				show_menu = AIRCONDITIONING_MENU;//Set the next menu to be shown to air conditioning menu
				break;//End of air conditioning control menu case
				
				case TEMPERATURE_MENU:
				temperature = 0;//clear the value of temperature
				while (temperature==0 && session_timeout == FALSE)//start the loop that asks for the temperature from the user in case of the time is not out
				{
					key_pressed = NOT_PRESSED;//set the key pressed to the default value
					hlcd_clearLCD();//remove all previously printed characters on the LCD and move the cursor to the first column of the first row
					hlcd_writeString("Set temp.:__ ");//print the format of inserting temperature
					hlcd_writeChar(DEGREES_SYMBOL); // print the symbol of degree
					hlcd_writeChar('C'); // print the C character
					hlcd_setCursor(0,11);//move the cursor to the place to write the entered temperature
					_delay_ms(200);//Halt the system for the given time in (ms)

					/*******************************************************************************/
					key_pressed = u8GetKeyPressed(login_mode);//wait for the user till key is pressed or the time is out
					_delay_ms(250);//to avoid the duplication of the pressed key

					if (session_timeout == TRUE) //in case of the time is out before the user press a key
					{
						break;//break the loop that ask for temperature
					}
					if (key_pressed <'0' || key_pressed >'9')//show wrong input message if the user entered non numeric value
					{
						hlcd_clearLCD();//remove all previously printed characters on the LCD and move the cursor to the first column of the first row
						hlcd_writeString("Wrong input");//print error message
						_delay_ms(500);//Halt the system for the given time in (ms)
						continue;//return to #while (temperature==0)# line 672
					}
					else//if the value is valid
					{
						hlcd_writeChar(key_pressed);//print the value on the lcd
						temp_tens = key_pressed-ASCII_ZERO;//save the entered value
						key_pressed = NOT_PRESSED;//set the key pressed to the default value
					}
					/*******************************************************************************/
					key_pressed = u8GetKeyPressed(login_mode);//wait for the user till key is pressed or the time is out
					_delay_ms(250);//to avoid the duplication of the pressed key
					
					if (session_timeout == TRUE)//if the user session is timeout
					{
						break;//break the loop that ask for temperature
					}
					if ((key_pressed <'0' || key_pressed >'9'))//show wrong input message if the user entered non numeric value
					{
						hlcd_clearLCD();//remove all previously printed characters on the LCD and move the cursor to the first column of the first row
						hlcd_writeString("Wrong input");//print error message
						_delay_ms(500);//Halt the system for the given time in (ms)
						continue;//repeat the loop that ask for the temperature
					}
					else//if the value is valid
					{
						hlcd_writeChar(key_pressed);//print the value on the lcd
						temp_ones = key_pressed-ASCII_ZERO;//save the entered value
						key_pressed = NOT_PRESSED;//set the key pressed to the default value
					}
					temperature = temp_tens*10 + temp_ones;//set the value of the temperature from the given separated values
					SPI_ui8TransmitRecive(SET_TEMPERATURE);//Send the code of set temperature
					_delay_ms(200);//Halt the system to prevent write collision
					SPI_ui8TransmitRecive(temperature);//send the entered temperature
					hlcd_clearLCD();//remove all previously printed characters on the LCD and move the cursor to the first column of the first row
					hlcd_writeString("Temperature Sent");//show the message
					_delay_ms(500);//Halt the system for the given time in (ms)
				}
				show_menu = AIRCONDITIONING_MENU;//Set the next menu to be shown to air conditioning menu
				break;//break from switch
			}//End of the switch
		}//End of while that repeats the menu after each successful action till session timeout
	}// end of the main while(1)
	return 0;
}//end of main function

ISR(TIMER0_COMP_vect)
{
	session_counter++;//increase the indicator of session time for every tick
}