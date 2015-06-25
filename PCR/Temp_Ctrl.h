/****************************************************
*	FileName 	:	Temp_Ctrl.h
*	Date	 	:	2012.08.11
*	Author		:	Yeon June
****************************************************/

/** Duplicate check ********************************/
#ifndef __TEMP_CTRL_H__
#define __TEMP_CTRL_H__

/** Prototypes *************************************/
//	Initialize & Temperature control routine.
void Init_Temp_Control(void);
void Temp_Control(void);
void Temp_Run_Routine(void);
void Temp_ErrorCheck(void);

//	Get ChamberFan Duration, Set ChamberFan Temperature.
void Get_ChamberFan_Duration(float temp);
void Set_ChamberFan_Duration(float duration);

//	Get SystemFan Duration, Set SystemFan Temperature.
void Get_SystemFan_Duration(float temp);
void Set_SystemFan_Duration(float duration);

//	Get Heater Duration, Set Heater Temperature.
void Get_Heater_Duration(float targetTemp, float curTemp, float *duration);
void Set_Heater_Duration(float duration);

//	Get Chamber Duration, Set Chamber Temperature.
void Get_Chamber_Duration(float temp);
void Set_Chamber_Duration(int dir, float duration);

#endif	/**	End of __TEMP_CTRL_H__ ****************/

