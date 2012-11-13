/**********************************************************************************
* File: Lab_2_3.cmd -- File for Lab 2 and 3 (Boot to SARAM boot mode)
* Devices: TMS320F28069
* Author: Technical Training Organization (TTO), Texas Instruments
* History:
*   10/14/11 - original
**********************************************************************************/

MEMORY
{
PAGE 0:    /* Program Memory */
   BEGIN_M0           : origin = 0x000000, length = 0x000002     /* Part of M0SARAM - used for "Boot to M0" bootloader mode */
   L3DPSARAM          : origin = 0x009000, length = 0x001000     /* L3 DPSARAM, CSM secure, CLA Prog RAM */
   L4SARAM            : origin = 0x00A000, length = 0x002000     /* L4 SARAM, CSM secure */
   RESET          (R) : origin = 0x3FFFC0, length = 0x000002     /* part of Boot ROM */

 PAGE 1 :   /* Data Memory */
   M0SARAM            : origin = 0x000002, length = 0x0003FE     /* M0 SARAM */
   M1SARAM            : origin = 0x000400, length = 0x000400     /* M1 SARAM */
   L0DPSARAM          : origin = 0x008000, length = 0x000800     /* L0 DPSARAM, CSM secure, CLA Data RAM 2 */
   L1DPSARAM          : origin = 0x008800, length = 0x000400     /* L1 DPSARAM, CSM secure, CLA Data RAM 0 */
   L2DPSARAM          : origin = 0x008C00, length = 0x000400     /* L2 DPSARAM, CSM secure, CLA Data RAM 1 */
   L5DPSARAM          : origin = 0x00C000, length = 0x002000     /* L5 DPSARAM, DMA RAM 0 */
   L6DPSARAM          : origin = 0x00E000, length = 0x002000     /* L6 DPSARAM, DMA RAM 1 */
   L7DPSARAM          : origin = 0x010000, length = 0x002000     /* L7 DPSARAM, DMA RAM 2 */
   L8DPSARAM          : origin = 0x012000, length = 0x002000     /* L8 DPSARAM, DMA RAM 3 */
}

 
SECTIONS
{
/*** Compiler Required Sections ***/

  /* Program memory (PAGE 0) sections */
   .text              : > L4SARAM,               PAGE = 0
   .cinit             : > L4SARAM,               PAGE = 0
   .const             : > L4SARAM,               PAGE = 0
   .econst            : > L4SARAM,               PAGE = 0      
   .pinit             : > L4SARAM,               PAGE = 0
   .reset             : > RESET,                 PAGE = 0, TYPE = DSECT  /* We are not using the .reset section */
   .switch            : > L4SARAM,               PAGE = 0

  /* Data Memory (PAGE 1) sections */
   .bss               : > M0SARAM,               PAGE = 1
   .ebss              : > M0SARAM,               PAGE = 1
   .cio               : > M0SARAM,               PAGE = 1
   .stack             : > M1SARAM,               PAGE = 1
   .sysmem            : > M1SARAM,               PAGE = 1
   .esysmem           : > M1SARAM,               PAGE = 1

/*** User Defined Sections ***/
   codestart          : > BEGIN_M0,              PAGE = 0                /* Used by file CodeStartBranch.asm */
}

/******************* end of file ************************/
