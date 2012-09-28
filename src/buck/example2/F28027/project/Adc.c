/**********************************************************************
* File: Adc.c
* Devices: TMS320F2802x
* Author: Technical Training Organization (TTO), Texas Instruments
* 				Juan Herrero Macías, Universidad Politécnica de Madrid
* History:
*   03/30/09 - original
*   13/09/2012 - modifications for piccolo project
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

	//--- Comparator 1 Configuration --> If (input + > input -) --> CompOut = 1
														// If (input + < input -) --> CompOut = 0
		Comp1Regs.COMPCTL.bit.COMPDACEN = 1; // Enable Comparator 1
		Comp1Regs.COMPCTL.bit.CMPINV = 0; // If you want to invert the output
		Comp1Regs.COMPCTL.bit.COMPSOURCE = 0;	// 1  Both comparator inputs connected to external pin
																			// 0 Input - is generated internally via DAC and compared to an input  + which is an external pin
		Comp1Regs.COMPCTL.bit.SYNCSEL = 0; //Asynchronous Comp1 Output
		Comp1Regs.COMPCTL.bit.QUALSEL =  0; // Don't Care

		Comp1Regs.DACVAL.bit.DACVAL = 500; // 10 bits [0-1023] Not used this time. Generates V = DACVAL * 3.3 / 1023 on DAC signal

	//--- Comparator 2 Configuration --> If (input + > input -) --> CompOut = 1
														// If (input + < input -) --> CompOut = 0
		Comp2Regs.COMPCTL.bit.COMPDACEN = 1; // Enable Comparator 2
		Comp2Regs.COMPCTL.bit.CMPINV = 0; // If you want to invert the output
		Comp2Regs.COMPCTL.bit.COMPSOURCE = 0;	// 1  Both comparator inputs connected to external pin
																			// 0 Input - is generated internally via DAC and compared to an input  + which is an external pin
		Comp2Regs.COMPCTL.bit.SYNCSEL = 0; //Asynchronous Comp1 Output
		Comp2Regs.COMPCTL.bit.QUALSEL =  0; // Don't Care
		Comp2Regs.DACVAL.bit.DACVAL = 0; // 10 bits [0-1023] Not used this time. Generates V = DACVAL * 3.3 / 1023 on DAC signal

		AdcRegs.ADCCTL1.bit.ADCBGPWD = 1; // It's already been enabled, but it's necessary to enable it for the comparator to work

//--- Finish up
	AdcRegs.ADCCTL1.bit.ADCENABLE = 1;	// Enable the ADC
	asm(" EDIS");						// Disable EALLOW protected register access

} // end InitAdc()


//--- end of file -----------------------------------------------------
