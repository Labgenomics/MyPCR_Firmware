/****************************************************
	FileName 	:	GlobalTypeVars.h
	Date	 	:	2012.08.11
	Author		:	Yeon June
****************************************************/

/** Duplicate check ********************************/
#ifndef __GLOBALTYPEVARS_H__
#define __GLOBALTYPEVARS_H__

/** Includes ***************************************/
#include "./DEFINE/GenericTypeDefs.h"
#include "./DEFINE/UserDefs.h"

/** For Timer Flags ********************************/
extern UINT T100MS_Counter;
//KJD181124
extern UINT tmpT100MS_Counter;
extern UINT T1S_Counter;
extern BOOL T100MS_Flag;
extern BOOL T1S_Flag;

/** Protect buffer *********************************/
extern unsigned char Rx_Buffer[];

/** State Variables ********************************/
extern unsigned char Prev_State;
extern unsigned char Cur_State;
extern unsigned char Cur_Command;

/** TempCtrl State **********************************/
extern unsigned char TempCtrl_State;

/** Counters ***************************************/
extern unsigned char Write_Count;

/** Temperature Variables **************************/
extern unsigned char LID_Temp_H;
extern unsigned char LID_Temp_L;
extern unsigned char Chamber_Temp_H;
extern unsigned char Chamber_Temp_L;
extern unsigned char Heatsink_Temp_H;
extern unsigned char Heatsink_Temp_L;

extern float Heater_Temper;
extern float Chamber_Temper;
extern float Heatsink_Temper;

extern float Pre_Chamber_Target;
extern float Chamber_Target;			//		..?
extern float Heater_Target;

extern float Het_Target_Temp;

extern unsigned char Chamber_Fan;		// neccessary change var name
extern unsigned char System_Fan;
extern BYTE Heater;

//KJD181123
extern float pre_convertTemp;
extern int Left_SecTime;
extern int Left_Sec_Total;


/** Flags *******************************************/
extern BOOL IsCoverCtrl;
extern BOOL IsChamberCtrl;
extern BOOL IsCoverHeated;
extern BOOL IsTargetArrived;
extern BOOL IsCompletePCR;
extern BOOL IsCoolingState;
extern BOOL IsRunning;

/** PID ..? *****************************************/
extern float Kp;			// neccessary change var name
extern float Ki;
extern float Kd;

/** Chamber Last Err & Integrals ********************/
extern float Chamber_LastErr;
extern float Chamber_LastIntegral;

/** PWM Dir  ************************************/
extern unsigned char PWM_Dir;

/** PWM High / Low **********************************/
extern BYTE PWM_H;
extern BYTE PWM_L;

/** Error Value *************************************/
extern unsigned char Fatal_Error;

/** Left Time Variable ******************************/
extern unsigned char Left_Time_H;
extern unsigned char Left_Time_L;
extern unsigned char Left_TotalTime_H;
extern unsigned char Left_TotalTime_L;

/** Current Task Line Number = CurTaskLineNo ********/
extern unsigned char Cur_Task_Line;

#endif

