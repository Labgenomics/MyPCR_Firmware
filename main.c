/****************************************************
 *	FileName 	:   main.c
 *	Date		:	1. 	2012.07.27	::	Project Create & set framework
					2.	2012.08.11	::	Set about PCR_Protocol
					3.	2012.08.12	::	Complete related to temperature control
					4.  2012.08.12  ::	Fixed Stop task bug
					5.	2012.08.17	::	Fixed Not working GOTO Label
					6.  2012.08.19	::	
 *	Author		:	Yeon June 
****************************************************/

/** Duplicate check ********************************/
#ifndef __MAIN_C__
#define __MAIN_C__

/** Includes ***************************************/
#include "./CONFIG/BootLoader.h"	//	for use interrupt & bootloader
#include "./CONFIG/Init.h"			//	for user Initialize 


/****************************************************
 * Function:        void main(void)
 *
 * Overview:        Main program entry point.
 *
 * Note:            None
 ***************************************************/
void main(void)
{
	Init();		// all initialize in .CONFIG/init.c

    while(1)
    {
		MainLooper();	// usb routine & PCR routine in .CONFIG/Init.h
    }
}

#endif	/** End __MAIN_C__ *************************/




