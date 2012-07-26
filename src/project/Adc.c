/**********************************************************************
* File: Adc.c -- File for Lab 3 and 4 (not used in Lab 2)
* Devices: TMS320F2802x
* Author: Technical Training Organization (TTO), Texas Instruments
* History:
*   03/30/09 - original
**********************************************************************/

#include "Lab.h"				// Main include file


/**********************************************************************
* Function: InitAdc()
*
* Description: Initializes the ADC on the F2802x
**********************************************************************/
void InitAdc(void)
{
	asm(" EALLOW");						// Enable EALLOW protected register access

//--- Reset the ADC module
// Note: The ADC is already reset after a DSP reset, but this example is just showing
// good coding practice to reset the peripheral before configuring it as you never
// know why the DSP has started the code over again from the beginning).  
	AdcRegs.ADCCTL1.bit.RESET = 1;		// Reset the ADC

// Must wait 2 ADCCLK periods for the reset to take effect.
// Note that ADCCLK = SYSCLKOUT for F2802x/F2803x devices.
	asm(" NOP");
	asm(" NOP");
	
//--- Power-up and configure the ADC
	AdcRegs.ADCCTL1.all = 0x00E4;		// Power-up reference and main ADC
// bit 15        0:      RESET, ADC software reset, 0=no effect, 1=resets the ADC
// bit 14        0:      ADCENABLE, ADC enable, 0=disabled, 1=enabled
// bit 13        0:      ADCBSY, ADC busy, read-only
// bit 12-8      0's:    ADCBSYCHN, ADC busy channel, read-only
// bit 7         1:      ADCPWDN, ADC power down, 0=powered down, 1=powered up
// bit 6         1:      ADCBGPWD, ADC bandgap power down, 0=powered down, 1=powered up 
// bit 5         1:      ADCREFPWD, ADC reference power down, 0=powered down, 1=powered up 
// bit 4         0:      reserved
// bit 3         0:      ADCREFSEL, ADC reference select, 0=internal, 1=external
// bit 2         1:      INTPULSEPOS, INT pulse generation, 0=start of conversion, 1=end of conversion
// bit 1         0:      VREFLOCONV, VREFLO convert, 0=VREFLO not connected, 1=VREFLO connected to B5
// bit 0         0:      Must write as 0.

	DelayUs(1000);						// Wait 1 ms after power-up before using the ADC

//--- SOC0 configuration
	AdcRegs.ADCSAMPLEMODE.bit.SIMULEN0 = 0;		// SOC0 in single sample mode (vs. simultaneous mode)

	AdcRegs.ADCSOC0CTL.bit.TRIGSEL = 7;			// Trigger using ePWM2-ADCSOCA
	AdcRegs.ADCSOC0CTL.bit.CHSEL = 0;			// Convert channel ADCINA0 (ch0)
	AdcRegs.ADCSOC0CTL.bit.ACQPS = 6;			// Acquisition window set to (6+1)=7 cycles

	AdcRegs.ADCINTSOCSEL1.bit.SOC0 = 0;			// No ADCINT triggers SOC0.  TRIGSEL field determines trigger.

	AdcRegs.SOCPRICTL.bit.SOCPRIORITY = 0;		// All SOCs handled in round-robin mode

//--- ADCINT1 configuration
	AdcRegs.INTSEL1N2.bit.INT1CONT = 1;			// ADCINT1 pulses regardless of ADCINT1 flag state
	AdcRegs.INTSEL1N2.bit.INT1E = 1;			// Enable ADCINT1
	AdcRegs.INTSEL1N2.bit.INT1SEL = 0;			// EOC0 triggers ADCINT1

	PieCtrlRegs.PIEIER1.bit.INTx1 = 1;			// Enable ADCINT1 in PIE group 1
	IER |= 0x0001;								// Enable INT1 in IER to enable PIE group

//--- Finish up
	AdcRegs.ADCCTL1.bit.ADCENABLE = 1;	// Enable the ADC
	asm(" EDIS");						// Disable EALLOW protected register access

} // end InitAdc()


//--- end of file -----------------------------------------------------
