/**********************************************************************
* File: lab.h
* Device: TMS320F2806x
* Author: Technical Training Organization (TTO), Texas Instruments
* 				Juan Herrero Mac�as, Universidad Polit�cnica de Madrid
* Description: Include file for C28x workshop labs.  Include this
*   file in all C-source files.
* History:
*   10/14/11 - original
*   13/09/2012 - modifications for piccolo project
**********************************************************************/

#ifndef LAB_H
#define LAB_H

//---------------------------------------------------------------------------
// Include Standard C Language Header Files
//
#include <string.h>


//---------------------------------------------------------------------------
// Include any other Header Files
//
#include "F2806x_Device.h"				// F2806x header file peripheral address definitions
#include "F2806x_DefaultIsr.h"			// ISR definitions - used in Labs 2, 3 and 4


//---------------------------------------------------------------------------
// Constant Definitions
//
// To calculate the period of the sin envelope that the current will follow
// We need to update the DAC value 300 times (steps) to complete a sine. We want the sine to have a frequency of 100 Hz
// So we need to call to an interruption 300 * 100 = 30 kHz
#define ENVELOPE_SAMPLE_PERIOD	2666		// 2666 = 30 kHz sampling w/ 80 MHz SYSCLKOUT

#define SIN_DEFINITION 300 // Number of steps in which a sine wave is divided
#define SIN_AMPLITUDE 200 // The difference between the Peak of the sine and the lower hysteresis band. This values are refered to the DAC value of the internal comparator
#define PI 3.14159f
#define LOWER_HYSTERESIS_BAND 400 // Sine offset (DAC value at which the sine is zero)

extern int D;
extern int sinValues[SIN_DEFINITION];

extern int step;
extern int state;
extern int plain;

//---------------------------------------------------------------------------
// Function Prototypes
//
extern void DelayUs(Uint16);
extern void InitAdc(void);
extern void InitEPwm(void);
extern void InitFlash(void);
extern void InitGpio(void);
extern void InitPieCtrl(void);
extern void InitSysCtrl(void);
extern void InitWatchdog(void);
extern void SetDBGIER(Uint16);


//---------------------------------------------------------------------------
// Global symbols defined in the linker command file
//
extern Uint16 secureRamFuncs_loadstart;
extern Uint16 secureRamFuncs_loadsize;
extern Uint16 secureRamFuncs_runstart;


//---------------------------------------------------------------------------
// Global Variables References
extern Uint16 DEBUG_TOGGLE;
extern const struct PIE_VECT_TABLE PieVectTableInit;	// PieVectTableInit is always extern


//---------------------------------------------------------------------------
// Macros
//
#define Device_cal_func_ptr (void (*)(void))0x3D7C80


//---------------------------------------------------------------------------
#endif  // end of LAB_H definition


//--- end of file -----------------------------------------------------
