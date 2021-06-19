/**
 * @file    LSTD_MESSAGES.h
 * @author  Aya-A.Toson--Smart_Home_Project_Q9
 * @brief   This header file contains communication messages.
 * @version 1.0
 * @date    16/6/2021
 *
 * @copyright Copyright (c) 2021
 *
 */
 
/*Header file guard*/
#ifndef STD_MESSAGES_H_
#define STD_MESSAGES_H_

//Setting status commands
#define ROOM1_STATUS    0x11
#define ROOM2_STATUS    0x12
#define ROOM3_STATUS    0x13
#define ROOM4_STATUS    0x14
#define TV_STATUS 		0x15
#define AIR_COND_STATUS 0x16

//Setting on commands
#define ROOM1_TURN_ON    0x21
#define ROOM2_TURN_ON    0x22
#define ROOM3_TURN_ON    0x23
#define ROOM4_TURN_ON    0x24
#define TV_TURN_ON 		 0x25
#define AIR_COND_TURN_ON 0x26

//Setting off commands
#define ROOM1_TURN_OFF    0x31
#define ROOM2_TURN_OFF    0x32
#define ROOM3_TURN_OFF    0x33
#define ROOM4_TURN_OFF    0x34
#define TV_TURN_OFF 	  0x35
#define AIR_COND_TURN_OFF 0x36

//Setting temperature command
#define SET_TEMPERATURE 0x40

//Setting defaults
#define DEFAULT_ACK    0xFF
#define DEMAND_RESPONSE 0xFF

//Setting on/off status commands
#define ON_STATUS   0x01
#define OFF_STATUS  0x00

#endif