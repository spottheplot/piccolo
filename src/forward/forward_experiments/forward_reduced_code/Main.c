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
// EPWM1 Global Variable
short int lastPos = 2;
	// 1 High
	// 0 Low
	// 2 First time

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
		sinValues[d] = UPPER_HYSTERESIS_BAND;//(int)(fabs(sin(d * 180.f / SIN_DEFINITION * 2 * PI / 360)) * SIN_AMPLITUDE) + LOWER_HYSTERESIS_BAND;
	}


// Variable Initialization
	// asm (" ESTOP0");							// Emulator Halt instruction¡

//--- Enable global interrupts
		// Enable global interrupts and realtime debug
	 // asm("DBGM");

	 // asm(" CLRC INTM");

	 GpioDataRegs.GPACLEAR.bit.GPIO2 = 1;

	 asm (" ESTOP0");

	 GpioDataRegs.GPASET.bit.GPIO2 = 1;

	 //--- Main Loop
	 	while(1)							// endless loop - wait for an interrupt
	 	{
	 		if (Comp1Regs.COMPSTS.bit.COMPSTS == 1 && (lastPos == 0 || lastPos == 2)) {

	 				GpioDataRegs.GPACLEAR.bit.GPIO2 = 1;

	 				lastPos = 1;
	 			}
	 			// If DCAEVT2 generated this interruption
	 			if (Comp2Regs.COMPSTS.bit.COMPSTS == 0 &&  (lastPos == 1 || lastPos == 2)) {
	 				GpioDataRegs.GPASET.bit.GPIO2 = 1;

	 				lastPos = 0;
	 			}
//	 		asm(" NOP");
	 	}

} //end of main()

/*** end of file *****************************************************/
