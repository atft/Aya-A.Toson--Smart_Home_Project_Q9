
/**
 * @file    HKPD_private.h
 * @author  Aya-A.Toson--Smart_Home_Project_Q9
 * @brief   This file contains private information of KPD Module.
 * @version 1.0
 * @date    16-6-2021
 *
 * @copyright Copyright (c) 2021
 *
 */
 
/*Header file guard*/
#ifndef HKPD_PRIVATE_H_
#define HKPD_PRIVATE_H_

/************************************************************************/
/*                              KPD Pins                                */
/************************************************************************/

/*KPD DIO ports*/
#define HKPD_COLS_PORT   (PORTD)
#define HKPD_ROWS_PORT   (PORTD)

/*KPD columns' pins*/
#define HKPD_COL0_PIN    (PIN0)
#define HKPD_COL1_PIN    (PIN1)
#define HKPD_COL2_PIN    (PIN2)

/*KPD rows' pins*/
#define HKPD_ROW0_PIN    (PIN3)
#define HKPD_ROW1_PIN    (PIN4)
#define HKPD_ROW2_PIN    (PIN5)
#define HKPD_ROW3_PIN    (PIN6)

#endif /* HKPD_PRIVATE_H_ */