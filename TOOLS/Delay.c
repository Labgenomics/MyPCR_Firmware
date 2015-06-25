/****************************************************
*	FileName 	:	Delay.c
*	Date	 	:	2012.07.27
*	Author		:	Yeon June
****************************************************/

/** Includes ***************************************/
#include "./TOOLS/Delay.h"

/***************************************************
 * Function:        void Delay(WORD ms)
 *
 * OverView:		For use Program Delay.
 *
 * Note:			the param is unsigned int, the value is ms. (1/1000 sec)
 ***************************************************/
void Delay(WORD ms)
{
	WORD i=0;	
    while(ms--)
	{ 
		for(i=0;i<1800;i++);
	}
}
