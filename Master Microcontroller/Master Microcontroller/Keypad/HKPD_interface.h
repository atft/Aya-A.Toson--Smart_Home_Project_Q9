
/**
 * @file    HKPD_interface.h
 * @author  Aya-A.Toson--Smart_Home_Project_Q9
 * @brief   This file contains interfacing information of KPD Module.
 * @version 1.0
 * @date    16-6-2021
 *
 * @copyright Copyright (c) 2021
 *
 */
 
/*Header file guard*/
#ifndef HKPD_INTERFACE_H_
#define HKPD_INTERFACE_H_

/************************************************************************/
/*                           Interfacing macros                         */
/************************************************************************/
#define NOT_PRESSED			 (0xff)

/************************************************************************/
/*                           Functions' prototypes                      */
/************************************************************************/

/*This function is used in initializing the KPD*/
void hkpd_init(void);

/*This function is used to get the pressed key of the KPD*/
u8_t hkpd_getPressed(void);

#endif /* HKPD_INTERFACE_H_ */