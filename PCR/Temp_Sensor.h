/***************************************************
*	FileName 	:	Temp_Sensor.h
*	Date	 	:	2012.08.11
*	Author		:	Yeon June
****************************************************/

/** Duplicate check ********************************/
#ifndef __TEMP_SENSOR_H__
#define __TEMP_SENSOR_H__

/** Includes ***************************************/
#include "./DEFINE/GenericTypeDefs.h"

/** Prototypes *************************************/
void Convert_Temp(void);
WORD Read_Temp(BYTE select);

#endif	/** End of __TEMP_SENSOR_H__ ***************/


