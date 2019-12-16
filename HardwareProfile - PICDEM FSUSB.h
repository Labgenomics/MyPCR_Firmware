/********************************************************************
 FileName:     	HardwareProfile - PICDEM FSUSB.h
 Dependencies:  See INCLUDES section
 Processor:     PIC18 USB Microcontrollers
 Hardware:      PICDEM FSUSB
 Compiler:      Microchip C18
 Company:       Microchip Technology, Inc.

 Software License Agreement:

 The software supplied herewith by Microchip Technology Incorporated
 (the “Company? for its PIC?Microcontroller is intended and
 supplied to you, the Company’s customer, for use solely and
 exclusively on Microchip PIC Microcontroller products. The
 software is owned by the Company and/or its supplier, and is
 protected under applicable copyright laws. All rights are reserved.
 Any use in violation of the foregoing restrictions may subject the
 user to criminal sanctions under applicable laws, as well as to
 civil liability for the breach of the terms and conditions of this
 license.

 THIS SOFTWARE IS PROVIDED IN AN “AS IS?CONDITION. NO WARRANTIES,
 WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.

********************************************************************
 File Description:

 Change History:
  Rev   Date         Description
  1.0   11/19/2004   Initial release
  2.1   02/26/2007   Updated for simplicity and to use common
                     coding style
  2.3   09/15/2008   Broke out each hardware platform into its own
                     "HardwareProfile - xxx.h" file
********************************************************************/

#ifndef HARDWARE_PROFILE_PICDEM_FSUSB_H
#define HARDWARE_PROFILE_PICDEM_FSUSB_H

    /*******************************************************************/
    /******** USB stack hardware selection options *********************/
    /*******************************************************************/
    //This section is the set of definitions required by the MCHPFSUSB
    //  framework.  These definitions tell the firmware what mode it is
    //  running in, and where it can find the results to some information
    //  that the stack needs.
    //These definitions are required by every application developed with
    //  this revision of the MCHPFSUSB framework.  Please review each
    //  option carefully and determine which options are desired/required
    //  for your application.

    //The PICDEM FS USB Demo Board platform supports the USE_SELF_POWER_SENSE_IO
    //and USE_USB_BUS_SENSE_IO features.  Uncomment the below line(s) if
    //it is desireable to use one or both of the features.
    //#define USE_SELF_POWER_SENSE_IO
    #define tris_self_power     TRISAbits.TRISA2    // Input
    #if defined(USE_SELF_POWER_SENSE_IO)
    #define self_power          PORTAbits.RA2
    #else
    #define self_power          1
    #endif

    //#define USE_USB_BUS_SENSE_IO
    #define tris_usb_bus_sense  TRISAbits.TRISA1    // Input
    #if defined(USE_USB_BUS_SENSE_IO)
    #define USB_BUS_SENSE       PORTAbits.RA1
    #else
    #define USB_BUS_SENSE       1
    #endif


    //Uncomment the following line to make the output HEX of this  
    //  project work with the MCHPUSB Bootloader    
    //#define PROGRAMMABLE_WITH_USB_MCHPUSB_BOOTLOADER
	
    //Uncomment the following line to make the output HEX of this 
    //  project work with the HID Bootloader
    #define PROGRAMMABLE_WITH_USB_HID_BOOTLOADER		

    /*******************************************************************/
    /*******************************************************************/
    /*******************************************************************/
    /******** Application specific definitions *************************/
    /*******************************************************************/
    /*******************************************************************/
    /*******************************************************************/

    /** Board definition ***********************************************/
    //These defintions will tell the main() function which board is
    //  currently selected.  This will allow the application to add
    //  the correct configuration bits as wells use the correct
    //  initialization functions for the board.  These defitions are only
    //  required in the stack provided demos.  They are not required in
    //  final application design.
    #define DEMO_BOARD PICDEM_FS_USB
    #define PICDEM_FS_USB
    #define CLOCK_FREQ 48000000

    /** LED ************************************************************/
    #define mLED_R              LATDbits.LATD1
    #define mLED_B              LATDbits.LATD2
	#define LED_1				PORTDbits.RD0
	#define LED_2				PORTDbits.RD1
	#define LED_3				PORTDbits.RD2
    
    #define mGetLED_R()         mLED_R
    #define mGetLED_B()         mLED_B
    
    #define mLED_R_On()         mLED_R = 1;    
    #define mLED_B_On()         mLED_B = 1;

	#define LED_1_On()			LED_1 = 1;
	#define LED_2_On()			LED_2 = 1;
	#define LED_3_On()			LED_3 = 1;

	#define LED_INIT()			{TRISDbits.TRISD0 = 0; TRISDbits.TRISD1 = 0; TRISDbits.TRISD2 = 0;}
        
    #define mLED_R_Off()        mLED_R = 0;    
    #define mLED_B_Off()        mLED_B = 0;    
    
    #define mLED_R_Toggle()     mLED_R = !mLED_R;    
    #define mLED_B_Toggle()     mLED_B = !mLED_B;

	#define mInitAllLEDs()	{mLED_R_Off();mLED_B_Off();TRISDbits.TRISD1=OUTPUT_PIN;TRISDbits.TRISD2=OUTPUT_PIN;}

    /** SWITCH *********************************************************/
    #define mInitAllSwitches()  TRISBbits.TRISB4=1;
    #define mInitSwitch2()      TRISBbits.TRISB4=1;  
    #define sw2                 PORTBbits.RB4

/** ADC for temperature sensor*********************************************/
	
	//analog input ch 7 
	//adc enable, select ch 7 
	//right adjustable, 6TAD, Fosc	

	#define ADC_VCFG_VREF_RA2	0x20	//external VREF-
	#define ADC_VCFG_VREF_AVSS	0x00
	#define ADC_VCFG_VREF_RA3	0x10	//external VREF+
	#define ADC_VCFG_VREF_AVDD	0x00

	#define ADC_CH_00		(0b00000000)
	#define ADC_CH_01		(0b00000100)
	#define ADC_CH_02		(0b00001000)
	#define ADC_CH_03		(0b00001100)
	#define ADC_CH_04		(0b00010000)
	#define ADC_CH_05		(0b00010100)   
	#define ADC_CH_06		(0b00011000)
	#define ADC_CH_07		(0b00011100)
	#define ADC_CH_08		(0b00100000)
	#define ADC_CH_09		(0b00100100)
	#define ADC_CH_10		(0b00101000)
	#define ADC_CH_11		(0b00101100)
	#define ADC_CH_12		(0b00110000)
	#define ADC_RESERVED1	(0b00110100)
	#define ADC_RESERVED2	(0b00111000)
	#define ADC_RESERVED3	(0b00111100)

	#define ADC_INIT_CH		ADC_CH_00

	//set AN0,AN1,AN4 as analog input
	#define Set_ADC_INPUT() {TRISAbits.TRISA0=1;TRISAbits.TRISA1=1;TRISAbits.TRISA4=1; ADCON1 |= 0x0A;}

	#define ADC_ADON()	{ADCON0|=0x01;}
	#define ADC_ADOFF()	{ADCON0&=~(0x01);}

	#define RIGHT_ADJUST			0x80
	#define LEFT_ADJUST				0x00
	#define ADC_CALIBRATION			0x40
	#define ADC_NO_CALIBRATION		0x00

	#define ADC_ACQT_00TAD			(0b00000000)
	#define ADC_ACQT_02TAD			(0b00001000)
	#define ADC_ACQT_04TAD			(0b00010000)
	#define ADC_ACQT_06TAD			(0b00011000)
	#define ADC_ACQT_08TAD			(0b00100000)
	#define ADC_ACQT_12TAD			(0b00101000)
	#define ADC_ACQT_16TAD			(0b00110000)
	#define ADC_ACQT_20TAD			(0b00111000)

	#define ADC_ADCS_FREQD02		(0b00000000)
	#define ADC_ADCS_FREQD08		(0b00000001)
	#define ADC_ADCS_FREQD32		(0b00000010)
	#define ADC_ADCS_FREQRC1		(0b00000011)
	#define ADC_ADCS_FREQD04		(0b00000100)
	#define ADC_ADCS_FREQD16		(0b00000101)
	#define ADC_ADCS_FREQD64		(0b00000110)
	#define ADC_ADCS_FREQRC2		(0b00000111)

	#define SetADCChannel(channel){ADCON0 = (ADCON0 & 0b11000011)|((channel) & 0b00111100);}
	#define SetVREF()	{ADCON1= (ADCON1 & 0b11001111) | ((ADC_VCFG_VREF_RA2 | ADC_VCFG_VREF_RA3)&0b00110000);}
	#define SetADCSampleFormat(DIR)	{ADCON2 = (ADCON2 & 0b01111111) | (DIR&0b10000000);}
	#define SetADCAcqTime(TIME)	{ADCON2= (ADCON2&0b11000111) | (TIME&0b00111000);}
	#define SetADCConvClock(CLOCK)	{ADCON2= (ADCON2&0b11111000) | (CLOCK & 0b00000011);}

	#define InitADC()	{Set_ADC_INPUT();\
						 SetVREF();\
						 SetADCSampleFormat(RIGHT_ADJUST);\
						 SetADCChannel(ADC_INIT_CH);\
						 SetADCAcqTime(ADC_ACQT_06TAD);\
						 SetADCConvClock(ADC_ADCS_FREQD64);\
						 ADC_ADON();}
	/** PWM *********************************************/	

	//CCP2 pin multiplexing
	//PWM+ : RC2,  PWM- : RD5

	//CCPxCON
	//If CCPxM<3:2> = 00, 01, 10: PxB, PxC and PxD assigned as port pins
	//If CCPxM<3:2> = 11:
	#define PxM_SINGLE_OUTPUT		(0b00000000) //Single output: P1A modulated; P1B, P1C, P1D assigned as port pins
	#define PxM_FULL_BRIDGE_FORWARD	(0b01000000) //Full-bridge output forward: P1D modulated; P1A active; P1B, P1C inactive
	#define PxM_HALF_BRIDGE			(0b10000000) //Half-bridge output: P1A, P1B modulated with dead-band control; P1C, P1D assigned as port pins
	#define PxM_FULL_BRIDGE_REVERSE	(0b11000000) //Full-bridge output reverse: P1B modulated; P1C active; P1A, P1D inactive

	//DCxB: PWM mode:These bits are the two LSbs of the 10-bit PWM duty cycle. The eight MSbs of the duty cycle are found in CCPRxL.

	//CCPxM3:CCPxM0	
	#define CCPxM_OFF 								0x00 //Capture/Compare/PWM off (resets ECCPx module)
	#define CCPxM_RESERVED 							0x01 //Reserved
	#define CCPxM_COMPARE_TOGGLE_OUT_MATCH 			0x02 //Compare mode, toggle output on match
	#define CCPxM_CAPTURE					 		0x03 //Capture mode
	#define CCPxM_CAPTURE_EVERY_FALLING		  		0x04 //Capture mode, every falling edge
	#define CCPxM_CAPTURE_EVERY_RISING				0x05 //Capture mode, every rising edge
	#define CCPxM_CAPTURE_4TH_RISING				0x06 //Capture mode, every 4th rising edge
	#define CCPxM_CAPTURE_16TH_RISING				0x07 //Capture mode, every 16th rising edge
	#define CCPxM_COMPARE_SETCCPxIF_LOW			  	0x08 //Compare mode, initialize ECCPx pin low, set output on compare match (set CCPxIF)
	#define CCPxM_COMPARE_SETCCPxIF_HIGH 		  	0x09 //Compare mode, initialize ECCPx pin high, clear output on compare match (set CCPxIF)
	#define CCPxM_COMPARE_SOFTWARE_INTERRUPT_ONLY 	0x0A //Compare mode, generate software interrupt only, ECCPx pin reverts to I/O state
	#define CCPxM_COMPARE_TRIGGER_EVENT			  	0x0B //Compare mode, trigger special event (ECCPx resets TMR1 or TMR3, starts A/D conversion, sets CCxIF bit)
	#define CCPxM_PWM_ACTIVE_ACH_BDH 				0x0C //PWM mode; PxA and PxC active-high; PxB and PxD active-high
	#define CCPxM_PWM_ACTIVE_ACH_BDL 				0x0D //PWM mode; PxA and PxC active-high; PxB and PxD active-low
	#define CCPxM_PWM_ACTIVE_ACL_BDH 				0x0E //PWM mode; PxA and PxC active-low; PxB and PxD active-high
	#define CCPxM_PWM_ACTIVE_ACL_BDL 				0x0F //PWM mode; PxA and PxC active-low; PxB and PxD active-low
	
	#define Set_PWM_plus_In()		{LATCbits.LATC2=1;TRISC |= 0x04;}
	#define Set_PWM_minus_In()		{LATDbits.LATD5=1;TRISD |= 0x20;}

	#define Set_PWM_plus_Out()		{LATCbits.LATC2=0;TRISC &= ~(0x04);}
	#define Set_PWM_minus_Out()		{LATDbits.LATD5=0;TRISD &= ~(0x20);}
			 
	#define InitPWMPort()	{Set_PWM_plus_Out();\
						 	 Set_PWM_minus_Out();}

	#define InitPWM_FAN()	{}
	#define InitPWM_HEATER()	{}
	

	#define Init_PWM_MODE()	{InitPWMPort();\
							 T2CONbits.TMR2ON = 0;\
							 PR2 = 0xFF;\
							 CCP1CON =  PxM_HALF_BRIDGE | CCPxM_PWM_ACTIVE_ACH_BDH;\
							 T2CONbits.TMR2ON = 1;}

	#define Stop_PWM_MODE() {T2CONbits.TMR2ON = 0;\
							 Set_PWM_plus_In();\
						 	 Set_PWM_minus_In();}

	#define Switch_PWM_Port(port) {if(port<1){Set_PWM_plus_In();Set_PWM_minus_Out();} else{Set_PWM_plus_Out();Set_PWM_minus_In();}}

	/**chamber fan ************************************************************/
	//#define InitFan()		TRISC &= 0xBF; LATCbits.LATC6=1;
	#define Init_ChamberFan()		TRISDbits.TRISD6 = OUTPUT_PIN; LATDbits.LATD6=0;
	#define mCFan 		LATDbits.LATD6
	
 	#define mCFan_On()         mCFan = 1;  //n-mos:1 p-mos:0
    #define mCFan_Off()        mCFan = 0;  //n-mos:0 p-mos:1

	//#define InitFan()		TRISC &= 0xBF; LATCbits.LATC6=1;		// 130312 YJ
	#define Init_SystemFan()		TRISDbits.TRISD3 = OUTPUT_PIN; LATDbits.LATD3=0;
	#define mSFan 		LATDbits.LATD3
	
 	#define mSFan_On()         mSFan = 1;  //n-mos:1 p-mos:0
    #define mSFan_Off()        mSFan = 0;  //n-mos:0 p-mos:1
	
	/**heater ************************************************************/
	//#define InitHeater()		TRISC &= 0x7F; LATCbits.LATC7=0;	// 130312 YJ
	#define InitHeater()		TRISDbits.TRISD7 = OUTPUT_PIN; LATDbits.LATD7=0;
	#define mHeater		 		LATDbits.LATD7
	
 	#define mHeater_On()         mHeater = 1; //n-mos:1 p-mos:0
    #define mHeater_Off()        mHeater = 0; //n-mos:0 p-mos:1

    /** I/O pin definitions ********************************************/
    #define INPUT_PIN 1
    #define OUTPUT_PIN 0

	

#endif  //HARDWARE_PROFILE_PICDEM_FSUSB_H
