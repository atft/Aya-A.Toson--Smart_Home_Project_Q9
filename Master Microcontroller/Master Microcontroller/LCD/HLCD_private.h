
/**
 * @file    HLCD_private.h
 * @author  Aya-A.Toson--Smart_Home_Project_Q9
 * @brief   This file contains private information of LCD Module.
 * @version 1.0
 * @date    16-6-2021
 *
 * @copyright Copyright (c) 2021
 *
 */
 
 
/*Header file guard*/
#ifndef HLCD_PRIVATE_H_
#define HLCD_PRIVATE_H_

/************************************************************************/
/*                            LCD private data                          */
/************************************************************************/

/*LCD ports*/
#define HLCD_CONTROL_PORT  (PORTB)
#define HLCD_DATA_PORT     (PORTA)

/*LCD control pins*/
#define HLCD_RS            (PIN1)
#define HLCD_RW            (PIN2)
#define HLCD_EN            (PIN3)

/*LCD data pins*/
#define HLCD_DB0           (PIN0)
#define HLCD_DB1           (PIN1)
#define HLCD_DB2           (PIN2)
#define HLCD_DB3           (PIN3)
#define HLCD_DB4           (PIN4)
#define HLCD_DB5           (PIN5)
#define HLCD_DB6           (PIN6)
#define HLCD_DB7           (PIN7)

#endif /* HLCD_PRIVATE_H_ */