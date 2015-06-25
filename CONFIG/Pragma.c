/***************************************************
 FileName 	:   Pragma.c
 Date		:	2012.07.27
 Author		:	Yeon June	 
****************************************************/

/** Duplicate check ********************************/
#ifndef __PRAGMA_C__
#define __PRAGMA_C__

/** Includes ***************************************/
#include "HardwareProfile.h"		// for use PICF4550 var

/** Compiler preconfig *****************************/
#if defined(PICDEM_FS_USB)      // Configuration bits for PICDEM FS USB Demo Board (based on PIC18F4550)
       #pragma config PLLDIV   = 1         // (4 MHz crystal)
       #pragma config CPUDIV   = OSC1_PLL2   
       #pragma config USBDIV   = 2         // Clock source from 96MHz PLL/2
       #pragma config FOSC     = HSPLL_HS
       #pragma config FCMEN    = OFF
       #pragma config IESO     = OFF
       #pragma config PWRT     = OFF
       #pragma config BOR      = ON
       #pragma config BORV     = 3
       #pragma config VREGEN   = ON      //USB Voltage Regulator
       #pragma config WDT      = OFF
       #pragma config WDTPS    = 32768
       #pragma config MCLRE    = ON
       #pragma config LPT1OSC  = OFF
       #pragma config PBADEN   = OFF
//      #pragma config CCP2MX   = ON
       #pragma config STVREN   = ON
       #pragma config LVP      = OFF
//      #pragma config ICPRT    = OFF       // Dedicated In-Circuit Debug/Programming
       #pragma config XINST    = OFF       // Extended Instruction Set
       #pragma config CP0      = OFF
       #pragma config CP1      = OFF
//      #pragma config CP2      = OFF
//      #pragma config CP3      = OFF
       #pragma config CPB      = OFF
//      #pragma config CPD      = OFF
       #pragma config WRT0     = OFF
       #pragma config WRT1     = OFF
//      #pragma config WRT2     = OFF
//      #pragma config WRT3     = OFF
       #pragma config WRTB     = OFF       // Boot Block Write Protection
       #pragma config WRTC     = OFF
//      #pragma config WRTD     = OFF
       #pragma config EBTR0    = OFF
       #pragma config EBTR1    = OFF
//      #pragma config EBTR2    = OFF
//      #pragma config EBTR3    = OFF
       #pragma config EBTRB    = OFF		
#elif defined(PIC18F87J50_PIM)				// Configuration bits for PIC18F87J50 FS USB Plug-In Module board
       #pragma config XINST    = OFF   	// Extended instruction set
       #pragma config STVREN   = ON      	// Stack overflow reset
       #pragma config PLLDIV   = 3         // (12 MHz crystal used on this board)
       #pragma config WDTEN    = OFF      	// Watch Dog Timer (WDT)
       #pragma config CP0      = OFF      	// Code protect
       #pragma config CPUDIV   = OSC1      // OSC1 = divide by 1 mode
       #pragma config IESO     = OFF      	// Internal External (clock) Switchover
       #pragma config FCMEN    = OFF      	// Fail Safe Clock Monitor
       #pragma config FOSC     = HSPLL     // Firmware must also set OSCTUNE<PLLEN> to start PLL!
       #pragma config WDTPS    = 32768
//      #pragma config WAIT     = OFF      	// Commented choices are
//      #pragma config BW       = 16      	// only available on the
//      #pragma config MODE     = MM      	// 80 pin devices in the 
//      #pragma config EASHFT   = OFF      	// family.
       #pragma config MSSPMSK  = MSK5
//      #pragma config PMPMX    = DEFAULT
//      #pragma config ECCPMX   = DEFAULT
       #pragma config CCP2MX   = DEFAULT   
#elif defined(PIC18F46J50_PIM) || defined(PIC18F_STARTER_KIT_1)
     #pragma config WDTEN = OFF          //WDT disabled (enabled by SWDTEN bit)
     #pragma config PLLDIV = 3           //Divide by 3 (12 MHz oscillator input)
     #pragma config STVREN = ON            //stack overflow/underflow reset enabled
     #pragma config XINST = OFF          //Extended instruction set disabled
     #pragma config CPUDIV = OSC1        //No CPU system clock divide
     #pragma config CP0 = OFF            //Program memory is not code-protected
     #pragma config OSC = HSPLL          //HS oscillator, PLL enabled, HSPLL used by USB
     #pragma config T1DIG = OFF          //Sec Osc clock source may not be selected, unless T1OSCEN = 1
     #pragma config LPT1OSC = OFF        //high power Timer1 mode
     #pragma config FCMEN = OFF          //Fail-Safe Clock Monitor disabled
     #pragma config IESO = OFF           //Two-Speed Start-up disabled
     #pragma config WDTPS = 32768        //1:32768
     #pragma config DSWDTOSC = INTOSCREF //DSWDT uses INTOSC/INTRC as clock
     #pragma config RTCOSC = T1OSCREF    //RTCC uses T1OSC/T1CKI as clock
     #pragma config DSBOREN = OFF        //Zero-Power BOR disabled in Deep Sleep
     #pragma config DSWDTEN = OFF        //Disabled
     #pragma config DSWDTPS = 8192       //1:8,192 (8.5 seconds)
     #pragma config IOL1WAY = OFF        //IOLOCK bit can be set and cleared
     #pragma config MSSP7B_EN = MSK7     //7 Bit address masking
     #pragma config WPFP = PAGE_1        //Write Protect Program Flash Page 0
     #pragma config WPEND = PAGE_0       //Start protection at page 0
     #pragma config WPCFG = OFF          //Write/Erase last page protect Disabled
     #pragma config WPDIS = OFF          //WPFP[5:0], WPEND, and WPCFG bits ignored 
#elif defined(LOW_PIN_COUNT_USB_DEVELOPMENT_KIT)
      	 #pragma config CPUDIV = NOCLKDIV
   	 #pragma config USBDIV = OFF
      	 #pragma config FOSC   = HS
      	 #pragma config PLLEN  = ON
      	 #pragma config FCMEN  = OFF
      	 #pragma config IESO   = OFF
      	 #pragma config PWRTEN = OFF
      	 #pragma config BOREN  = OFF
      	 #pragma config BORV   = 30
      	 #pragma config WDTEN  = OFF
      	 #pragma config WDTPS  = 32768
      	 #pragma config MCLRE  = OFF
        #pragma config HFOFST = OFF
      	 #pragma config STVREN = ON
      	 #pragma config LVP    = OFF
      	 #pragma config XINST  = OFF
      	 #pragma config BBSIZ  = OFF
      	 #pragma config CP0    = OFF
      	 #pragma config CP1    = OFF
      	 #pragma config CPB    = OFF
      	 #pragma config WRT0   = OFF
      	 #pragma config WRT1   = OFF
      	 #pragma config WRTB   = OFF
      	 #pragma config WRTC   = OFF
      	 #pragma config EBTR0  = OFF
      	 #pragma config EBTR1  = OFF
      	 #pragma config EBTRB  = OFF       
#elif defined(EXPLORER_16)
    #ifdef __PIC24FJ256GB110__ //Defined by MPLAB when using 24FJ256GB110 device
        _CONFIG1( JTAGEN_OFF & GCP_OFF & GWRP_OFF & COE_OFF & FWDTEN_OFF & ICS_PGx2) 
        _CONFIG2( 0xF7FF & IESO_OFF & FCKSM_CSDCMD & OSCIOFNC_OFF & POSCMOD_HS & FNOSC_PRIPLL & PLLDIV_DIV2 & IOL1WAY_ON)
    #elif defined(__PIC24FJ64GB004__)
        _CONFIG1(WDTPS_PS1 & FWPSA_PR32 & WINDIS_OFF & FWDTEN_OFF & ICS_PGx1 & GWRP_OFF & GCP_OFF & JTAGEN_OFF)
        _CONFIG2(POSCMOD_HS & I2C1SEL_PRI & IOL1WAY_OFF & OSCIOFNC_ON & FCKSM_CSDCMD & FNOSC_PRIPLL & PLL96MHZ_ON & PLLDIV_DIV2 & IESO_ON)
        _CONFIG3(WPFP_WPFP0 & SOSCSEL_SOSC & WUTSEL_LEG & WPDIS_WPDIS & WPCFG_WPCFGDIS & WPEND_WPENDMEM)
        _CONFIG4(DSWDTPS_DSWDTPS3 & DSWDTOSC_LPRC & RTCOSC_SOSC & DSBOREN_OFF & DSWDTEN_OFF)
    #elif defined(__32MX460F512L__) || defined(__32MX795F512L__)
        #pragma config UPLLEN   = ON        // USB PLL Enabled
        #pragma config FPLLMUL  = MUL_15        // PLL Multiplier
        #pragma config UPLLIDIV = DIV_2         // USB PLL Input Divider
        #pragma config FPLLIDIV = DIV_2         // PLL Input Divider
        #pragma config FPLLODIV = DIV_1         // PLL Output Divider
        #pragma config FPBDIV   = DIV_1         // Peripheral Clock divisor
        #pragma config FWDTEN   = OFF           // Watchdog Timer
        #pragma config WDTPS    = PS1           // Watchdog Timer Postscale
        #pragma config FCKSM    = CSDCMD        // Clock Switching & Fail Safe Clock Monitor
        #pragma config OSCIOFNC = OFF           // CLKO Enable
        #pragma config POSCMOD  = HS            // Primary Oscillator
        #pragma config IESO     = OFF           // Internal/External Switch-over
        #pragma config FSOSCEN  = OFF           // Secondary Oscillator Enable (KLO was off)
        #pragma config FNOSC    = PRIPLL        // Oscillator Selection
        #pragma config CP       = OFF           // Code Protect
        #pragma config BWP      = OFF           // Boot Flash Write Protect
        #pragma config PWP      = OFF           // Program Flash Write Protect
        #pragma config ICESEL   = ICS_PGx2      // ICE/ICD Comm Channel Select
        #pragma config DEBUG    = ON            // Background Debugger Enable
    #else
        #error No hardware board defined, see "HardwareProfile.h" and __FILE__
    #endif
#elif defined(PIC24F_STARTER_KIT)
    _CONFIG1( JTAGEN_OFF & GCP_OFF & GWRP_OFF & COE_OFF & FWDTEN_OFF & ICS_PGx2) 
    _CONFIG2( 0xF7FF & IESO_OFF & FCKSM_CSDCMD & OSCIOFNC_OFF & POSCMOD_HS & FNOSC_PRIPLL & PLLDIV_DIV3 & IOL1WAY_ON)
#elif defined(PIC24FJ256DA210_DEV_BOARD)
    //_CONFIG1(FWDTEN_OFF & ICS_PGx2 & COE_OFF & GWRP_OFF & GCP_OFF & JTAGEN_OFF)
    //_CONFIG2(POSCMOD_HS & IOL1WAY_ON & OSCIOFNC_ON & FCKSM_CSDCMD & FNOSC_PRIPLL & PLL96MHZ_ON & PLLDIV_DIV2 & IESO_OFF)
#elif defined(PIC32_USB_STARTER_KIT)
    #pragma config UPLLEN   = ON        // USB PLL Enabled
    #pragma config FPLLMUL  = MUL_15        // PLL Multiplier
    #pragma config UPLLIDIV = DIV_2         // USB PLL Input Divider
    #pragma config FPLLIDIV = DIV_2         // PLL Input Divider
    #pragma config FPLLODIV = DIV_1         // PLL Output Divider
    #pragma config FPBDIV   = DIV_1         // Peripheral Clock divisor
    #pragma config FWDTEN   = OFF           // Watchdog Timer
    #pragma config WDTPS    = PS1           // Watchdog Timer Postscale
    #pragma config FCKSM    = CSDCMD        // Clock Switching & Fail Safe Clock Monitor
    #pragma config OSCIOFNC = OFF           // CLKO Enable
    #pragma config POSCMOD  = HS            // Primary Oscillator
    #pragma config IESO     = OFF           // Internal/External Switch-over
    #pragma config FSOSCEN  = OFF           // Secondary Oscillator Enable (KLO was off)
    #pragma config FNOSC    = PRIPLL        // Oscillator Selection
    #pragma config CP       = OFF           // Code Protect
    #pragma config BWP      = OFF           // Boot Flash Write Protect
    #pragma config PWP      = OFF           // Program Flash Write Protect
    #pragma config ICESEL   = ICS_PGx2      // ICE/ICD Comm Channel Select
    #pragma config DEBUG    = ON            // Background Debugger Enable
#else
    #error No hardware board defined, see "HardwareProfile.h" and __FILE__
#endif

#endif	/** End of __PRAGMA_C__ *************************/


