/**********************************************************************
* File: DefaultIsr_3_4.c -- File for Lab 3 and 4
* Devices: TMS320F2802x
* Author: Technical Training Organization (TTO), Texas Instruments
* History:
*   03/30/09 - original
**********************************************************************/

#include "Lab.h"						// Main include file


//---------------------------------------------------------------------
interrupt void TINT1_ISR(void)					// 0x000D1A  TINT1 - CPU Timer1
{
// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void TINT2_ISR(void)					// 0x000D1C  TINT2 - CPU Timer2
{
// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void DATALOG_ISR(void)				// 0x000D1E  DATALOG - CPU data logging interrupt
{
// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void RTOSINT_ISR(void)				// 0x000D20  RTOSINT - CPU RTOS interrupt
{
// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void EMUINT_ISR(void) 				// 0x000D22  EMUINT - CPU emulation interrupt
{
// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void NMI_ISR(void)					// 0x000D24  NMI - XNMI interrupt
{
// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void ILLEGAL_ISR(void)				// 0x000D26  ILLEGAL - illegal operation trap
{
// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void USER1_ISR(void)					// 0x000D28  USER1 - software interrupt #1
{
// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void USER2_ISR(void)					// 0x000D2A  USER2 - software interrupt #2
{
// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void USER3_ISR(void)					// 0x000D2C  USER3 - software interrupt #3
{
// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void USER4_ISR(void)					// 0x000D2E  USER4 - software interrupt #4
{
// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void USER5_ISR(void)					// 0x000D30  USER5 - software interrupt #5
{
// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void USER6_ISR(void)					// 0x000D32  USER6 - software interrupt #6
{
// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void USER7_ISR(void)					// 0x000D34  USER7 - software interrupt #7
{
// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void USER8_ISR(void)					// 0x000D36  USER8 - software interrupt #8
{
// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void USER9_ISR(void)					// 0x000D38  USER9 - software interrupt #9
{
// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void USER10_ISR(void)					// 0x000D3A  USER10 - software interrupt #10
{
// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void USER11_ISR(void)					// 0x000D3C  USER11 - software interrupt #11
{
// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void USER12_ISR(void)					// 0x000D3E  USER12 - software interrupt #12
{
// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void ADCINT1_ISR(void)				// PIE1.1 @ 0x000D40  ADCINT1 (ADC INT1)
{
static Uint16 *AdcBufPtr = AdcBuf;				// Pointer to buffer
static volatile Uint16 GPIO34_count = 0;		// Counter for pin toggle

	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;		// Must acknowledge the PIE group

//--- Manage the ADC registers     
	AdcRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;		// Clear ADCINT1 flag

//--- Read the ADC result
	*AdcBufPtr++ = 	AdcResult.ADCRESULT0;     	// Read the result

//--- Brute-force the circular buffer
	if( AdcBufPtr == (AdcBuf + ADC_BUF_LEN) )
	{	
		AdcBufPtr = AdcBuf;						// Rewind the pointer to beginning
	}

//--- Example: Toggle GPIO18 so we can read it with the ADC ***/
	if(DEBUG_TOGGLE == 1)
	{
		GpioDataRegs.GPATOGGLE.bit.GPIO18 = 1;		// Toggle the pin
	}

//--- Example: Toggle GPIO34 at a 0.5 sec rate (connected to the LED on the ControlSTICK).
//             (1/50000 sec/sample)*(1 samples/int)*(x interrupts/toggle) = (0.5 sec/toggle)
//             ==> x = 25000
	if(GPIO34_count++ > 25000)					// Toggle slowly to see the LED blink
	{
		GpioDataRegs.GPBTOGGLE.bit.GPIO34 = 1;	// Toggle the pin
		GPIO34_count = 0;						// Reset the counter
	}
}

//---------------------------------------------------------------------
interrupt void ADCINT2_ISR(void)				// PIE1.2 @ 0x000D42  ADCINT2 (ADC INT2)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;		// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
												// PIE1.3 @ 0x000D44  reserved

//---------------------------------------------------------------------
interrupt void XINT1_ISR(void)					// PIE1.4 @ 0x000D46  XINT1
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;		// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void XINT2_ISR(void)					// PIE1.5 @ 0x000D48  XINT2
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;		// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void ADCINT9_ISR(void)				// PIE1.6 @ 0x000D4A  ADCINT9 (ADC INT9)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;		// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void TINT0_ISR(void)					// PIE1.7 @ 0x000D4C  TINT0 (CPU TIMER 0)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;		// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void WAKEINT_ISR(void)				// PIE1.8 @ 0x000D4E  WAKEINT (LPM/WD)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;		// Must acknowledge the PIE group
  
// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void EPWM1_TZINT_ISR(void)			// PIE2.1 @ 0x000D50  EPWM1_TZINT (EPWM1)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;		// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void EPWM2_TZINT_ISR(void)			// PIE2.2 @ 0x000D52  EPWM2_TZINT (EPWM2)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;		// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void EPWM3_TZINT_ISR(void)			// PIE2.3 @ 0x000D54  EPWM3_TZINT (EPWM3)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;		// Must acknowledge the PIE group
  
// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void EPWM4_TZINT_ISR(void)			// PIE2.4 @ 0x000D56  EPWM4_TZINT (EPWM4)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;		// Must acknowledge the PIE group
  
// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
												// PIE2.5 @ 0x000D58  reserved
												// PIE2.6 @ 0x000D5A  reserved
												// PIE2.7 @ 0x000D5C  reserved
												// PIE2.8 @ 0x000D5E  reserved
     
//---------------------------------------------------------------------
interrupt void EPWM1_INT_ISR(void)				// PIE3.1 @ 0x000D60  EPWM1_INT (EPWM1)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;		// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void EPWM2_INT_ISR(void)				// PIE3.2 @ 0x000D62  EPWM2_INT (EPWM2)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;		// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void EPWM3_INT_ISR(void)				// PIE3.3 @ 0x000D64  EPWM3_INT (EPWM3)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;		// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void EPWM4_INT_ISR(void)				// PIE3.4 @ 0x000D66  EPWM4_INT (EPWM4)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;		// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
												// PIE3.5 @ 0x000D68  reserved
												// PIE3.6 @ 0x000D6A  reserved
												// PIE3.7 @ 0x000D6C  reserved
												// PIE3.8 @ 0x000D6E  reserved

//---------------------------------------------------------------------
interrupt void ECAP1_INT_ISR(void)				// PIE4.1 @ 0x000D70  ECAP1_INT (ECAP1)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;		// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
												// PIE4.2 @ 0x000D72  reserved
												// PIE4.3 @ 0x000D74  reserved
												// PIE4.4 @ 0x000D76  reserved
												// PIE4.5 @ 0x000D78  reserved
												// PIE4.6 @ 0x000D7A  reserved
												// PIE4.7 @ 0x000D7C  reserved
												// PIE4.8 @ 0x000D7E  reserved

//---------------------------------------------------------------------
												// PIE5.1 @ 0x000D80  reserved
												// PIE5.2 @ 0x000D82  reserved
												// PIE5.3 @ 0x000D84  reserved
												// PIE5.4 @ 0x000D86  reserved
												// PIE5.5 @ 0x000D88  reserved
												// PIE5.6 @ 0x000D8A  reserved
												// PIE5.7 @ 0x000D8C  reserved
												// PIE5.8 @ 0x000D8E  reserved

//---------------------------------------------------------------------
interrupt void SPIRXINTA_ISR(void)				// PIE6.1 @ 0x000D90  SPIRXINTA (SPI-A)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;		// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void SPITXINTA_ISR(void)				// PIE6.2 @ 0x000D92  SPITXINTA (SPI-A)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;		// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
												// PIE6.3 @ 0x000D94  reserved
												// PIE6.4 @ 0x000D96  reserved
												// PIE6.5 @ 0x000D98  reserved
												// PIE6.6 @ 0x000D9A  reserved
												// PIE6.7 @ 0x000D9C  reserved
												// PIE6.8 @ 0x000D9E  reserved

//---------------------------------------------------------------------
												// PIE7.1 @ 0x000DA0  reserved
												// PIE7.2 @ 0x000DA2  reserved
												// PIE7.3 @ 0x000DA4  reserved
												// PIE7.4 @ 0x000DA6  reserved
												// PIE7.5 @ 0x000DA8  reserved
												// PIE7.6 @ 0x000DAA  reserved
												// PIE7.7 @ 0x000DAC  reserved
												// PIE7.8 @ 0x000DAE  reserved

//---------------------------------------------------------------------
interrupt void I2CINT1A_ISR(void)				// PIE8.1 @ 0x000DB0  I2CINT1A (I2C-A)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;		// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void I2CINT2A_ISR(void)				// PIE8.2 @ 0x000DB2  I2CINT2A (I2C-A)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;		// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
												// PIE8.3 @ 0x000DB4  reserved
												// PIE8.4 @ 0x000DB6  reserved
												// PIE8.5 @ 0x000DB8  reserved
												// PIE8.6 @ 0x000DBA  reserved
												// PIE8.7 @ 0x000DBC  reserved
												// PIE8.8 @ 0x000DBE  reserved

//---------------------------------------------------------------------
interrupt void SCIRXINTA_ISR(void)				// PIE9.1 @ 0x000DC0  SCIRXINTA (SCI-A)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;		// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void SCITXINTA_ISR(void)				// PIE9.2 @ 0x000DC2  SCITXINTA (SCI-A)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;		// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
												// PIE9.3 @ 0x000DC4  reserved
												// PIE9.4 @ 0x000DC6  reserved
												// PIE9.5 @ 0x000DC8  reserved
												// PIE9.6 @ 0x000DCA  reserved
												// PIE9.7 @ 0x000DCC  reserved
												// PIE9.8 @ 0x000DCE  reserved

//---------------------------------------------------------------------
												// PIE10.1 @ 0x000DD0  (ADCINT1 - see PIE1.1)
												// PIE10.2 @ 0x000DD2  (ADCINT2 - see PIE1.2)

//---------------------------------------------------------------------
interrupt void ADCINT3_ISR(void)				// PIE10.3 @ 0x000DD4  ADCINT3 (ADC INT3)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;	// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void ADCINT4_ISR(void)				// PIE10.4 @ 0x000DD6  ADCINT4 (ADC INT4)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;	// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void ADCINT5_ISR(void)				// PIE10.5 @ 0x000DD8  ADCINT5 (ADC INT5)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;	// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void ADCINT6_ISR(void)				// PIE10.6 @ 0x000DDA  ADCINT6 (ADC INT6)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;	// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void ADCINT7_ISR(void)				// PIE10.7 @ 0x000DDC  ADCINT7 (ADC INT7)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;	// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void ADCINT8_ISR(void)				// PIE10.8 @ 0x000DDE  ADCINT8 (ADC INT8)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;	// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
												// PIE11.1 @ 0x000DE0 reserved
												// PIE11.2 @ 0x000DE2 reserved
												// PIE11.3 @ 0x000DE4 reserved
												// PIE11.4 @ 0x000DE6 reserved
												// PIE11.5 @ 0x000DE8 reserved
												// PIE11.6 @ 0x000DEA reserved
												// PIE11.7 @ 0x000DEC reserved
												// PIE11.8 @ 0x000DEE reserved

//---------------------------------------------------------------------
interrupt void XINT3_ISR(void)					// PIE12.1 @ 0x000DF0  XINT3
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;	// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}     

//---------------------------------------------------------------------
												// PIE12.2 @ 0x000DF2 reserved
												// PIE12.3 @ 0x000DF4 reserved
												// PIE12.4 @ 0x000DF6 reserved
												// PIE12.5 @ 0x000DF8 reserved
												// PIE12.6 @ 0x000DFA reserved
												// PIE12.7 @ 0x000DFC reserved
												// PIE12.8 @ 0x000DFE reserved

//---------------------------------------------------------------------
interrupt void rsvd_ISR(void)					// Reserved PIE vectors
{
// This ISR is for reserved PIE vectors.  It should never be reached by
// properly executing code.  If you get here, it means something is wrong.

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}


//--- end of file -----------------------------------------------------
