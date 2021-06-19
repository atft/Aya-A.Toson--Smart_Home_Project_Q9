
/**
 * @file    MEEPROM_interface.h
 * @author  Aya-A.Toson--Smart_Home_Project_Q9
 * @brief   This file contains interfacing information of EEPROM Module.
 * @version 1.0
 * @date    16-6-2021
 *
 * @copyright Copyright (c) 2021
 *
 */
 
/*Header file guard*/ 
#ifndef HEADERS_EEPROM_H_
#define HEADERS_EEPROM_H_

/************************************************************************/
/*                           Functions' prototypes                      */
/************************************************************************/

//	Function Description :  Read one byte from the given  address.
u8_t EEPROM_ui8ReadByteFromAddress(const u16_t u16Address);


//	Function Description : Read block of bytes of the given size (size) and save the result to given array(dist array).
void EEPROM_vReadBlockFromAddress(const u16_t u16Address, u8_t* dist,const u16_t size);


//	Function Description : Write one byte to given address.
void EEPROM_vWriteByteToAddress(const u16_t u16Address, const u8_t u8Data);


//	Function Description : Write block of bytes  of the given size (size) to EEPROM at the given address(u16Address) from the given array (u8Data).
void EEPROM_vWriteBlockToAddress(const u16_t u16Address, const u8_t* u8Data,const u16_t size);

#endif /* HEADERS_EEPROM_H_ */
