/**********************************************************************
* File: Adc.c -- File for Lab 3 and 4 (not used in Lab 2)
* Devices: TMS320F2806x
* Author: Technical Training Organization (TTO), Texas Instruments
* 				Juan Herrero Macías, Universidad Politécnica de Madrid
* History:
*   10/14/11 - original
*   13/09/2012 - modifications for piccolo project
**********************************************************************/

#include "Lab.h"				// Main include file


/**********************************************************************
* Function: InitAdc()
*
* Description: Initializes the ADC on the F2806x
**********************************************************************/
void InitAdc(void)
{
	asm(" EALLOW");						// Enable EALLOW protected register access
	
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
// bit 0         0:      TEMPCONV, Temperature sensor convert.  0=ADCINA5 is pin, 1=ADCINA5 is temp sensor

	AdcRegs.ADCCTL2.all = 0x0001;		// ADC clock configuration
// bit 15-3      0's:    reserved
// bit 2         0:      CLKDIV4EN, ADC clock divider.  0=no effect, 1=CPUCLK/4 if CLKDIV2EN=1 (else no effect)
// bit 1         0:      ADCNONOVERLAP, 0=overlap sample and conversion, 1=no overlap 
// bit 0         1:      CLKDIV2EN, ADC clock divider.  0=CPUCLK, 1=CPUCLK/2

	DelayUs(1000);						// Wait 1 ms after power-up before using the ADC

		 AdcRegs.ADCCTL1.bit.ADCBGPWD = 1; // It's already been enabled, but it's necessary to enable it for the comparator to work

//--- Finish up
	AdcRegs.ADCCTL1.bit.ADCENABLE = 1;	// Enable the ADC
	asm(" EDIS");						// Disable EALLOW protected register access

} // end InitAdc()


//--- end of file -----------------------------------------------------
