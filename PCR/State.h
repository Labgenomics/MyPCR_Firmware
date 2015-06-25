/****************************************************
*	FileName 	:	State.h
*	Date	 	:	2012.08.12
*	Author		:	Yeon June
****************************************************/

/** Duplicate check ********************************/
#ifndef __STATE_H__
#define __STATE_H__

/** Prototypes *************************************/
void Process_Ready(void);
void Process_Run(void);
void Process_PCREnd(void);
void Process_Stop(void);
void Process_TaskWrite(void);
void Process_Error(void);
void Process_ParamWrite(void);

#endif	/** End of __STATE_H__	********************/

