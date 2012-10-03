/**********************************************************************
* File: Lab_2_3.cmd -- File for Lab 2 and 3 (Boot to SARAM boot mode)
* Devices: TMS320F28027
* Author: Technical Training Organization (TTO), Texas Instruments
* History:
*   03/30/09 - original
**********************************************************************/

MEMORY
{
PAGE 0:    /* Program Memory */
   BEGIN_M0        : origin = 0x000000, length = 0x000002     /* Part of M0SARAM.  Used for "Boot to M0" bootloader mode. */
   L0SARAM         : origin = 0x008000, length = 0x001000     /* L0 SARAM, CSM secure */
   RESET           : origin = 0x3FFFC0, length = 0x000002     /* part of Boot ROM */

 PAGE 1 :   /* Data Memory */
   M0SARAM         : origin = 0x000002, length = 0x0003FE     /* 1Kw M0 SARAM */
   M1SARAM         : origin = 0x000400, length = 0x000400     /* 1Kw M1 SARAM */
}

 
SECTIONS
{
/*** Compiler Required Sections ***/

  /* Program memory (PAGE 0) sections */
   .text             : > L0SARAM,               PAGE = 0
   .cinit            : > L0SARAM,               PAGE = 0
   .const            : > L0SARAM,               PAGE = 0
   .econst           : > L0SARAM,               PAGE = 0      
   .pinit            : > L0SARAM,               PAGE = 0
   .reset            : > RESET,                 PAGE = 0, TYPE = DSECT  /* We are not using the .reset section */
   .switch           : > L0SARAM,               PAGE = 0

  /* Data Memory (PAGE 1) sections */
   .bss              : > M0SARAM,               PAGE = 1
   .ebss             : > M0SARAM,               PAGE = 1
   .cio              : > M0SARAM,               PAGE = 1
   .stack            : > M1SARAM,               PAGE = 1
   .sysmem           : > M1SARAM,               PAGE = 1
   .esysmem          : > M1SARAM,               PAGE = 1

/*** User Defined Sections ***/
   codestart         : > BEGIN_M0,              PAGE = 0                /* Used by file CodeStartBranch.asm */
}

/******************* end of file ************************/
