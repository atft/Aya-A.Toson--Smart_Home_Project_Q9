
/**
 * @file    MEEPROM_program.c
 * @author  Aya-A.Toson--Smart_Home_Project_Q9
 * @brief   This file contains logical implementations of EEPROM Module.
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
#include "MEEPROM_interface.h"
#include <avr/io.h>

/************************************************************************/
/*                          Functions' definitions                      */
/************************************************************************/
u8_t EEPROM_ui8ReadByteFromAddress(const u16_t u16Address)
{
	/* Wait for completion of previous write */
	while (((EECR & (1 << EEWE))>>EEWE)==1)
	;
	/* Set up address register */
	EEAR = u16Address;
	/* Start EEPROM read by writing EERE */
	EECR |= (1 << EERE);
	/* Return data from data register */
	return EEDR;
}

void EEPROM_vReadBlockFromAddress(const u16_t uiAddress, u8_t* dist,const u16_t size)
{
	/* Wait for completion of previous write */
	while (((EECR & (1 << EEWE))>>EEWE)==1)
	;

	u16_t counter = 0;//the counter of bytes that are read

	while (counter < size) //loop until move all bytes to the given array
	{
		/* Set up address register */
		EEAR = uiAddress + counter;
		/* Start EEPROM read by writing EERE */
		EECR |= (1 << EERE);
		/* move data from data register to the array */
		*(dist + counter) = EEDR;

		counter++;//increase the bytes counter
	}
}

void EEPROM_vWriteByteToAddress(const u16_t uiAddress, const u8_t uiData)
{

	/* Wait for completion of previous write process*/
	while ( ( (EECR & (1 << EEWE) ) >>EEWE ) == 1)
	;
	/* Set up address register */
	EEAR = uiAddress;

	/* Read the byte in the address of EEAR */
	EECR |= (1 << EERE);
	if (EEDR != uiData)//compare the value read to the value to be written
	{//if they are not equal then write the data 
		EEDR = uiData;//move the data to EEDR

		/* Write logical one to EEMWE */
		EECR |= (1 << EEMWE);
		/* Start EEPROM write by setting EEWE */
		EECR |= (1 << EEWE);
	}
	else
	{

	}

}

void EEPROM_vWriteBlockToAddress(const u16_t uiAddress, const u8_t* uiData,const u16_t size)
{
	u16_t counter = 0;//Bytes write counter
	while (counter < size)
	{
		/* Wait for completion of previous write process*/
		while (( (EECR & (1 << EEWE) ) >>EEWE ) == 1)
		;
		/* Set up address register */
		EEAR = uiAddress + counter;

		/* Read the byte in the address of EEAR */
		EECR |= (1 << EERE);
		if (EEDR != (*(uiData + counter)))//compare the value read to the value to be written
		{//if they are not equal then write the data 
			EEDR = *(uiData + counter);//move the data to EEDR

			/* Write logical one to EEMWE */
			EECR |= (1 << EEMWE);
			/* Start EEPROM write by setting EEWE */
			EECR |= (1 << EEWE);
		}
		else
		{

		}
		counter++;//increase bytes counter
	}
}
