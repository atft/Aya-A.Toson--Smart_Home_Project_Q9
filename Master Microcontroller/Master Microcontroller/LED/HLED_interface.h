
/**
 * @file    HLED_interface.h
 * @author  Aya-A.Toson--Smart_Home_Project_Q9
 * @brief   This file contains interfacing information of LED Module.
 * @version 1.0
 * @date    16-6-2021
 *
 * @copyright Copyright (c) 2021
 *
 */
 
 
/*Header file guard*/
#ifndef HLED_INTERFACE_H_
#define HLED_INTERFACE_H_
/************************************************************************/
/*									LED Macros                          */
/************************************************************************/

/*LED ports*/
#define HLED_PORT			(PORTC)

/*LED pins*/
#define HLED_LOGIN		(PIN2)
#define HLED_BLOCK		(PIN7)

/************************************************************************/
/*                           Functions' prototypes                      */
/************************************************************************/


//	Function Description : Initialize the pin as an output pin to connect the led.
void LED_vInit(u8_t portname,u8_t pinnumber);


//	Function Description : Turn on the led connected to the given pin and port.
void LED_vTurnOn(u8_t portname,u8_t pinnumber);//


//	Function Description : Turn off the led connected to the given pin and port.
void LED_vTurnOff(u8_t portname,u8_t pinnumber);


//	Function Description : Toggle the led connected to the given pin and port.
void LED_vToggle(u8_t portname,u8_t pinnumber);//


//	Function Description : Returns 0 if the led connected to the given port and pin is off or return 1 if it was on.
u8_t LED_u8ReadStatus(u8_t portname,u8_t pinnumber);

#endif /* HLED_INTERFACE_H_ */