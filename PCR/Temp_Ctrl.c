/****************************************************
*	FileName 	:	Temp_Ctrl.c
*	Date	 	:	2012.08.11
*	Author		:	Yeon June
****************************************************/

/** Includes ***************************************/
#include "HardwareProfile.h"
#include "./CONFIG/Compiler.h"
#include "./DEFINE/GlobalTypeVars.h"
#include "./PCR/Temp_Ctrl.h"
#include "./PCR/Temp_Sensor.h"

#if defined(TESTER)
	#include <math.h>
#endif

/** Variables **************************************/
// Duration Value
BYTE Chamber_Fan_Duration = 0x00;
BYTE System_Fan_Duration = 0x00;
float PWM_Duration = 0.;

// Heater Value
float Heater_Duration = 0.;
float Heater_LastErr = 0x00;
float Heater_LastIntegral = 0x00;

/***************************************************
 * Function:        void Init_Temp_Control(void)
 *
 * OverView:		Initialize Temperature Value.
 * 					Copy Previous Heater Temper, Start PWM
 *
 * Note:			None
 ***************************************************/
void Init_Temp_Control(void)
{
	// LID heater target temp
	Heater_Target = Het_Target_Temp;

	// Start LID Heater control
	IsCoverCtrl = TRUE;

	// reset All Variables
	Kp = 50;
	Ki = 0;
	Kd = 0;
	IsCoverHeated = FALSE;
	IsChamberCtrl = FALSE;
	IsCompletePCR = FALSE;

	// Init PWM
	Init_PWM_MODE();
}

/***************************************************
 * Function:        void Temp_Control(void)
 *
 * OverView:		This Function is Get Device Temperature
 *					Check State is running, Control Temperature device.
 *
 * Note:			None
 ***************************************************/
void Temp_Control(void)
{
	// Get Temperature by Temperature table.
	#if !defined(TESTER)
		Convert_Temp();
	#endif

	// Chamber Fan Control
	Get_ChamberFan_Duration(Chamber_Temper);
	Set_ChamberFan_Duration(Chamber_Fan_Duration);

	// System Fan Control
	Get_SystemFan_Duration(Heatsink_Temper);
	Set_SystemFan_Duration(System_Fan_Duration);

	// Adding the Errorcheck for all routine
	// 130729 YJ
	Temp_ErrorCheck();

	// Check Current State, if State is run, Called Temperature control Routine.
	switch(Cur_State)
	{
		case STATE_READY:
			#if defined(TESTER)
			Heater_Temper = 25.;
			Chamber_Temper = 25.;

			LID_Temp_H = 25;
			LID_Temp_L = 1;
			Chamber_Temp_H = 25;
			Chamber_Temp_L = 2;
			#endif
			return;
		case STATE_RUN:		// Valid Section
			Temp_Run_Routine();
			break;
		case STATE_PCREND:
			return;
		default:
			break;
	}
}

/***************************************************
 * Function:        void Temp_Run_Routine(void)
 *
 * OverView:		Check the Current State & Control Device Temperature
 *
 * Note:			None
 ***************************************************/
void Temp_Run_Routine(void)
{
	// LID Heater Temperature Control
	if( IsCoverCtrl == TRUE )
	{
		#if !defined(TESTER)
		if( Chamber_Target < HEATEROFF_TEMP)
		{
			Set_Heater_Duration(0);
			IsChamberCtrl = TRUE;
			IsCoverHeated = TRUE;
			TempCtrl_State = RUN_REFRIGERATOR;
		}
		else
		{
			Get_Heater_Duration(Heater_Target, Heater_Temper, &Heater_Duration);
			Set_Heater_Duration(Heater_Duration);
		}

		if( IsCoverHeated == FALSE )
		{
			if( Heater_Temper > Heater_Target - TARGETTEMP_DELTA ) // Delta is Defines
			{
				IsChamberCtrl = TRUE;
				IsCoverHeated = TRUE;
			}
		}
		#else
		if( Heater_Temper > 105 )
		{
			Heater_Temper = Heater_Temper - 0.5;
			LID_Temp_H = (unsigned char)(int)Heater_Temper;

			IsChamberCtrl = TRUE;
			IsCoverHeated = TRUE;
		}
		else
		{
			Heater_Temper = Heater_Temper + 0.5;
			LID_Temp_H = (unsigned char)(int)Heater_Temper;
		}

		#endif

		Set_Chamber_Duration(PWM_Dir, 0);
	}
	else
	{
		Heater = 0x00;
	}

	// Error Check
	Temp_ErrorCheck();

	// Wait until LID Heater is heated fully
	if( IsCoverHeated == FALSE ) return;
	
	// Chamber Temperature Control
	if( IsChamberCtrl == TRUE )
	{
		#if !defined(TESTER)

		float target_temp = (float)Chamber_Target;
		float d_t = Chamber_Temper - target_temp;
		
		if(d_t < 0.0) d_t = -d_t;
		// Determine PWM, Fan, Heater from current and target temp
		if( d_t < TARGETTEMP_DELTA )
			IsTargetArrived = TRUE;

		#else

		float target_temp = (float)Chamber_Target;
		float d_t = Chamber_Target - target_temp;
		if( d_t < 0.0 ) d_t = -d_t;
		if( d_t < 5.0 )
		{
			IsTargetArrived = TRUE;
		}
		if( Chamber_Temper > Chamber_Target ) Chamber_Temper = Chamber_Temper - 0.5;
		else Chamber_Temper = Chamber_Temper + 0.5;
			
		if( IsTargetArrived )
		{
			Chamber_Temper = Chamber_Target;
		}
		Chamber_Temp_H = (unsigned char)(int)Chamber_Temper;

		#endif

		Get_Chamber_Duration(Chamber_Temper);
		Set_Chamber_Duration(PWM_Dir, PWM_Duration);
	}
	else
	{
		#if !defined(TESTER)

		Stop_PWM_MODE();

		#else

		float u = (float)rand() / (RAND_MAX + 1) * 2.0 + -1.0;
		Heater_Temper = 25.0 + 0.2*cos(u);
		Chamber_Temper = 25.0 + 0.1*sin(u);

		#endif
	}

	// Check Refrigirator State
	if( Chamber_Temper <= REFRIGERATOR_TEMP )
	{
		Set_Heater_Duration(0);
		Cur_State = STATE_RUN;
		TempCtrl_State = RUN_REFRIGERATOR;
	}
}

/***************************************************
 * Function:        void Temp_ErrorCheck(void)
 *
 * OverView:		If Controling temperature detect error, set Error Value.
 *
 * Note:			None
 ***************************************************/
void Temp_ErrorCheck(void)
{
	// Detect Sensor Error
	if( (Heater_Temper < 0) || (Chamber_Temper < 0) || (Heatsink_Temper < 0) || (Heater_Temper > 128) || (Chamber_Temper > 128) || (Heatsink_Temper > 128 ) )
	{
		mLED_R_On();
		Set_Heater_Duration(0);
		Set_Chamber_Duration(0, 0);
		Cur_State = STATE_STOP;
		Fatal_Error = 255;
	}

	//	Error Protection
	if( Heater_Temper > LID_TEMP_LIMIT )
	{
		mLED_R_On();
		Set_Heater_Duration(0);
		Set_Chamber_Duration(0, 0);
		Cur_State = STATE_STOP;
		Fatal_Error++;
	}
	
	//	Detect Chamber Error
	if( Chamber_Temper > CHM_TEMP_LIMIT )
	{
		mLED_R_On();
		Set_Heater_Duration(0);
		Set_Chamber_Duration(0, 0);
		Cur_State = STATE_STOP;
		Fatal_Error = Fatal_Error + 2;
	}

	//	Detect Heatsink Error
	if( Heatsink_Temper > SINK_TEMP_LIMIT )
	{
		mLED_R_On();
		Set_Heater_Duration(0);
		Set_Chamber_Duration(0, 0);
		Cur_State = STATE_STOP;
		Fatal_Error = Fatal_Error + 4;
	}
}

/***************************************************
 * Function:        void Get_ChamberFan_Duration(float temp)
 *
 * OverView:		Get ChamberFan duration by chamber temperature
 *
 * Note:			None
 ***************************************************/
void Get_ChamberFan_Duration(float temp)
{
	if( temp < CHMFAN_TEMP_DURATION_0 ) Chamber_Fan_Duration = 0;
	if( temp > CHMFAN_TEMP_DURATION_50 ) Chamber_Fan_Duration = 50;
	if( temp > CHMFAN_TEMP_DURATION_100 ) Chamber_Fan_Duration = 100;

	if( Chamber_Target < 10 ) Chamber_Fan_Duration = 100;

	if( Chamber_Fan_Duration > 100 ) Chamber_Fan_Duration = 100;
	else if( Chamber_Fan_Duration < 0 ) Chamber_Fan_Duration = 0;
}

/***************************************************
 * Function:        void Set_ChamberFan_Duration(float duration)
 *
 * OverView:		Set ChamberFan Temperature by chamber duration.
 *
 * Note:			None
 ***************************************************/
void Set_ChamberFan_Duration(float duration)
{
	float PWM_MAX = CHM_FAN_DURATION;
	float pwm = duration/100. * PWM_MAX;
	int nPwm = 0;

	if( pwm >= PWM_MAX ) pwm = PWM_MAX;
	if( pwm <= 0 ) pwm = 0;
	nPwm = (int)pwm;

	Chamber_Fan = (BYTE)(nPwm&0x00FF);
}

/***************************************************
 * Function:        void Get_SystemFan_Duration(float temp)
 *
 * OverView:		Get SystemFan duration by SystemFan temperature
 *
 * Note:			None
 ***************************************************/
void Get_SystemFan_Duration(float temp)
{
	if( temp < SYSFAN_TEMP_DURATION_0 ) System_Fan_Duration = 0;
	if( temp > SYSFAN_TEMP_DURATION_50 ) System_Fan_Duration = 50;
	if( temp > SYSFAN_TEMP_DURATION_100 ) System_Fan_Duration = 100;

	//	Limit Duration
	if( System_Fan_Duration > 100 ) System_Fan_Duration = 100;
	else if( System_Fan_Duration < 0) System_Fan_Duration = 0;
}

/***************************************************
 * Function:        void Set_SystemFan_Duration(float duration)
 *
 * OverView:		Set SystemFan Temperature by SystemFan duration.
 *
 * Note:			None
 ***************************************************/
void Set_SystemFan_Duration(float duration)
{
	float PWM_MAX = CHM_FAN_DURATION;
	float pwm = duration/100. * PWM_MAX;
	int nPwm = 0;

	if( pwm >= PWM_MAX ) pwm = PWM_MAX;
	if( pwm <= 0 ) pwm = 0;
	nPwm = (int)pwm;

	System_Fan = (BYTE)(nPwm);	
}

/***************************************************
 * Function:        void Get_Heater_Duration(float targetTemp, float curTemp, float *duration)
 *
 * OverView:		Get Heater duration by heaterTemp, Current Temp at *duration
 *
 * Note:			None
 ***************************************************/
void Get_Heater_Duration(float targetTemp, float curTemp, float *duration)
{
	float p = 60.;
	float i = 45.;
	float d = 5.;
	float currentErr = 0;
	float Proportional = 0;
	float Integral = 0;
	float Derivative = 0;

	currentErr = targetTemp - curTemp;
	Proportional = p * currentErr;

	Integral = Heater_LastIntegral + i * (currentErr + Heater_LastErr);
	if( Integral > 99 ) Integral = 99;
	else if( Integral < 0 ) Integral = 0;

	Derivative = d * (currentErr - Heater_LastErr);

	*duration = Proportional + Integral + Derivative;

	if( *duration > 99 ) *duration = 99;
	else if( *duration < 0 ) *duration = 0;

	Heater_LastErr = currentErr;
	Heater_LastIntegral = Integral;
}

/***************************************************
 * Function:        void Set_Heater_Duration(float duration)
 *
 * OverView:		Set Heater by Heater duration.
 *
 * Note:			None
 ***************************************************/
void Set_Heater_Duration(float duration)
{
	float PWM_MAX = LID_HEATER_DURATION;
	float pwm = duration/100. * PWM_MAX;

	if( pwm >= PWM_MAX ) pwm = PWM_MAX;
	if( pwm <= 0 ) pwm = 0;
	
	Heater = (BYTE)pwm;
}

/***************************************************
 * Function:        void Get_Chamber_Duration(float temp)
 *
 * OverView:		Get Chamber duration by chamber temperature
 *
 * Note:			None
 ***************************************************/
void Get_Chamber_Duration(float temp)
{
	float currentErr = 0.;
	float Proportional = 0.;
	float Integral = 0.;
	float Derivative = 0.;
	float out = 0.;
	float IntPart = 0.;

	currentErr = Chamber_Target - temp;
	Proportional = Kp * currentErr;

	Integral = currentErr + Chamber_LastIntegral;

	if( Integral > 100 ) Integral = 100;
	else if( Integral < -100 ) Integral = -100;

	IntPart = Ki * Integral;
	Derivative = Kd * (currentErr - Chamber_LastErr);

	out = (Proportional + IntPart + Derivative);

	// Out Limits
	if( out > 99.0 ) PWM_Duration = 99;
	else if( out < -99.0) PWM_Duration = -99;
	else PWM_Duration = out;

	if( out < 0.0 ) PWM_Dir = 1;
	else PWM_Dir = 0;

	if( PWM_Duration < 0.0 ) PWM_Duration = -PWM_Duration;

	Chamber_LastErr = currentErr;
	Chamber_LastIntegral = Integral;
}

/***************************************************
 * Function:        void Set_Chamber_Duration(int dir, float duration)
 *
 * OverView:		Set PWM value By chamber duration.
 *
 * Note:			None
 ***************************************************/
void Set_Chamber_Duration(int dir, float duration)
{
	float PWM_MAX = CHAMBER_PWM_MAX;
	float pwm = 0;
	int nPwm = 0;

	pwm = duration/100. * PWM_MAX;

	if( pwm >= PWM_MAX ) pwm = PWM_MAX;
	if( pwm <= 0.0 ) pwm = 0;
	nPwm = (int)pwm;

	if( dir < 1 ) nPwm = (int)PWM_MAX - nPwm;
	
	PWM_L = (BYTE)nPwm;
	PWM_H = (BYTE)(nPwm>>8);

	CCPR1L = (BYTE)(nPwm>>2);
	CCP1CON = ((CCP1CON&0xCF) | (BYTE)((nPwm&0x03)<<4));

	// polar is config PWM Port.
	Switch_PWM_Port(dir);
}

