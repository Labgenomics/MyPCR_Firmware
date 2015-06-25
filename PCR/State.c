/****************************************************
*	FileName 	:	State.c
*	Date	 	:	2012.08.12
*	Author		:	Yeon June
****************************************************/

/** Includes ***************************************/
#include "HardwareProfile.h"
#include "./CONFIG/Compiler.h"
#include "./DEFINE/GlobalTypeVars.h"
#include "./DEFINE/UserDefs.h"
#include "./PCR/State.h"
#include "./PCR/PCR_Task.h"
#include "./PCR/Temp_Ctrl.h"

/***************************************************
 * Function:        void Process_Ready(void)
 *
 * OverView:		If device state is Ready, Called this function.
 *
 * Note:			at Check_State() function in PCR_Task.c
 ***************************************************/
void Process_Ready(void)
{
	switch(Cur_Command)
	{
		case CMD_TASK_WRITE:
			Cur_State = STATE_TASK_WRITE;
			break;
		case CMD_GO:
			mLED_R_Off();
			Fatal_Error = 0;		// Initialize Error Value
			TempCtrl_State = 0;		
			Init_Temp_Control();	// Initialize PWM & values for Control Temperature
			Cur_State = STATE_RUN;
			break;
		case CMD_PARAM_WRITE:
			Cur_State = STATE_PARAM_WRITE;
			Write_Count = 0;
			break;
		case CMD_STOP:
			Cur_State = STATE_READY;
			break;
	}
}

/***************************************************
 * Function:        void Process_Run(void)
 *
 * OverView:		If device state is Run, Called this function.
 *
 * Note:			at Check_State() function in PCR_Task.c
 ***************************************************/
void Process_Run(void)
{
	if( Cur_Command == CMD_STOP )
	{
		Cur_State = STATE_STOP;
	}
}

/***************************************************
 * Function:        void Process_PCREnd(void)
 *
 * OverView:		If device state is finished PCR, Called this function.
 *
 * Note:			at Check_State() function in PCR_Task.c
 ***************************************************/
void Process_PCREnd(void)
{
	Cur_State = STATE_READY;
}

/***************************************************
 * Function:        void Process_Stop(void)
 *
 * OverView:		If device state is Stop, Called this function.
 *
 * Note:			at Check_State() function in PCR_Task.c
 ***************************************************/
void Process_Stop(void)
{
	mLED_R_On();		// Red LED On
	mLED_B_Off();		// Blue LED Off
}

/***************************************************
 * Function:        void Process_TaskWrite(void)
 *
 * OverView:		If device state is Task writing, Called this function.
 *
 * Note:			at Check_State() function in PCR_Task.c
 ***************************************************/
void Process_TaskWrite(void)
{
	if( Cur_Command == CMD_TASK_END )
	{
		Cur_State = STATE_READY;
	}
}

/***************************************************
 * Function:        void Process_Error(void)
 *
 * OverView:		If device state is actived error, Called this function.
 *
 * Note:			at Check_State() function in PCR_Task.c
 ***************************************************/
void Process_Error(void)
{
	Cur_State = STATE_READY;
}

/***************************************************
 * Function:        void Process_ParamWrite(void)
 *
 * OverView:		If device state is param writing, Called this function.
 *
 * Note:			at Check_State() function in PCR_Task.c
 ***************************************************/
void Process_ParamWrite(void)
{
	if( Cur_Command == CMD_PARAM_END )
	{
		Cur_State = STATE_READY;
	}
}