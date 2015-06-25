/****************************************************
*	FileName 	:	Timer.c
*	Date	 	:	2012.07.27
*	Author		:	Yeon June
****************************************************/

/** Includes ***************************************/
#include "HardwareProfile.h"
#include "./CONFIG/Compiler.h"
#include "./DEFINE/GenericTypeDefs.h"
#include "./DEFINE/GlobalTypeVars.h"
#include "./DEFINE/UserDefs.h"
#include "./PCR/Timer.h"

/** Variables **************************************/
// Counter
BYTE Heater_Count = 0x0000;
BYTE ChamberFan_Count = 0x0000;
BYTE SystemFan_Count = 0x0000;

/***************************************************
 * Function:        void TIMR0_init(void)
 *
 * OverView:		This routine will use low interrupt service routine configuration.
 *
 * Note:			Calculate duration 
 *					timer0 clock : Fosc/4 = 12MHz 
 *					timer0 prescaler 1:256 
 *					1 clock time  = 256/12M = 21.33us
 *					8bit timer -> 255*21.33 = 5.439 msec
 *					16bit timer -> 65535*21.33 = 1.398080 sec
 *					21.3us min to 5.439ms max is variable per 1 interrupt
 ***************************************************/
void TIMR0_init(void)
{
	//Timer0
	T0CONbits.TMR0ON = 0; //stop timer
	T0CONbits.T08BIT = 1; //1:8bit , 0:16bit
	T0CONbits.T0CS = 0; //Internal instruction cycle clock (CLKO)
	T0CONbits.PSA=0;//Timer0 prescaler is assigned. Timer0 clock input comes from prescaler output.
	
	//Timer0 Prescaler Select bits 
	T0CONbits.T0PS2=1;	//1:256 -> 12/256 = 46.8Khz
	T0CONbits.T0PS1=1;	
	T0CONbits.T0PS0=1;	

	//8bit setting
	TMR0L = 0xf5;  //set taking 255 - 245(0xf5) = 10*21.3us = 213us at every timer0 interrupt	
	
	//16bit setting
	//TMR0H = 0x00; //set duration high first
	//TMR0L = 0x00;  //set duration low 
	
	// Enable interrupts 
	INTCON2bits.TMR0IP = 0;//Low priority
	INTCONbits.GIEH=1;//Enables all unmasked interrupts
	INTCONbits.GIEL=1;//Enables all unmasked peripheral interrupts
	INTCONbits.TMR0IE=1;//Enables the TMR0 overflow interrupt

	T0CONbits.TMR0ON = 1;  	//start timer
}

/***************************************************
 * Function:        void TIMR1_init(void)
 *
 * OverView:		This routine will use high interrupt service routine configuration.
 *
 * Note:			None
 ***************************************************/
void TIMR1_init(void)
{
	T1CONbits.TMR1ON = 0; //stop timer
	T1CONbits.RD16 = 1; //0:two 8bit , 1:one 16bit		
	T1CONbits.TMR1CS = 0; //Internal clock	(Fosc/4) = 12Mhz
	T1CONbits.T1OSCEN=0;  //timer 1 oscillator shut off
	//Timer1 Prescaler Select bits 	
	T1CONbits.T1CKPS1=1;	//12 / 8 => 1/1.5Mhz * 1500 = 1ms at every timer 1 interrupt
	T1CONbits.T1CKPS0=1;	

	//16bit setting	  65536-1500 = 64035 = 0xFA23
	TMR1H = 0xFA; //set duration high byte first
	TMR1L = 0x23;  //set duration low byte


	// Enable interrupts 
	//INTCON2bits.TMR1IP = 1;// timer 1 interrupt Low priority
	INTCONbits.GIEH=1;//Enables all unmasked interrupts
	INTCONbits.GIEL=1;//Enables all unmasked peripheral interrupts		
	PIE1bits.TMR1IE =1;	

	T1CONbits.TMR1ON = 1;  	//start timer	
}

/***************************************************
 * Function:        void timer0_isr(void)
 *
 * OverView:		If low interrupt actived, called this function.
 *					Control Heater, Chamber, System Fan.
 *
 * Note:			reference BootLoader.h
 ***************************************************/
void timer0_isr(void)
{
	//Clears the TMR0 interrupt flag to stop the program 
	//from processing the same interrupt multiple times.   
	INTCONbits.TMR0IF =0;
	//TMR0L = 0xf5;	
	TMR0L = 0xf0;

	// Heater Control
	if( Heater_Count < (WORD)Heater || Heater == 0xff )
	{
		mHeater_On();
	}
	else 
	{
		mHeater_Off();
	}

	// Chamber Fan Control
	if( ChamberFan_Count < (WORD)Chamber_Fan || Chamber_Fan == 0xff )
	{
		mCFan_On();
	}
	else
	{
		mCFan_Off();
	}

	// System Fan Control
	if( SystemFan_Count < (WORD)System_Fan || System_Fan == 0xff )
	{
		mSFan_On();
	}
	else
	{
		mSFan_Off();
	}

	Heater_Count++;
	ChamberFan_Count++;
	SystemFan_Count++;

	if( Heater_Count > LID_HEATER_DURATION )
		Heater_Count = 0;
	
	if( ChamberFan_Count > CHM_FAN_DURATION )
		ChamberFan_Count = 0;

	if( SystemFan_Count > SYS_FAN_DURATION )
		SystemFan_Count = 0;
}

/***************************************************
 * Function:        timer1_isr(void)
 *
 * OverView:		If high interrupt actived, called this function.
 *
 * Note:			reference BootLoader.h
 ***************************************************/
void timer1_isr(void)
{
	if(PIR1bits.TMR1IF)
	{
		PIR1bits.TMR1IF=0;	// set off timer1 flag.

		TMR1H = 0xFA; 	//	set duration high first
		TMR1L = 0x23;  	//	set duration low

		if( T100MS_Counter >= 50 )
		{
			T100MS_Flag = TRUE;		//	set 100ms flag	
			T100MS_Counter = 0;
			T1S_Counter++;			
		}
		else
		{
			T100MS_Counter++;
		}

		if(T1S_Counter==10)
		{
			if( Cur_State == STATE_RUN ) mLED_B_On();
		}

		if(T1S_Counter>=20)
		{
			if( Cur_State == STATE_RUN )
				if( !IsCoolingState ) mLED_B_Off();

			T1S_Flag = TRUE;	//	set 1sec flag	
			T1S_Counter = 0;
		}
	}
}

