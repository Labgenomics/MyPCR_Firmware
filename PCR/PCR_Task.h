/***************************************************
*	FileName 	:	PCR_Task.h
*	Date	 	:	2012.08.11
*	Author		:	Yeon June
****************************************************/

/** Duplicate check ********************************/
#ifndef __PCR_TASK_H__
#define __PCR_TASK_H__

/** Prototypes *************************************/
void PCR_Task(void);		//	Calling Functions related to PCR_Task.

void Buffer_Copy(void);		//	Buffer Copy
void Pre_Process(void);		//	Command Setting

void Task_Write(void);		// Command TaskWrite
void Task_Read(void);

void Calc_Time(void);		//	Calculation Time

void Param_Write(void);		//	Command ParamWrite

void Task_Control(void);	// Read the stored task and execute task.
							// Called at every 1sec.

void PCR_End(void);			// process PCR end

void Reset_All_Values(void);// Reset All Values

void Find_PID_Params(void);	// Find PID Params

int Get_Action_Number(int number);	// Get Action Number

void Check_State(void);		// Check Machine State & Change the State for after task control

void Post_Process(void);	//	Set Tx Message & Set Status for State

#endif	/** End of __PCR_TASK_H__ *****************/

