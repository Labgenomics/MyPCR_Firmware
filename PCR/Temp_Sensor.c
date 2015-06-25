/***************************************************
*	FileName 	:	Temp_Sensor.c
*	Date	 	:	2012.08.11
*	Author		:	Yeon June
****************************************************/

/** Includes ***************************************/
#include "HardwareProfile.h"
#include "./DEFINE/GlobalTypeVars.h"
#include "./DEFINE/UserDefs.h"
#include "./USB/usb.h"
#include "./USB/usb_function_hid.h"
#include "./PCR/Temp_Sensor.h"
#include "./PCR/Temp_Table.h"

/** Variables **************************************/
// temperature table in Temp_Table.c
extern struct{BYTE ntc_heater[NTC_HEATER_SIZE];}NTC_HEATER_TABLE;
extern struct{BYTE ntc_chamber[NTC_CHAMBER_SIZE];}NTC_CHAMBER_TABLE;

ROM BYTE *pTemp_Chamber = (ROM BYTE *)&NTC_CHAMBER_TABLE;
ROM BYTE *pTemp_Heater  = (ROM BYTE *)&NTC_HEATER_TABLE;

/***************************************************
 * Function:        void Convert_Temp(void)
 *
 * OverView:		Get Temperature by Temperature table.
 *
 * Note:			None
 ***************************************************/
void Convert_Temp(void)
{
	WORD index = 0x00;
	// Heater
	index = Read_Temp(HEATER_TEMP); index *= 2;
	LID_Temp_H = pTemp_Heater[index];
	LID_Temp_L = pTemp_Heater[index+1];
	Heater_Temper = LID_Temp_H + LID_Temp_L * 0.1;

	// Chamber
	index= Read_Temp(CHAMBER_TEMP);	index *= 2;
	Chamber_Temp_H = pTemp_Chamber[index];
	Chamber_Temp_L = pTemp_Chamber[index+1];
	Chamber_Temper = Chamber_Temp_H + Chamber_Temp_L * 0.1;

	// HeatSink
	index = Read_Temp(HEATSINK_TEMP); index *= 2;
	Heatsink_Temp_H = pTemp_Chamber[index];
	Heatsink_Temp_L = pTemp_Chamber[index+1];
	Heatsink_Temper = Heatsink_Temp_H + Heatsink_Temp_L * 0.1;
}

/***************************************************
 * Function:        WORD Read_Temp(BYTE select)
 *
 * OverView:		Get Temperature by Selected Temperature
 *					1. Heater Temperature
 *					2. Chamber Temperature
 *					3. Heatsink Temperature
 *					* counter value is SAMPLING_COUNT.
 *					* SAMPLING_COUNT is read temperature count.
 *
 * Note:			Define select value in ./DEFINE/UserDefs.h
 ***************************************************/
WORD Read_Temp(BYTE select)
{
	WORD w;
	BYTE low = 0x00;
	BYTE high = 0x00;
	BYTE counter = SAMPLING_COUNT;
	WORD sum = 0;

	switch(select)
	{
		case HEATER_TEMP:
			SetADCChannel(SENSOR_HEATER);
			break;
		case CHAMBER_TEMP:
			SetADCChannel(SENSOR_CHAMBER);
			break;
		case HEATSINK_TEMP:
			SetADCChannel(SENSOR_HEATSINK);
			break;
	}

	while(counter--)
	{
		while(ADCON0bits.NOT_DONE);     // Wait for busy
    	ADCON0bits.GO = 1;              // Start AD conversion
    	while(ADCON0bits.NOT_DONE);     // Wait for conversion

		low = ADRESL;
		high = ADRESH;
    	w = (WORD)high*256 + (WORD)low;
		sum += w;
	}

	w = sum / SAMPLING_COUNT;

	return w;
}