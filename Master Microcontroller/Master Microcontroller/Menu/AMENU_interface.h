
/**
 * @file    AMENU_interface.h
 * @author  Aya-A.Toson--Smart_Home_Project_Q9
 * @brief   This file contains interfacing information of Menu Module.
 * @version 1.0
 * @date    16-6-2021
 *
 * @copyright Copyright (c) 2021
 *
 */

/*Header file guard*/ 
#ifndef AMENU_INTERFACE_H_
#define AMENU_INTERFACE_H_


/************************************************************************/
/*                           Functions' prototypes                      */
/************************************************************************/


//	Function Description : Compare two arrays of bytes and return True in case they are identical and return false in case they are different .
u8_t ui8ComparePass(const u8_t* pass1,const u8_t* pass2,const u8_t size);


//	Function Description : Show the sub menus of room 1 ,room 2 ,room 3,room 4 , tv
void vMenuOption(const u8_t u8SelectedRoom,const u8_t u8LoginMode);


//	Function Description : Wait the user to press key then return the key pressed or return (NOT_PRESSED = 0xFF) in case of timeout.
u8_t u8GetKeyPressed(const u8_t u8LoginMode);

#endif /* AMENU_INTERFACE_H_ */