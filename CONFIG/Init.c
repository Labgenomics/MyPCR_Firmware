/***************************************************
 *	FileName 	:   Init.c
 *	Date		:	2012.07.27
 *	Author		:	Yeon June	 
****************************************************/

/** Includes ***************************************/
#include "HardwareProfile.h"
#include "./CONFIG/Compiler.h"
#include "./CONFIG/Init.h"
#include "./USB/usb.h"
#include "./DEFINE/GlobalTypeVars.h"
#include "./DEFINE/UserDefs.h"
#include "./TOOLS/Delay.h"
#include "./PCR/Timer.h"
#include "./PCR/PCR_Task.h"

/** Extern Variables & Functions *******************/
extern void USB_Task(void);
extern unsigned char ReceivedDataBuffer[RX_BUFSIZE];
extern unsigned char ToSendDataBuffer[TX_BUFSIZE];

/***************************************************
 * Function:        void Init(void)
 *
 * OverView:		All calling related to Initialized functions.
 *
 * Note:			None
 ***************************************************/
void Init(void)
{
	InitializeSystem();		//	Initialize Related to connect usb port.
	InitializeUser();		//	Initialize for User Variables.
	InitializeDevice();		//	Initialize PICF4550 LED, PWM, ADC Ports
	USBDeviceInit();		//	Initialize USB Module.

	#if defined(USB_INTERRUPT)
		USBDeviceAttach();	//	Enable to find USB Device
	#endif
}

/********************************************************************
 * Function:        void InitializeSystem(void)
 *
 * Overview:        InitializeSystem is a centralize initialization
 *                  routine. All required USB initialization routines
 *                  are called from here.
 *
 *                  User application initialization routine should
 *                  also be called from here.                  
 *
 * Note:            None
 *******************************************************************/
void InitializeSystem(void)
{
	#ifndef __INITSYSTEM__

	#define __INITSYSTEM__

    #if (defined(__18CXX) & !defined(PIC18F87J50_PIM))
        ADCON1 |= 0x0F;                 // Default all pins to digital
    #elif defined(__C30__)
    	#if defined(__PIC24FJ256DA210__)
    		ANSA = 0x0000;
    		ANSB = 0x0000;
    		ANSC = 0x0000;
    		ANSD = 0x0000;
    		ANSE = 0x0000;
    		ANSF = 0x0000;
    		ANSG = 0x0000;
        #else
        	AD1PCFGL = 0xFFFF;
        #endif        
    #elif defined(__C32__)
        AD1PCFG = 0xFFFF;
    #endif

    #if defined(PIC18F87J50_PIM) || defined(PIC18F46J50_PIM) || defined(PIC18F_STARTER_KIT_1)
	//On the PIC18F87J50 Family of USB microcontrollers, the PLL will not power up and be enabled
	//by default, even if a PLL enabled oscillator configuration is selected (such as HS+PLL).
	//This allows the device to power up at a lower initial operating frequency, which can be
	//advantageous when powered from a source which is not gauranteed to be adequate for 48MHz
	//operation.  On these devices, user firmware needs to manually set the OSCTUNE<PLLEN> bit to
	//power up the PLL.
    {
        unsigned int pll_startup_counter = 600;
        OSCTUNEbits.PLLEN = 1;  //Enable the PLL and wait 2+ms until the PLL locks before enabling USB module
        while(pll_startup_counter--);
    }
    //Device switches over automatically to PLL output after PLL is locked and ready.
    #endif

    #if defined(PIC18F87J50_PIM)
	//Configure all I/O pins to use digital input buffers.  The PIC18F87J50 Family devices
	//use the ANCONx registers to control this, which is different from other devices which
	//use the ADCON1 register for this purpose.
    WDTCONbits.ADSHR = 1;			// Select alternate SFR location to access ANCONx registers
    ANCON0 = 0xFF;                  // Default all pins to digital
    ANCON1 = 0xFF;                  // Default all pins to digital
    WDTCONbits.ADSHR = 0;			// Select normal SFR locations
    #endif

    #if defined(PIC18F46J50_PIM) || defined(PIC18F_STARTER_KIT_1)
	//Configure all I/O pins to use digital input buffers.  The PIC18F87J50 Family devices
	//use the ANCONx registers to control this, which is different from other devices which
	//use the ADCON1 register for this purpose.
    ANCON0 = 0xFF;                  // Default all pins to digital
    ANCON1 = 0xFF;                  // Default all pins to digital
    #endif
    
   #if defined(PIC24FJ64GB004_PIM) || defined(PIC24FJ256DA210_DEV_BOARD)
	//On the PIC24FJ64GB004 Family of USB microcontrollers, the PLL will not power up and be enabled
	//by default, even if a PLL enabled oscillator configuration is selected (such as HS+PLL).
	//This allows the device to power up at a lower initial operating frequency, which can be
	//advantageous when powered from a source which is not gauranteed to be adequate for 32MHz
	//operation.  On these devices, user firmware needs to manually set the CLKDIV<PLLEN> bit to
	//power up the PLL.
    {
        unsigned int pll_startup_counter = 600;
        CLKDIVbits.PLLEN = 1;
        while(pll_startup_counter--);
    }

    //Device switches over automatically to PLL output after PLL is locked and ready.
    #endif


//	The USB specifications require that USB peripheral devices must never source
//	current onto the Vbus pin.  Additionally, USB peripherals should not source
//	current on D+ or D- when the host/hub is not actively powering the Vbus line.
//	When designing a self powered (as opposed to bus powered) USB peripheral
//	device, the firmware should make sure not to turn on the USB module and D+
//	or D- pull up resistor unless Vbus is actively powered.  Therefore, the
//	firmware needs some means to detect when Vbus is being powered by the host.
//	A 5V tolerant I/O pin can be connected to Vbus (through a resistor), and
// 	can be used to detect when Vbus is high (host actively powering), or low
//	(host is shut down or otherwise not supplying power).  The USB firmware
// 	can then periodically poll this I/O pin to know when it is okay to turn on
//	the USB module/D+/D- pull up resistor.  When designing a purely bus powered
//	peripheral device, it is not possible to source current on D+ or D- when the
//	host is not actively providing power on Vbus. Therefore, implementing this
//	bus sense feature is optional.  This firmware can be made to use this bus
//	sense feature by making sure "USE_USB_BUS_SENSE_IO" has been defined in the
//	HardwareProfile.h file.    
    #if defined(USE_USB_BUS_SENSE_IO)
    tris_usb_bus_sense = INPUT_PIN; // See HardwareProfile.h
    #endif
    
//	If the host PC sends a GetStatus (device) request, the firmware must respond
//	and let the host know if the USB peripheral device is currently bus powered
//	or self powered.  See chapter 9 in the official USB specifications for details
//	regarding this request.  If the peripheral device is capable of being both
//	self and bus powered, it should not return a hard coded value for this request.
//	Instead, firmware should check if it is currently self or bus powered, and
//	respond accordingly.  If the hardware has been configured like demonstrated
//	on the PICDEM FS USB Demo Board, an I/O pin can be polled to determine the
//	currently selected power source.  On the PICDEM FS USB Demo Board, "RA2" 
//	is used for	this purpose.  If using this feature, make sure "USE_SELF_POWER_SENSE_IO"
//	has been defined in HardwareProfile.h, and that an appropriate I/O pin has been mapped
//	to it in HardwareProfile.h.
    #if defined(USE_SELF_POWER_SENSE_IO)
    tris_self_power = INPUT_PIN;	// See HardwareProfile.h
    #endif

//    USBDeviceInit();	//usb_device.c.  Initializes USB module SFRs and firmware
    					//variables to known states.
	#endif
}//end InitializeSystem

/***************************************************
 * Function:        InitializeDevice(void)
 *
 * OverView:		Initialize Device Port, LED, Switches, ADC, PWM, TIMER, ETC..
 *
 * Note:			None
 ***************************************************/
void InitializeDevice(void)
{
	//Initialize all of the LED pins
	mInitAllLEDs();	
	LED_INIT();

    //Initialize all of the push buttons
    mInitAllSwitches();

	//initialize adc for ntc sensor
	InitADC();

	//initialize lid heater
	InitHeater();

	//initialize fan
	Init_ChamberFan();
	Init_SystemFan();

	//initialize pwm 	
	Stop_PWM_MODE();

	//initialize fan & heater control with timer0
	TIMR0_init();

	//pcr task tick
	TIMR1_init();
}

/***************************************************
 * Function:        InitializeUser(void)
 *
 * OverView:		Now only buffer Init.
 *
 * Note:			None
 ***************************************************/
void InitializeUser(void)
{
	//	Buffer init
	memset(ReceivedDataBuffer, 0, RX_BUFSIZE);
	memset(ToSendDataBuffer, 0, TX_BUFSIZE);
}

/***************************************************
 * Function:        void MainLooper(void)
 *
 * OverView:		At 0.2 ticks, Called USB_Task(), PCR_Task() functions.
 *
 * Note:			None
 ***************************************************/
void MainLooper(void)
{
	if(T100MS_Flag)		//	At 0.1 ticks. but now 0.2 ms? maybe
	{
		USB_Task();		//	If connected to host, commnuicate by host. rx, tx.
		
		PCR_Task();		//	PCR Service Routine.
	}
}