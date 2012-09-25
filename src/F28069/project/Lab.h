/**********************************************************************
* File: lab.h
* Device: TMS320F2806x
* Author: Technical Training Organization (TTO), Texas Instruments
* Description: Include file for C28x workshop labs.  Include this
*   file in all C-source files.
* History:
*   10/14/11 - original
**********************************************************************/

#ifndef LAB_H
#define LAB_H

extern int D;

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
#define ADC_BUF_LEN			50				// ADC buffer length
#define ADC_SAMPLE_PERIOD	1599			// 1599 = 50 kHz sampling w/ 80 MHz SYSCLKOUT
#define PWM_HALF_PERIOD		20000			// period/2 for 2 kHz symmetric PWM w/ 80 MHz SYSCLKOUT
#define PWM_DUTY_CYCLE		15000			// 25% duty cycle


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
//
extern Uint16 AdcBuf[ADC_BUF_LEN];
extern Uint16 DEBUG_TOGGLE;
extern const struct PIE_VECT_TABLE PieVectTableInit;	// PieVectTableInit is always extern


//---------------------------------------------------------------------------
// Macros
//
#define Device_cal_func_ptr (void (*)(void))0x3D7C80


//---------------------------------------------------------------------------
#endif  // end of LAB_H definition


//--- end of file -----------------------------------------------------
