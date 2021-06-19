/**
 * @file    UART.c
 * @author  Aya-A.Toson--Smart_Home_Project_Q9
 * @brief   This file contains logical implementations of UART Module.
 * @version 1.0
 * @date    16-6-2021
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "STD_Types.h"
#include "UART.h"
#include "util/delay.h"
uint8 compareString(uint8 arr1[10] , uint8 arr2[10])
{
	uint16 i=0;
	uint8 flag=0;
	while((arr2[i]!='\0'))
	{
		if(arr1[i]==arr2[i])
		{
			flag=1;
		}else{
			flag=0;
		}
		i++;
	}
	return flag ;
}
void Uart_init(uint32 BaudRate)
{
	UCSRB=(1<<RXEN)|(1<<TXEN);
	UCSRC=(1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);
	UBRRL=(uint8)(((F_CPU)/(16*BaudRate))-1);
}

void UART_send_byte( uint8 byte)
{
	while(!(UCSRA &(1<<UDRE))); // while shift register flag != 1 (not empty))
	UDR=byte;

}

void UART_send_string( uint8 *ptr)
{
	uint16 i=0;

	while(ptr[i] != '\0')
	{
		UART_send_byte(ptr[i]);
		i++;
	}
	UART_send_byte(ptr[i]);
}

uint8  UART_recieve_byte(void)
{
	while((UCSRA & (1<<RXC)) ==0);

	return UDR ;


}
void  UART_recieve_string(uint8 * ptr)
{
	uint16 i=0;
	ptr[i]=UART_recieve_byte();
	while(ptr[i] !='#')
	{
		i++;
		ptr[i]=UART_recieve_byte();

	}
	ptr[i]='\0';


}

