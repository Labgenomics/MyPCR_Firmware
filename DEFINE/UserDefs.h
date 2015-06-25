/****************************************************
 FileName 	:   UserDefs.h
 Date		:	2012.07.27
 Author		:	Yeon June	 
****************************************************/

/** Duplicate check ********************************/
#ifndef __USERDEFS_H__
#define __USERDEFS_H__

/** Includes ***************************************/
#include "./DEFINE/GenericTypeDefs.h"

#define RX_BUFSIZE		64		// Buffer Size
#define TX_BUFSIZE		64
#define RX_PARAM_SIZE	4
#define TX_PARAM_SIZE	4

//#define TESTER

// YJ 130202
#define FIRMWARE_VERSION	0x03

typedef enum _RXINDEX 			//	Rx Buffer matching at index
{								//  Used in PCR_Task.c
	RX_CMD = 0x00,
	RX_ACTNO,
	RX_START_TEMP = 0x01,
	RX_TEMP,
	RX_END_TEMP = 0x02,
	RX_TIMEH,
	RX_PARAM_P = 0x03,
	RX_TIMEL,
	RX_LIDTEMP,
	RX_REQLINE,
	RX_PARAM_I,
	RX_PARAM_D = 0x0B
} RXINDEX;

typedef enum _TXINDEX			//	Tx Buffer matching at index
{
	TX_STATE = 0x00,			//	0	
	TX_RES,						//	1	My Response
	TX_CURRENTACTNO,			//	2	Current action number
	TX_CURRENTLOOP,				//	3	Current Loop
	TX_TOTALACTNO,				//	4	Total Action number
	TX_KP,						//	5
	TX_KI,						//	6
	TX_KD,						//	7
	TX_LEFTTIMEH,				//	8	Total left time
	TX_LEFTTIMEL,				//	9
	TX_LEFTSECTIMEH,			//	10	Left time per Line
	TX_LEFTSECTIMEL,			//	11
	TX_LIDTEMPH,				//	12	Lid Heater temp
	TX_LIDTEMPL,				//	13
	TX_CHMTEMPH,				//	14	Chamber temp
	TX_CHMTEMPL,				//	15
	TX_PWMH,					//	16	PWM Duration ( 0x00 ~ 0x3F )
	TX_PWML,					//	17
	TX_PWMDIR,					//	18	PWM Direction ( +, - )
	TX_LABEL,					//	19	PCR Task line
	TX_TEMP,					//	20	Target temp
	TX_TIMEH,					//	21	Left time
	TX_TIMEL,					//	22
	TX_LIDTEMP,					//	23	LID Target temp
	TX_REQLINE,					//	24	Task line number required by host
	TX_ERROR,					//	25	for Error Report
	TX_CUR_OPR,					//	26	Current operation
	TX_SINKTEMPH,				//	27	Heatsink temp
	TX_SINKTEMPL,				//	28	Heatsink temp
	TX_KP_1,					//	29
	TX_KI_1 = 33,				//	33
	TX_KD_1 = 37,				//	37
								//	41, 42, 43 is Serial Number from Bluetooth Ver
	TX_VERSION = 44				//	44	Firmware version	// YJ 130202

} TXINDEX;

typedef enum _STATE				//	Device State.
{								//  Used in PCR_Task.c
	STATE_READY = 0x01,
	STATE_RUN,
	STATE_PCREND,
	STATE_STOP,
	STATE_TASK_WRITE,
	STATE_ERROR,
	STATE_PARAM_WRITE
} STATE;

typedef enum _COMMAND			//	Rx_Buffer[0] = Set Command
{								//  Used in PCR_Task.c
	CMD_NOP = 0x00,
	CMD_TASK_WRITE,
	CMD_TASK_END,
	CMD_GO,
	CMD_STOP,
	CMD_PARAM_WRITE,
	CMD_PARAM_END,
	CMD_BOOTLOADER = 0x55
} COMMAND;

// Constants about action format.
// Action format : 4B
// [1B : Action Number] [1B : Set Temperature in cel. deg. -128~127] [ 2B : Hold time in sec.]
// AF : Used PCR_Task.c

#define AF_GOTO		250
#define AF_END		251

// Pause Code : 0xF000
#define AF_PAUSE	0xF000
#define AF_PAUSE_H	0xF0
#define AF_PAUSE_L	0x00

//	Line Info Structure
typedef struct _ACTION
{
	unsigned char Label;
	unsigned char Temp;
	UINT Time;
} Action;

//	Parameter Info Structure
typedef struct _PIDPARAM
{
	unsigned char Start_Temp;
	unsigned char Target_Temp;
	float Param_P;
	float Param_I;
	float Param_D;
} PID_Param;

//	Differential between Target and CurrentTemp ? 
#define TARGETTEMP_DELTA			5.

// Heater & Fan duration
#define LID_HEATER_DURATION			10
#define CHM_FAN_DURATION			10
#define SYS_FAN_DURATION			10

//	Chamber & System Temperature Duration
#define CHMFAN_TEMP_DURATION_0		20.
#define CHMFAN_TEMP_DURATION_50		30.
#define CHMFAN_TEMP_DURATION_100	40.

#define SYSFAN_TEMP_DURATION_0		30.
#define SYSFAN_TEMP_DURATION_50		40.
#define SYSFAN_TEMP_DURATION_100	50.

#define HEATEROFF_TEMP				10.

//	Temperature Limitness
#define	LID_TEMP_LIMIT				120.
#define CHM_TEMP_LIMIT				100.
#define SINK_TEMP_LIMIT				80.

// TimeOut Value
#define ARRIVAL_TIMEOUT			20000	//	YJ

// Refrigerator Temperature
#define REFRIGERATOR_TEMP		10.

// Temperature Sampling Count
#define SAMPLING_COUNT			0x05

// Select Temperature Menu
#define HEATER_TEMP				0x01
#define CHAMBER_TEMP			0x02
#define HEATSINK_TEMP			0x03

// Select Sensor Menu ( Refer HardwareProfile - PICDEM FSUSB.h File in ADC Section )
#define SENSOR_HEATER			(0b00000000)
#define SENSOR_CHAMBER			(0b00000100)
#define SENSOR_HEATSINK			(0b00010000)

#define TARGET_TEMP_INIT		25.

typedef enum _OPRSTATE
{
	READY_INIT = 0x00,
	READY_COMPLETE,
	READY_INCOMPLETE,
	RUN_REFRIGERATOR
} OPR_STATE;

// Chamber Duration PWM_MAX
#define CHAMBER_PWM_MAX			1023.0

// Initalize TimeOut Count
#define TIMEOUT_COUNT			5000

// Response List
#define	RES_NONE				0x00
#define	RES_BUSY				0x01
#define	RES_TASK_WR_DONE		0x02
#define	RES_TASK_ER_DONE		0x03
#define	RES_GO_DONE				0x04
#define	RES_STOP_DONE			0x05
#define	RES_PCR_END				0x06

#endif


