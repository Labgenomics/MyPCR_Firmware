/****************************************************
*	FileName 	:	GlobalTypeVars.c
*	Date	 	:	2012.08.11
*	Author		:	Yeon June
****************************************************/

/** Includes ***************************************/
#include "./DEFINE/GlobalTypeVars.h"

/** Define Extern Variables ********************/
UINT T100MS_Counter = 0x00;
//KJD181124
UINT tmpT100MS_Counter = 0x00;
UINT T1S_Counter = 0x00;
BOOL T100MS_Flag = FALSE;
BOOL T1S_Flag = FALSE;

unsigned char Rx_Buffer[RX_BUFSIZE];

unsigned char Write_Count = -1;

unsigned char Prev_State = 0x00;
unsigned char Cur_State = STATE_READY;
unsigned char Cur_Command = CMD_NOP;
unsigned char TempCtrl_State = 0x00;

unsigned char LID_Temp_H = 0x00;
unsigned char LID_Temp_L = 0x00;
unsigned char Chamber_Temp_H = 0x00;
unsigned char Chamber_Temp_L = 0x00;
unsigned char Heatsink_Temp_H = 0x00;
unsigned char Heatsink_Temp_L = 0x00;

float Heater_Temper = 0.;						// Tl : Temperature of Lid Heater
float Chamber_Temper = 0.;						// Tc : T of chamber = Tcc (Current chamber Temperature)
float Heatsink_Temper = 0.;						// Th : T of Heatsink

float Pre_Chamber_Target = TARGET_TEMP_INIT;
float Chamber_Target = TARGET_TEMP_INIT;		// Tct : T of chamber target
float Heater_Target = 0.;						

float Het_Target_Temp = 0.;						

unsigned char Chamber_Fan = 0x00;
unsigned char System_Fan = 0x00;
BYTE Heater = 0x00;

//KJD181123
float pre_convertTemp = 0.;
int Left_Sec_Total = 0;


BOOL IsCoverCtrl = FALSE;
BOOL IsChamberCtrl = FALSE;
BOOL IsCoverHeated = FALSE;
BOOL IsTargetArrived = FALSE;
BOOL IsCompletePCR = FALSE;
BOOL IsCoolingState = FALSE;
BOOL IsRunning = FALSE;

float Kp = 0;
float Ki = 0;
float Kd = 0;

float Chamber_LastErr = 0;
float Chamber_LastIntegral = 0;

unsigned char PWM_Dir = 0;

BYTE PWM_H = 0xFF;
BYTE PWM_L = 0xFF;

unsigned char Fatal_Error = 0;

unsigned char Left_Time_H = 0;
unsigned char Left_Time_L = 0;
unsigned char Left_TotalTime_H = 0;
unsigned char Left_TotalTime_L = 0;

unsigned char Cur_Task_Line = 0;