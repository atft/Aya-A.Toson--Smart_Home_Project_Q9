/**
 * @file    MSPI.h
 * @author  Aya-A.Toson--Smart_Home_Project_Q9
 * @brief   This file contains interfacing information of SPI Module.
 * @version 1.0
 * @date    16-6-2021
 *
 * @copyright Copyright (c) 2021
 *
 */
 
/*Header file guard*/ 
#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_


/************************************************************************/
/*                           Interfacing macros                         */
/************************************************************************/

#define SPI_SCK  7
#define SPI_MISO 6
#define SPI_MOSI 5
#define SPI_SS   4

/************************************************************************/
/*                           Functions' prototypes                      */
/************************************************************************/


//	Function Description : Initialize the master.
void SPI_vInitMaster (void);


//	Function Description : Initialize the slave.
void SPI_vInitSlave (void);


//	Function Description : Send data in case of master or receive data and send response in case of slave.
u8_t SPI_ui8TransmitRecive (u8_t data);

#endif /* SPI_INTERFACE_H_ */
