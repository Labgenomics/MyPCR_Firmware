/****************************************************
*	FileName 	:	Timer.h
*	Date	 	:	2012.07.27
*	Author		:	Yeon June
****************************************************/

/** Duplicate check ********************************/
#ifndef __TIMER_H__
#define __TIMER_H__

/** Prototypes *************************************/
void TIMR0_init(void);	//	Initialize Timer 0
void TIMR1_init(void);	//	Initialize Timer 1
void timer0_isr(void);	//	Low Interrupt Service Routine
void timer1_isr(void);	//	High Interrupt Service Routine

#endif	/** End of __TIMER_H__ *********************/