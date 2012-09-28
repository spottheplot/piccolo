/**********************************************************************
* File: PieVect.c -- File for Lab 2, 3 and 4
* Devices: TMS320F2802x
* Author: Technical Training Organization (TTO), Texas Instruments
* History:
*   03/30/09 - original
**********************************************************************/

#include "Lab.h"						// Main include file


/**********************************************************************
* The PIE vector initialization table for the F2802x
**********************************************************************/
const struct PIE_VECT_TABLE PieVectTableInit = {

//--- Base vectors
    rsvd_ISR,                       // 0x000D00  reserved
    rsvd_ISR,                       // 0x000D02  reserved
    rsvd_ISR,                       // 0x000D04  reserved
    rsvd_ISR,                       // 0x000D06  reserved
    rsvd_ISR,                       // 0x000D08  reserved
    rsvd_ISR,                       // 0x000D0A  reserved
    rsvd_ISR,                       // 0x000D0C  reserved
    rsvd_ISR,                       // 0x000D0E  reserved
    rsvd_ISR,                       // 0x000D10  reserved
    rsvd_ISR,                       // 0x000D12  reserved
    rsvd_ISR,                       // 0x000D14  reserved
    rsvd_ISR,                       // 0x000D16  reserved
    rsvd_ISR,                       // 0x000D18  reserved
    TINT1_ISR,                      // 0x000D1A  TINT1 - CPU Timer1
    TINT2_ISR,                      // 0x000D1C  TINT2 - CPU Timer2
    DATALOG_ISR,                    // 0x000D1E  DATALOG - CPU data logging interrupt
    RTOSINT_ISR,                    // 0x000D20  RTOSINT - CPU RTOS interrupt
    EMUINT_ISR,                     // 0x000D22  EMUINT - CPU emulation interrupt
    NMI_ISR,                        // 0x000D24  NMI - XNMI interrupt
    ILLEGAL_ISR,                    // 0x000D26  ILLEGAL - illegal operation trap
    USER1_ISR,                      // 0x000D28  USER1 - software interrupt #1
    USER2_ISR,                      // 0x000D2A  USER2 - software interrupt #2
    USER3_ISR,                      // 0x000D2C  USER3 - software interrupt #3
    USER4_ISR,                      // 0x000D2E  USER4 - software interrupt #4
    USER5_ISR,                      // 0x000D30  USER5 - software interrupt #5
    USER6_ISR,                      // 0x000D32  USER6 - software interrupt #6
    USER7_ISR,                      // 0x000D34  USER7 - software interrupt #7
    USER8_ISR,                      // 0x000D36  USER8 - software interrupt #8
    USER9_ISR,                      // 0x000D38  USER9 - software interrupt #9
    USER10_ISR,                     // 0x000D3A  USER10 - software interrupt #10
    USER11_ISR,                     // 0x000D3C  USER11 - software interrupt #11
    USER12_ISR,                     // 0x000D3E  USER12 - software interrupt #12

//--- Core interrupt #1 re-map
    ADCINT1_ISR,                    // 0x000D40  ADC INT1
    ADCINT2_ISR,                    // 0x000D42  ADC INT2
    rsvd_ISR,                       // 0x000D44  reserved
    XINT1_ISR,                      // 0x000D46  XINT1
    XINT2_ISR,                      // 0x000D48  XINT2
    ADCINT9_ISR,                    // 0x000D4A  ADC INT9
    TINT0_ISR,                      // 0x000D4C  TINT0 (CPU TIMER 0)
    WAKEINT_ISR,                    // 0x000D4E  WAKEINT (LPM/WD)

//--- Core interrupt #2 re-map
    EPWM1_TZINT_ISR,                // 0x000D50  EPWM1TZINT
    EPWM2_TZINT_ISR,                // 0x000D52  EPWM2TZINT
    EPWM3_TZINT_ISR,                // 0x000D54  EPWM3TZINT
    EPWM4_TZINT_ISR,                // 0x000D56  EPWM4TZINT
    rsvd_ISR,                       // 0x000D58  reserved
    rsvd_ISR,                       // 0x000D5A  reserved
    rsvd_ISR,                       // 0x000D5C  reserved
    rsvd_ISR,                       // 0x000D5E  reserved

//--- Core interrupt #3 re-map
    EPWM1_INT_ISR,                  // 0x000D60  EPWM1INT
    EPWM2_INT_ISR,                  // 0x000D62  EPWM2INT
    EPWM3_INT_ISR,                  // 0x000D64  EPWM3INT
    EPWM4_INT_ISR,                  // 0x000D66  EPWM4INT
    rsvd_ISR,                       // 0x000D68  reserved
    rsvd_ISR,                       // 0x000D6A  reserved
    rsvd_ISR,                       // 0x000D6C  reserved
    rsvd_ISR,                       // 0x000D6E  reserved

//--- Core interrupt #4 re-map
    ECAP1_INT_ISR,                  // 0x000D70  ECAP1INT
    rsvd_ISR,                       // 0x000D72  reserved
    rsvd_ISR,                       // 0x000D74  reserved
    rsvd_ISR,                       // 0x000D76  reserved
    rsvd_ISR,                       // 0x000D78  reserved
    rsvd_ISR,                       // 0x000D7A  reserved
    rsvd_ISR,                       // 0x000D7C  reserved
    rsvd_ISR,                       // 0x000D7E  reserved

//--- Core interrupt #5 re-map
    rsvd_ISR,                       // 0x000D80  reserved
    rsvd_ISR,                       // 0x000D82  reserved
    rsvd_ISR,                       // 0x000D84  reserved
    rsvd_ISR,                       // 0x000D86  reserved
    rsvd_ISR,                       // 0x000D88  reserved
    rsvd_ISR,                       // 0x000D8A  reserved
    rsvd_ISR,                       // 0x000D8C  reserved
    rsvd_ISR,                       // 0x000D8E  reserved

//--- Core interrupt #6 re-map
    SPIRXINTA_ISR,                  // 0x000D90  SPIRXINTA
    SPITXINTA_ISR,                  // 0x000D92  SPIRXINTA
    rsvd_ISR,                       // 0x000D94  reserved
    rsvd_ISR,                       // 0x000D96  reserved
    rsvd_ISR,                       // 0x000D98  reserved
    rsvd_ISR,                       // 0x000D9A  reserved
    rsvd_ISR,                       // 0x000D9C  reserved
    rsvd_ISR,                       // 0x000D9E  reserved

//--- Core interrupt #7 re-map
    rsvd_ISR,                       // 0x000DA0  reserved
    rsvd_ISR,                       // 0x000DA2  reserved
    rsvd_ISR,                       // 0x000DA4  reserved
    rsvd_ISR,                       // 0x000DA6  reserved
    rsvd_ISR,                       // 0x000DA8  reserved
    rsvd_ISR,                       // 0x000DAA  reserved
    rsvd_ISR,                       // 0x000DAC  reserved
    rsvd_ISR,                       // 0x000DAE  reserved

//--- Core interrupt #8 re-map
    I2CINT1A_ISR,                   // 0x000DB0  I2CINT1A (I2C-A)
    I2CINT2A_ISR,                   // 0x000DB2  I2CINT2A (I2C-A)
    rsvd_ISR,                       // 0x000DB4  reserved
    rsvd_ISR,                       // 0x000DB6  reserved
    rsvd_ISR,                       // 0x000DB8  reserved
    rsvd_ISR,                       // 0x000DBA  reserved
    rsvd_ISR,                       // 0x000DBC  reserved
    rsvd_ISR,                       // 0x000DBE  reserved

//--- Core interrupt #9 re-map
    SCIRXINTA_ISR,                  // 0x000DC0  SCIRXINTA (SCI-A)
    SCITXINTA_ISR,                  // 0x000DC2  SCITXINTA (SCI-A)
    rsvd_ISR,                       // 0x000DC4  reserved
    rsvd_ISR,                       // 0x000DC6  reserved
    rsvd_ISR,                       // 0x000DC8  reserved
    rsvd_ISR,                       // 0x000DCA  reserved
    rsvd_ISR,                       // 0x000DCC  reserved
    rsvd_ISR,                       // 0x000DCE  reserved

//--- Core interrupt #10 re-map
    rsvd_ISR,                       // 0x000DD0  reserved, If this is ADCINT1_ISR, then INT1.1 should be rsvd_ISR
    rsvd_ISR,                       // 0x000DD2  reserved, If this is ADCINT2_ISR, then INT1.2 should be rsvd_ISR
    ADCINT3_ISR,                    // 0x000DD4  ADC INT3
    ADCINT4_ISR,                    // 0x000DD6  ADC INT4
    ADCINT5_ISR,                    // 0x000DD8  ADC INT5
    ADCINT6_ISR,                    // 0x000DDA  ADC INT6
    ADCINT7_ISR,                    // 0x000DDC  ADC INT7
    ADCINT8_ISR,                    // 0x000DDE  ADC INT8

//--- Core interrupt #11 re-map
    rsvd_ISR,                       // 0x000DE0  reserved
    rsvd_ISR,                       // 0x000DE2  reserved
    rsvd_ISR,                       // 0x000DE4  reserved
    rsvd_ISR,                       // 0x000DE6  reserved
    rsvd_ISR,                       // 0x000DE8  reserved
    rsvd_ISR,                       // 0x000DEA  reserved
    rsvd_ISR,                       // 0x000DEC  reserved
    rsvd_ISR,                       // 0x000DEE  reserved


//--- Core interrupt #12 re-map
    XINT3_ISR,                      // 0x000DF0  XINT3
    rsvd_ISR,                       // 0x000DF2  reserved
    rsvd_ISR,                       // 0x000DF4  reserved
    rsvd_ISR,                       // 0x000DF6  reserved
    rsvd_ISR,                       // 0x000DF8  reserved
    rsvd_ISR,                       // 0x000DFA  reserved
    rsvd_ISR,                       // 0x000DFC  reserved
    rsvd_ISR,                       // 0x000DFE  reserved

}; // end PieVectTableInit{}


//--- end of file -----------------------------------------------------
