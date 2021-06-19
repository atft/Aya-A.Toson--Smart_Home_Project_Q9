
/**
 * @file    MTIMER_program.c
 * @author  Aya-A.Toson--Smart_Home_Project_Q9
 * @brief   This file contains logical implementations of Timer Module.
 * @version 1.0
 * @date    16-6-2021
 *
 * @copyright Copyright (c) 2021
 *
 */
/************************************************************************/
/*                              Includes                                */
/************************************************************************/
#include "LBIT_MATH.h"
#include "LSTD_Types.h"
#include "MTIMER_interface.h"

#include <avr/io.h>
#include <avr/interrupt.h>

/************************************************************************/
/*                          Functions' definitions                      */
/************************************************************************/
void timer0_initializeCTC(void)
{
	//Config OCR0
	//OCR0 = the value to compare with
	OCR0 = 78; //to achieve tick equal to 10 msec
	
	//Set timer mode
	//Set the mode as Compare match
	SET_BIT(TCCR0, WGM01);
	CLEAR_BIT(TCCR0, WGM00);
	
	//Configure clock
	//set as clk/1024
	SET_BIT(TCCR0, CS00);
	CLEAR_BIT(TCCR0, CS01);
	SET_BIT(TCCR0, CS02);
	
	//Enable global interrupts
	sei();
	
	//Enable timer 0 interrupt for compare match
	SET_BIT(TIMSK, OCIE0);
}

void timer0_stop(void)
{
	//disable the clock to stop the counter
	CLEAR_BIT(TCCR0, CS00);
	CLEAR_BIT(TCCR0, CS01);
	CLEAR_BIT(TCCR0, CS02);
}
void timer_initializefastpwm(void)
{
	//Config OCR0
	//OCR0 = the value to compare with
	OCR0 = 128;
	
	//Set timer mode
	//adjust fast pulse width modulation mode
	SET_BIT(TCCR0, WGM00); 
	SET_BIT(TCCR0, WGM01);
	
	//Enable global interrupts
	sei();
	
	SET_BIT(TCCR0, COM01); //adjust non inverting mode
	
	//Enable timer0 interrupt for overflow mode
	SET_BIT(TIMSK,TOIE0);
	
	//Configure clock
	//set as clk/1024
	SET_BIT(TCCR0, CS00);
	CLEAR_BIT(TCCR0, CS01);
	SET_BIT(TCCR0, CS02);
}
void change_dutycycle(f64_t duty)
{
	OCR0 = (duty / 100) * 256;//Set the OCR0 depending on the duty percentage
}

