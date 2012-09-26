/**********************************************************************
* File: EPwm.c -- File for Lab 3 and 4
* Devices: TMS320F2806x
* Author: Technical Training Organization (TTO), Texas Instruments
* 				Juan Herrero Macías, Universidad Politécnica de Madrid
* History:
*   10/14/11 - original
*   13/09/2012 - modifications for piccolo project
**********************************************************************/

#include "Lab.h"				// Main include file


/**********************************************************************
* Function: InitEPwm()
*
* Description: Initializes the Enhanced PWM modules on the F2806x
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
	//--- Configure ePWM2 to trigger the ADC at a 50 kHz rate
	//---------------------------------------------------------------------
		EPwm2Regs.TBCTL.bit.CTRMODE = 0x3;		// Disable the timer

		EPwm2Regs.TBCTL.all = 0xC033;			// Configure timer control register
	// bit 15-14     11:     FREE/SOFT, 11 = ignore emulation suspend
	// bit 13        0:      PHSDIR, 0 = count down after sync event
	// bit 12-10     000:    CLKDIV, 000 => TBCLK = HSPCLK/1
	// bit 9-7       000:    HSPCLKDIV, 000 => HSPCLK = SYSCLKOUT/1
	// bit 6         0:      SWFSYNC, 0 = no software sync produced
	// bit 5-4       11:     SYNCOSEL, 11 = sync-out disabled
	// bit 3         0:      PRDLD, 0 = reload PRD on counter=0
	// bit 2         0:      PHSEN, 0 = phase control disabled
	// bit 1-0       11:     CTRMODE, 11 = timer stopped (disabled)

		EPwm2Regs.TBCTR = 0x0000;				// Clear timer counter
		EPwm2Regs.TBPRD = ADC_SAMPLE_PERIOD;	// Set timer period
		EPwm2Regs.TBPHS.half.TBPHS = 0x0000;	// Set timer phase

		EPwm2Regs.ETPS.all = 0x0100;			// Configure SOCA
	// bit 15-14     00:     EPWMxSOCB, read-only
	// bit 13-12     00:     SOCBPRD, don't care
	// bit 11-10     00:     EPWMxSOCA, read-only
	// bit 9-8       01:     SOCAPRD, 01 = generate SOCA on first event
	// bit 7-4       0000:   reserved
	// bit 3-2       00:     INTCNT, don't care
	// bit 1-0       00:     INTPRD, don't care

		EPwm2Regs.ETSEL.all = 0x0A00;			// Enable SOCA to ADC
	// bit 15        0:      SOCBEN, 0 = disable SOCB
	// bit 14-12     000:    SOCBSEL, don't care
	// bit 11        1:      SOCAEN, 1 = enable SOCA
	// bit 10-8      010:    SOCASEL, 010 = SOCA on PRD event
	// bit 7-4       0000:   reserved
	// bit 3         0:      INTEN, 0 = disable interrupt
	// bit 2-0       000:    INTSEL, don't care

		EPwm2Regs.TBCTL.bit.CTRMODE = 0x0;		// Enable the timer in count up mode



//---------------------------------------------------------------------
//--- Configure ePWM1
//---------------------------------------------------------------------
	// 1. Time Base Module
//	EPwm1Regs.TBCTL.bit.CTRMODE = 0x3;		// Disable the timer
//
//	EPwm1Regs.TBCTL.all = 0xC033;			// Configure timer control register
//// bit 15-14     11:     FREE/SOFT, 11 = ignore emulation suspend
//// bit 13        0:      PHSDIR, 0 = count down after sync event
//// bit 12-10     000:    CLKDIV, 000 => TBCLK = HSPCLK/1
//// bit 9-7       000:    HSPCLKDIV, 000 => HSPCLK = SYSCLKOUT/1
//// bit 6         0:      SWFSYNC, 0 = no software sync produced
//// bit 5-4       11:     SYNCOSEL, 11 = sync-out disabled
//// bit 3         0:      PRDLD, 0 = reload PRD on counter=0
//// bit 2         0:      PHSEN, 0 = phase control disabled
//// bit 1-0       11:     CTRMODE, 11 = timer stopped (disabled)
//
//	EPwm1Regs.TBCTR = 0x0000;				// Clear timer counter
//	EPwm1Regs.TBPRD = PWM_HALF_PERIOD;		// Set timer period
//	EPwm1Regs.TBPHS.half.TBPHS = 0x0000;	// Set timer phase
//
////	 2. Compare Module --> We don't need this module set for this example
//	EPwm1Regs.CMPA.half.CMPA = PWM_DUTY_CYCLE;	// Set PWM duty cycle
//
//	EPwm1Regs.CMPCTL.all = 0x0002;			// Compare control register
//// bit 15-10     0's:    reserved
//// bit 9         0:      SHDWBFULL, read-only
//// bit 8         0:      SHDWAFULL, read-only
//// bit 7         0:      reserved
//// bit 6         0:      SHDWBMODE, don't care
//// bit 5         0:      reserved
//// bit 4         0:      SHDWAMODE, 0 = shadow mode
//// bit 3-2       00:     LOADBMODE, don't care
//// bit 1-0       10:     LOADAMODE, 10 = load on zero or PRD match
//
//	// 3. Action-Qualifier Module
//	EPwm1Regs.AQCTLA.all = 0x0000;//0x0060;		// Action-qualifier control register A
//// bit 15-12     0000:   reserved
//// bit 11-10     00:     CBD, 00 = do nothing
//// bit 9-8       00:     CBU, 00 = do nothing
//// bit 7-6       01:     CAD, 01 = clear
//// bit 5-4       10:     CAU, 10 = set
//// bit 3-2       00:     PRD, 00 = do nothing
//// bit 1-0       00:     ZRO, 00 = do nothing
//
//	EPwm1Regs.AQCTLB.all = 0x0000;		// Action-qualifier control register B
//// bit 15-12     0000:   reserved
//// bit 11-10     00:     CBD, 00 = do nothing
//// bit 9-8       00:     CBU, 00 = do nothing
//// bit 7-6       01:     CAD, 10 = do nothing
//// bit 5-4       10:     CAU, 01 = do nothing
//// bit 3-2       00:     PRD, 00 = do nothing
//// bit 1-0       00:     ZRO, 00 = do nothing
//
//	EPwm1Regs.AQSFRC.all = 0x0000;		// Action-qualifier s/w force register
//// bit 15-8      0's:    reserved
//// bit 7-6       00:     RLDCSF, 00 = reload AQCSFRC on zero
//// bit 5         0:      OTSFB, 0 = do not initiate a s/w forced event on output B
//// bit 4-3       00:     ACTSFB, don't care
//// bit 2         0:      OTSFA, 0 = do not initiate a s/w forced event on output A
//// bit 1-0       00:     ACTSFA, don't care
//
//	EPwm1Regs.AQCSFRC.all = 0x0000;		// Action-qualifier continuous s/w force register
//// bit 15-4      0's:    reserved
//// bit 3-2       00:     CSFB, 00 = forcing disabled
//// bit 1-0       00:     CSFA, 00 = forcing disabled

	// 4. Deadband
	EPwm1Regs.DBCTL.bit.OUT_MODE = 3; // Deadband disabled until we manage to make it work
	EPwm1Regs.DBCTL.bit.IN_MODE = 0;   // Select EpwmA as input for Rise and Falling Edges
	EPwm1Regs.DBCTL.bit.POLSEL = 2;
	EPwm1Regs.DBCTL.bit.HALFCYCLE = 0;
	EPwm1Regs.DBRED = 2;	// Each clock cycle lasts 1/60MHz = 16,66666 ns. We'll need different dead bands in each converter
	EPwm1Regs.DBFED = 2;


	// 5. PWM Chopper Module
	EPwm1Regs.PCCTL.bit.CHPEN = 0;		// PWM chopper unit disabled

	// 6. Trip Zone and DC Compare Modules
	asm(" EALLOW");						// Enable EALLOW protected register access

		EPwm1Regs.TZDCSEL.all = 0x0000;		// All trip zone and DC compare actions disabled

		// Clear EPwm1A when the input in the comparator 1 is higher than the reference (by generating DCAEVT1)
				EPwm1Regs.DCTRIPSEL.bit.DCAHCOMPSEL = 8; // Select the source for the Digital Compare A High (DCAH) input --> Comp1Out = DCAH
						//	0000 TZ1 input
						//	0001 TZ2 input
						//	0010 TZ3 input
						//	1000 COMP1OUT input
						//	1001 COMP2OUT input
						// 1010 COMP3OUT input

				// Once set the event signal creation, we want the Trip-Zone Submodule to catch the event and handle it
				EPwm1Regs.TZDCSEL.bit.DCAEVT1 = 2;//1; //The event signal DCAEVT1 will be sent when Comp1Out goes high (DCAH High)
						//	0 || 000 Event disabled
						//	1 || 001 DCAH = low, DCAL = don't care
						//	2 || 010 DCAH = high, DCAL = don't care
						//	3 || 011 DCAL = low, DCAH = don't care
						//	4 || 100 DCAL = high, DCAH = don't care
						//	5 || 101 DCAL = high, DCAH = low

				EPwm1Regs.DCACTL.bit.EVT2SRCSEL = 0; // Here we choose if we want to filter the signal
						// 0 Source is DCAEVT Signal
						// 1 Source is DCAEVTFILT Signal

				EPwm1Regs.DCACTL.bit.EVT2FRCSYNCSEL = 1;  // Force Sync Signal Select
						// 0 Source is Sync signal
						// 1 Source is Async Signal

//				EPwm1Regs.TZSEL.bit.DCAEVT1 = 0;
						// 1 Disable DCAEVT2 as a CBC trip source event for this ePWM module

				EPwm1Regs.TZCTL.bit.DCAEVT1 = 2; // When a trip event occurs the following action is taken on output EPwm1A
						//0 || 	00 High-impedance (EPWMxA = High-impedance state)
						//	1 || 01 Force EPWMxA to a high state.
						//	2 || 10 Force EPWMxA to a low state.
						//	3 || 11 Do Nothing, trip action is disabled

				EPwm1Regs.TZEINT.bit.DCAEVT1 = 1; //Digital Comparator Output A Event 2 Interrupt Enable
										//0 Disabled
										//1 Enabled

		// Set EPwm1A when the input in the comparator 2 is lower than the reference (by generating DCAEVT2)
				EPwm1Regs.DCTRIPSEL.bit.DCALCOMPSEL = 9; // Digital Compare A Low Input Select
						//	0 || 0000 TZ1 input
						//	1 || 0001 TZ2 input
						//	2 || 0010 TZ3 input
						//	8 || 1000 COMP1OUT input
						//	9 || 1001 COMP2OUT input
						// 10 ||1010 COMP3OUT input

				// Once set the event signal creation, we want the Trip-Zone Submodule to catch the event and handle it
				EPwm1Regs.TZDCSEL.bit.DCAEVT2 = 3; //The event signal DCAEVT2 will be sent when Comp2Out goes low (DCAL Low)
						//	0 || 000 Event disabled
						//	1 || 001 DCAH = low, DCAL = don't care
						//	2 || 010 DCAH = high, DCAL = don't care
						//	3 || 011 DCAL = low, DCAH = don't care
						//	4 || 100 DCAL = high, DCAH = don't
						//	5 || 101 DCAL = high, DCAH = low

				EPwm1Regs.DCACTL.bit.EVT2SRCSEL = 0; // Here we choose if we want to filter the signal
						// 0 Source is DCAEVT Signal
						// 1 Source is DCBEVTFILT Signal

				EPwm1Regs.DCACTL.bit.EVT2FRCSYNCSEL = 1;  // Force Sync Signal Select
						// 0 Source is Sync signal
						// 1 Source is Async Signal

//				EPwm1Regs.TZSEL.bit.DCAEVT1 = 0;
						// 1 Enable DCBEVT2 as a CBC trip source event for this ePWM module

				EPwm1Regs.TZCTL.bit.DCAEVT2 = 3; // When a trip event occurs the following action is taken on output EPwmxA
				//Commented because it introduces noise in the signal when activated
						//0 || 00 High-impedance (EPWMxB = High-impedance state)
						//	1 || 01 Force EPWMxA to a high state.
						//	2 || 10 Force EPWMxA to a low state.
						//	3 || 11 Do Nothing, trip action is disabled

				EPwm1Regs.TZEINT.bit.DCAEVT2 = 1; //Digital Comparator Output A Event 2 Interrupt Enable
						//0 Disabled
						//1 Enabled

				// Enable PIE interrupts from TZ for EPwm1 (EPWM1_TZINT)
				PieCtrlRegs.PIEIER2.bit.INTx1 = 1; // Enable EPWM_TZINT in PIE group 2
				IER |= 0x0002; // Enable INT2 in IER to enable PIE group 2

		asm(" EDIS");						// Disable EALLOW protected register access

	// 7. Set the timer
//	EPwm1Regs.TBCTL.bit.CTRMODE = 0x2;	// Enable the timer in count up/down mode

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
