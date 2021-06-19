
/**
 * @file    HLCD_interface.h
 * @author  Aya-A.Toson--Smart_Home_Project_Q9
 * @brief   This file contains interfacing information of LCD Module.
 * @version 1.0
 * @date    16-6-2021
 *
 * @copyright Copyright (c) 2021
 *
 */
 
/*Header file guard*/
#ifndef HLCD_INTERFACE_H_
#define HLCD_INTERFACE_H_

/************************************************************************/
/*                           Interfacing macros                         */
/************************************************************************/


/************************************************************************/
/*                           Functions' prototypes                      */
/************************************************************************/

/*This function is used in initializing the LCD module*/
void hlcd_init(void);

/*This function is used in writing a character over LCD*/
void hlcd_writeChar(u8_t au8_charData);

/*This function is used in writing a string of characters over LCD*/
void hlcd_writeString(u8_t* pu8_stringData);

/*This function is used in clearing LCD*/
void hlcd_clearLCD(void);

/*This function is used in setting cursor*/
void hlcd_resetCursor(void);

/*This function is used in setting cursor*/
void hlcd_setCursor(u8_t au8_row , u8_t au8_col);



#endif /* HLCD_INTERFACE_H_ */