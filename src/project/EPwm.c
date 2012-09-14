/**********************************************************************
* File: EPwm.c -- File for Lab 3 and 4
* Devices: TMS320F2802x
* Author: Technical Training Organization (TTO), Texas Instruments
* History:
*   03/30/09 - original
**********************************************************************/

#include "Lab.h"				// Main include file


/**********************************************************************
* Function: InitEPwm()
*
* Description: Initializes the Enhanced PWM modules on the F2802x
**********************************************************************/
void InitEPwm(void)
{
//---------------------------------------------------------------------
//--- Must disable the clock to the ePWM modules if you       
//--- want all ePMW modules synchronized.
//---------------------------------------------------------------------
	asm(" EALLOW");						// Enable EALLOW protected register access
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;
	asm(" EDIS");						// Disable EALLOW protected register access

//---------------------------------------------------------------------
//--- Configure ePWM1
//---------------------------------------------------------------------
	// 1. Time Base Module
	EPwm1Regs.TBCTL.bit.CTRMODE = 0x3;		// Disable the timer

	EPwm1Regs.TBCTL.all = 0xC033;			// Configure timer control register
// bit 15-14     11:     FREE/SOFT, 11 = ignore emulation suspend
// bit 13        0:      PHSDIR, 0 = count down after sync event
// bit 12-10     000:    CLKDIV, 000 => TBCLK = HSPCLK/1
// bit 9-7       000:    HSPCLKDIV, 000 => HSPCLK = SYSCLKOUT/1
// bit 6         0:      SWFSYNC, 0 = no software sync produced
// bit 5-4       11:     SYNCOSEL, 11 = sync-out disabled
// bit 3         0:      PRDLD, 0 = reload PRD on counter=0
// bit 2         0:      PHSEN, 0 = phase control disabled --> Set as Master Module
// bit 1-0       11:     CTRMODE, 11 = timer stopped (disabled)

	EPwm1Regs.TBCTR = 0x0000;				// Clear timer counter
	EPwm1Regs.TBPRD = PWM_PERIOD;		// Set timer period
	EPwm1Regs.TBPHS.half.TBPHS = 0x0000;	// Set timer phase to 0

	// 2. Compare Module --> We don't need this module set for this example
//	EPwm1Regs.CMPA.half.CMPA = PWM_DUTY_CYCLE;	// Set PWM duty cycle

//	EPwm1Regs.CMPCTL.all = 0x0002;			// Compare control register
// bit 15-10     0's:    reserved
// bit 9         0:      SHDWBFULL, read-only
// bit 8         0:      SHDWAFULL, read-only
// bit 7         0:      reserved
// bit 6         0:      SHDWBMODE 0 = shadow mode
// bit 5         0:      reserved
// bit 4         0:      SHDWAMODE, 0 = shadow mode
// bit 3-2       00:     LOADBMODE, don't care
// bit 1-0       10:     LOADAMODE, 10 = load on zero or PRD match

	// 3. Action-Qualifier Module
//	EPwm1Regs.AQCTLA.all = 0x0064;		// Action-qualifier control register A
// bit 15-12     0000:   reserved
// bit 11-10     00:     CBD, 00 = do nothing
// bit 9-8       00:     CBU, 00 = do nothing
// bit 7-6       01:     CAD, 01 = clear
// bit 5-4       10:     CAU, 10 = set
// bit 3-2       00:     PRD, 01 = clear
// bit 1-0       00:     ZRO, 00 = do nothing

//	EPwm1Regs.AQCTLB.all = 0x0090;		// Action-qualifier control register B
// bit 15-12     0000:   reserved
// bit 11-10     00:     CBD, 00 = do nothing
// bit 9-8       00:     CBU, 00 = do nothing
// bit 7-6       01:     CAD, 10 = set
// bit 5-4       10:     CAU, 01 = clear
// bit 3-2       00:     PRD, 00 = do nothing
// bit 1-0       00:     ZRO, 00 = do nothing

//	EPwm1Regs.AQSFRC.all = 0x0000;		// Action-qualifier s/w force register
// bit 15-8      0's:    reserved
// bit 7-6       00:     RLDCSF, 00 = reload AQCSFRC on zero
// bit 5         0:      OTSFB, 0 = do not initiate a s/w forced event on output B
// bit 4-3       00:     ACTSFB, don't care
// bit 2         0:      OTSFA, 0 = do not initiate a s/w forced event on output A
// bit 1-0       00:     ACTSFA, don't care

//	EPwm1Regs.AQCSFRC.all = 0x0000;		// Action-qualifier continuous s/w force register
// bit 15-4      0's:    reserved
// bit 3-2       00:     CSFB, 00 = forcing disabled
// bit 1-0       00:     CSFA, 00 = forcing disabled


	// 4. Deadband
	EPwm1Regs.DBCTL.bit.OUT_MODE = 11;	// Deadband enabled for EpwmA & EpwmB
	EPwm1Regs.DBCTL.bit.IN_MODE = 00;   // Select EpwmA as input for Rise and Falling Edges
	EPwm1Regs.DBCTL.bit.POLSEL = 10;
	EPwm1Regs.DBCTL.bit.HALFCYCLE = 0;
	EPwm1Regs.DBRED = 2;	// Each clock cycle lasts 1/60MHz = 16,66666 ns. We'll need different dead bands in each converter
	EPwm1Regs.DBFED = 2;

	// 5. PWM Chopper Module
	EPwm1Regs.PCCTL.bit.CHPEN = 0;		// PWM chopper unit disabled

	// 6. Trip Zone and DC Compare Modules
	EPwm1Regs.TZDCSEL.all = 0x0000;		// All trip zone and DC compare actions disabled

		// Clear EPwm1A when the input in the comparator 1 is higher than the reference
				EPwm1Regs.DCTRIPSEL.bit.DCAHCOMPSEL = 1000; // Select the source for the Digital Compare A High (DCAH) input
						//	0000 TZ1 input
						//	0001 TZ2 input
						//	0010 TZ3 input
						//	1000 COMP1OUT input
						//	1001 COMP2OUT input

				// Once set the event signal creation, we want the Trip-Zone Submodule to catch the event and handle it
				EPwm1Regs.TZDCSEL.bit.DCAEVT2 = 010; //The event signal DCAEVT2 will be sent when Comp1Out goes high
						//	000 Event disabled
						//	001 DCAH = low, DCAL = don't care
						//	010 DCAH = high, DCAL = don't care
						//	011 DCAL = low, DCAH = don't care
						//	100 DCAL = high, DCAH = don't

				EPwm1Regs.DCACTL.bit.EVT2SRCSEL = 0; // Here we choose if we want to filter the signal
						// 0 Source is DCAEVT Signal
						// 1 Source is DCAEVTFILT Signal

				EPwm1Regs.DCACTL.bit.EVT2FRCSYNCSEL = 0;  // Force Sync Signal Select
						// 0 Source is Sync signal
						// 1 Source is Async Signal

				EPwm1Regs.TZSEL.bit.DCAEVT2 = 1;
						// 1 Enable DCAEVT2 as a CBC trip source event for this ePWM module

				EPwm1Regs.TZCTL.bit.TZA = 10; // When a trip event occurs the following action is taken on output EPwm1A
						//	00 High-impedance (EPWMxA = High-impedance state)
						//	01 Force EPWMxA to a high state.
						//	10 Force EPWMxA to a low state.
						//	11 Do Nothing, trip action is disabled

		// Set EPwm1B when the input in the comparator 2 is lower than the reference
				EPwm1Regs.DCTRIPSEL.bit.DCBLCOMPSEL = 1001; // Digital Compare B Low Input Select
						//	0000 TZ1 input
						//	0001 TZ2 input
						//	0010 TZ3 input
						//	1000 COMP1OUT input
						//	1001 COMP2OUT input

				// Once set the event signal creation, we want the Trip-Zone Submodule to catch the event and handle it
				EPwm1Regs.TZDCSEL.bit.DCBEVT2 = 011; //The event signal DCAEVT2 will be sent when Comp2Out goes low
						//	000 Event disabled
						//	001 DCBH = low, DCBL = don't care
						//	010 DCBH = high, DCBL = don't care
						//	011 DCBL = low, DCBH = don't care
						//	100 DCBL = high, DCBH = don't

				EPwm1Regs.DCBCTL.bit.EVT2SRCSEL = 0; // Here we choose if we want to filter the signal
						// 0 Source is DCBEVT Signal
						// 1 Source is DCBEVTFILT Signal

				EPwm1Regs.DCBCTL.bit.EVT2FRCSYNCSEL = 0;  // Force Sync Signal Select
						// 0 Source is Sync signal
						// 1 Source is Async Signal

				EPwm1Regs.TZSEL.bit.DCBEVT2 = 1;
						// 1 Enable DCBEVT2 as a CBC trip source event for this ePWM module

				EPwm1Regs.TZCTL.bit.TZB = 01; // When a trip event occurs the following action is taken on output EPwm1A
						//	00 High-impedance (EPWMxB = High-impedance state)
						//	01 Force EPWMxB to a high state.
						//	10 Force EPWMxB to a low state.
						//	11 Do Nothing, trip action is disabled

	// 7. Set the timer
	EPwm1Regs.TBCTL.bit.CTRMODE = 0x0;	// Enable the timer in count up mode
// 0 Count Up || 1 Count Down || 2 Count Up/Down


//---------------------------------------------------------------------
//--- Enable the clocks to the ePWM module.                   
//--- Note: this should be done after all ePWM modules are configured
//--- to ensure synchronization between the ePWM modules.
//---------------------------------------------------------------------
	asm(" EALLOW");							// Enable EALLOW protected register access
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;	// TBCLK to ePWM modules enabled
	asm(" EDIS");							// Disable EALLOW protected register access

} // end InitEPwm()


//--- end of file -----------------------------------------------------
