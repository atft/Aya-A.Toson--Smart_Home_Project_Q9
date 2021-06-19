
/**
 * @file    UART.h
 * @author  Aya-A.Toson--Smart_Home_Project_Q9
 * @brief   This file contains interfacing information of UART Module.
 * @version 1.0
 * @date    16-6-2021
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef UART_H_
#define UART_H_

#include <avr/io.h>

void Uart_init(uint32 BaudRate);
void UART_send_byte( uint8 byte);
void UART_send_string( uint8 *ptr);
uint8 UART_recieve_byte(void);
void UART_recieve_string( uint8 *ptr);
uint8 compareString(uint8 arr1[10] ,uint8 arr2[10]);

#endif /* UART_H_ */
