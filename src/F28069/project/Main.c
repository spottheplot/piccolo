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

//--- Global Variables
Uint16 AdcBuf[ADC_BUF_LEN];					// ADC buffer allocation
Uint16 DEBUG_TOGGLE = 1;					// Used for realtime mode investigation test
int D = 1;  // While D = 1, the current hasnt reached the hysteresis cycle
int step = 440;
int state = 0;
int plain = 0;


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

// Variable Initialization
	asm (" ESTOP0");							// Emulator Halt instruction
	int i = 0;


//--- Enable global interrupts
		// Enable global interrupts and realtime debug
	asm("DBGM");

	asm(" CLRC INTM");

	 //--- Main Loop
	 	while(D)							// endless loop - wait for an interrupt
	 	{
	 		i ++;
	 		if (i == 600) {

	 			EPwm1Regs.AQSFRC.bit.ACTSFA = 1; //  What to do when One-Time Software Forced Event is invoked
	 						//	00 Does nothing (action disabled)
	 						//	01 Clear (low)
	 						//	10 Set (high)
	 						//	11 Toggle
	 			EPwm1Regs.AQSFRC.bit.OTSFA = 1; // Invoke One-Time Software Forced Event on Output A

	 			EPwm1Regs.AQSFRC.bit.ACTSFB = 2; //  What to do when One-Time Software Forced Event is invoked
	 						//	00 Does nothing (action disabled)
	 						//	01 Clear (low)
	 						//	10 Set (high)
	 						//	11 Toggle
	 			EPwm1Regs.AQSFRC.bit.OTSFB = 1; // Invoke One-Time Software Forced Event on Output A
	 			i = 0;
	 		}
	 	}

	 //--- Main Loop
	 	while(1)							// endless loop - wait for an interrupt
	 	{
	 		asm(" NOP");
	 	}

} //end of main()

/*** end of file *****************************************************/
