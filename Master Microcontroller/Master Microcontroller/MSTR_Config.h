#ifndef MASTER_CONFIG_H_
#define MASTER_CONFIG_H_


#define NOT_STORED   0xFF
#define NOT_SET 0xFF

#define BLOCK_MODE_TIME		(u32_t)20000
#define PASS_SHOW_TIME		(u16_t)300
#define DEGREES_SYMBOL		(u8_t)0xDF

/*********************************** PIN Configuration ***********************************/
#define PASS_SIZE        (u8_t)4
#define TRIES_ALLOWED    (u8_t)3
#define PASS_HIDE		 (u8_t)'*'
#define ASCII_ZERO       (u8_t)'0'

#define PASS_NOT_SET (u8_t)0xFF
#define PASS_SET     (u8_t)0x01

#define PASS_STATUS_ADDRESS		  (u16_t)0X100
#define EEPROM_PASS_ADDRESS       (u16_t)0X101
#define LOGIN_BLOCKED_ADDRESS     (u16_t)0X105
/*****************************************************************************************/

/************************************   Login configurations *****************************/
#define LOGOUT  (u8_t)0
#define LOGIN   (u8_t)1
/*****************************************************************************************/

/************************************   Logic values *************************************/
#define FALSE   (u8_t)0
#define TRUE    (u8_t)1
/*****************************************************************************************/
#define CHECK_LOGIN_MODE        (u8_t)'0'

#define SELECT_ROOM1            (u8_t)'1'
#define SELECT_ROOM2            (u8_t)'2'
#define SELECT_ROOM3            (u8_t)'3'
#define MORE_OPTION			    (u8_t)'4'

#define SELECT_ROOM4	        (u8_t)'1'
#define SELECT_TV               (u8_t)'2'
#define SELECT_AIR_CONDITIONING (u8_t)'3'
#define RET_OPTION			    (u8_t)'4'

#define SELECT_SET_TEMPERATURE  (u8_t)'1'
#define SELECT_AIR_COND_CTRL    (u8_t)'2'
#define SELECT_AIR_COND_RET     (u8_t)'0'
/*****************************************************************************************/

/****************************   number of ticks to run timeout ***************************/
#define LOGIN_TIMEOUT (u16_t)5000
/*****************************************************************************************/

/****************************   Show menu codes  *****************************************/
#define MAIN_MENU            (u8_t)1
#define MORE_MENU            (u8_t)2
#define ROOM1_MENU           (u8_t)3
#define ROOM2_MENU           (u8_t)4
#define ROOM3_MENU           (u8_t)5
#define ROOM4_MENU           (u8_t)6
#define TV_MENU              (u8_t)7
#define AIRCONDITIONING_MENU (u8_t)8
#define AIRCOND_CTRL_MENU    (u8_t)9
#define TEMPERATURE_MENU     (u8_t)10
/*****************************************************************************************/

#endif /* MASTER_CONFIG_H_ */