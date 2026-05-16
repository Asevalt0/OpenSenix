// SPDX-License-Identifier: GPL-2.0-only
/* added this to have some easier readable code
this isnt needed but i still prefer keeping it.*/


#ifndef X86CONSTANTS_H
#define X86CONSTANTS_H

/* ========================================================================
   CORE MEMORY MAP CONFIGURATIONS
   ======================================================================== */
#define KERNEL_VIRT_BASE    0xC0000000U       /* standard 3GB virtual offset boundary */
#define VIDEO_VGA_BUFFER    0x000B8000U       /* Legacy VGA text mode buffer physical address */

/* ========================================================================
   SYSTEM REGISTER BIT MASKS (CR0/CR4 Flags)
   ======================================================================== */
#define CR0_PE_BIT          0x00000001U       /* protected Mode Enable bit flag */
#define CR0_WP_BIT          0x00010000U       /* write Protect bit flag*/
#define CR4_PAE_BIT         0x00000020U       /* physical Address Extension bit */

/* ========================================================================
   LEGACY HARDWARE CONTROLLER PORTS
   ======================================================================== */
#define PORT_PIC_MASTER_CMD  0x0020U          /* master Programmable Interrupt Controller command port */
#define PORT_PIC_MASTER_DATA 0x0021U          /* master Programmable Interrupt Controller data port */
#define PORT_COM1_DEBUG      0x03F8U          /* serial Port 1 */

#endif
