
/**
 * @file    TIMER_interface.h
 * @author  Aya-A.Toson--Smart_Home_Project_Q9
 * @brief   This file contains interfacing information of Timer Module.
 * @version 1.0
 * @date    16-6-2021
 *
 * @copyright Copyright (c) 2021
 *
 */
 
/*Header file guard*/ 
#ifndef MTIMER_INTERFACE_H_
#define MTIMER_INTERFACE_H_


/************************************************************************/
/*                           Functions' prototypes                      */
/************************************************************************/

//	Function Description : Initialize and start the timer0 for compare match.
void timer0_initializeCTC(void);


//	Function Description : Stop timer0.
void timer0_stop(void);


//	Function Description : Initialize timer0 for FastPWM mode.
void timer_initializefastpwm(void);


//	Function Description : Set duty cycle to the given duty percentage.
void change_dutycycle(f64_t duty);


#endif /* TIMER_DRIVER_H_ */
