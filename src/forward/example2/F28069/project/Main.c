/**********************************************************************
* File: Main_3.c -- File for Lab 3
* Devices: TMS320F2806x
* Author: Technical Training Organization (TTO), Texas Instruments
* 				Juan Herrero Macías, Universidad Politécnica de Madrid
* History:
*   10/14/11 - original
*   13/09/2012 - modifications for piccolo project
**********************************************************************/

#include "Lab.h"						// Main include file
#include "math.h"

//--- Global Variable
Uint16 DEBUG_TOGGLE = 1;					// Used for realtime mode investigation test
int D = 1;  // While D = 1, the current hasnt reached the hysteresis cycle
int step = 0;
int sinValues[SIN_DEFINITION];

/**********************************************************************
* Function: main()
*
* Description: Main function for C28x workshop labs
**********************************************************************/

void main(void)
{
//--- CPU Initialization
	InitSysCtrl();						// Initialize the CPU (FILE: SysCtrl.c)
	InitGpio();							// Initialize the shared GPIO pins (FILE: Gpio.c)
	InitPieCtrl();						// Initialize and enable the PIE (FILE: PieCtrl.c)
	InitWatchdog();						// Initialize the Watchdog Timer (FILE: WatchDog.c)

//--- Peripheral Initialization
	InitAdc();							// Initialize the ADC (FILE: Adc.c)
	InitEPwm();							// Initialize the EPwm (FILE: EPwm.c) 

	int d;
	for (d = 0; d < SIN_DEFINITION; d++) {
		sinValues[d] = (int)(fabs(sin(d * 180.f / SIN_DEFINITION * 2 * PI / 360)) * SIN_AMPLITUDE) + LOWER_HYSTERESIS_BAND;
	}


// Variable Initialization
 	asm (" ESTOP0");							// Emulator Halt instruction

//--- Enable global interrupts
		// Enable global interrupts and realtime debug
	asm("DBGM");

	 //--- Main Loop
	// Force EPwm1 high
	EPwm1Regs.AQCSFRC.bit.CSFA = 2; // Invoke One-Time Software Forced Event on Output A
//	EPwm1Regs.AQSFRC.bit.OTSFA = 1;

	asm(" CLRC INTM");

	 //--- Main Loop
	 	while(1)							// endless loop - wait for an interrupt
	 	{
	 		asm(" NOP");
	 	}

} //end of main()

/*** end of file *****************************************************/
