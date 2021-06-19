
/**
 * @file    HLED_program.c
 * @author  Aya-A.Toson--Smart_Home_Project_Q9
 * @brief   This file contains logical implementations of LED Module.
 * @version 1.0
 * @date    16-6-2021
 *
 * @copyright Copyright (c) 2021
 *
 */
 
/************************************************************************/
/*							       Includes			                    */
/************************************************************************/
#include "LBIT_MATH.h"
#include "LSTD_TYPES.h"
#include "MDIO_interface.h"
#include "HLED_interface.h"


/************************************************************************/
/*                          Functions' definitions                      */
/************************************************************************/
void LED_vInit(u8_t portname,u8_t pinnumber)
{
	mdio_setPinStatus(portname,pinnumber,OUTPUT);//Set the given pin in the given port as an output
}
void LED_vTurnOn(u8_t portname,u8_t pinnumber)
{
	SET_BIT(portname,pinnumber);//Set the given pin in the given port to one(on)
}
void LED_vTurnOff(u8_t portname,u8_t pinnumber)
{
	CLEAR_BIT(portname,pinnumber);//Set the given pin in the given port to zero(off)
}
void LED_vToggle(u8_t portname,u8_t pinnumber)
{
	TOGGLE_BIT(portname,pinnumber);//Set the given pin in the given port to zero if it is one or set it to one if it is zero
}
u8_t LED_u8ReadStatus(u8_t portname,u8_t pinnumber)
{
	return mdio_getPinValue(portname,pinnumber);//return the current status of the given pin
}
