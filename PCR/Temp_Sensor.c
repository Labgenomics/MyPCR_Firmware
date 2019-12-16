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
	float dispTemp;
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
	//KJD181123, 29, 30, 1206
	if ( IsTargetArrived == FALSE ) {
 		if ( Pre_Chamber_Target > Chamber_Target ) //cooling target
			 Chamber_Temper = RHOD*Chamber_Temper + (1-RHOD)*pre_convertTemp;
		else Chamber_Temper = RHOU*Chamber_Temper + (1-RHOU)*pre_convertTemp;
		pre_convertTemp = Chamber_Temper;
		tmpT100MS_Counter = 0;
	}
	else {
		float ss = (float) tmpT100MS_Counter * 1./REC_STEPS;
		if ( ss < 1. ) Chamber_Temper = ss*Chamber_Temper + (1-ss)*pre_convertTemp;
		tmpT100MS_Counter++;
	}			
	dispTemp = Chamber_Temper;
	Chamber_Temp_H = (int) dispTemp; //for display temeprature
	Chamber_Temp_L = (int) ((dispTemp -(float) Chamber_Temp_H)*10); 
	//KJD181129}

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