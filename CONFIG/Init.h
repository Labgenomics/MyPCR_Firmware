/***************************************************
 *	FileName 	:   Init.h
 *	Date		:	2012.07.27
 *	Author		:	Yeon June 
****************************************************/

/** Duplicate check ********************************/
#ifndef __INIT_H__
#define __INIT_H__

/** Prototypes *************************************/
void Init(void);				//	Called all init functions
void InitializeSystem(void);	//	Initialize USB
void InitializeDevice(void);	// 	Initialize Device Port & State
void InitializeUser(void);		//	For User Initialize
void MainLooper(void);			//	Infinity called in main.c / Called USB, PCR Task

#endif	/** End of __INIT_H__ *********************/

