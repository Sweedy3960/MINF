/*******************************************************************************
  MPLAB Harmony System Configuration Header

  File Name:
    system_config.h

  Summary:
    Build-time configuration header for the system defined by this MPLAB Harmony
    project.

  Description:
    An MPLAB Project may have multiple configurations.  This file defines the
    build-time options for a single configuration.

  Remarks:
    This configuration header must not define any prototypes or data
    definitions (or include any files that do).  It only provides macro
    definitions for build-time configuration options that are not instantiated
    until used by another MPLAB Harmony module or application.

    Created with MPLAB Harmony Version 2.06
*******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2015 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED AS IS WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
*******************************************************************************/
// DOM-IGNORE-END

#ifndef _SYSTEM_CONFIG_H
#define _SYSTEM_CONFIG_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
/*  This section Includes other configuration headers necessary to completely
    define this configuration.
*/


// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: System Service Configuration
// *****************************************************************************
// *****************************************************************************
// *****************************************************************************
/* Common System Service Configuration Options
*/
#define SYS_VERSION_STR           "2.06"
#define SYS_VERSION               20600

// *****************************************************************************
/* Clock System Service Configuration Options
*/
#define SYS_CLK_FREQ                        80000000ul
#define SYS_CLK_BUS_PERIPHERAL_1            80000000ul
#define SYS_CLK_UPLL_BEFORE_DIV2_FREQ       48000000ul
#define SYS_CLK_CONFIG_PRIMARY_XTAL         0ul
#define SYS_CLK_CONFIG_SECONDARY_XTAL       32768ul
   
/*** Ports System Service Configuration ***/
#define SYS_PORT_AD1PCFG        ~0xffff
#define SYS_PORT_CNPUE          0x0
#define SYS_PORT_CNEN           0x0
#define SYS_PORT_A_TRIS         0x7FFD
#define SYS_PORT_A_LAT          0x8000
#define SYS_PORT_A_ODC          0x0000

#define SYS_PORT_B_TRIS         0xFFFF
#define SYS_PORT_B_LAT          0x0000
#define SYS_PORT_B_ODC          0x0000

#define SYS_PORT_C_TRIS         0xDFF7
#define SYS_PORT_C_LAT          0x2008
#define SYS_PORT_C_ODC          0x0000

#define SYS_PORT_D_TRIS         0xF4FF
#define SYS_PORT_D_LAT          0x0200
#define SYS_PORT_D_ODC          0x0000

#define SYS_PORT_E_TRIS         0xFFFF
#define SYS_PORT_E_LAT          0x0000
#define SYS_PORT_E_ODC          0x0000

#define SYS_PORT_F_TRIS         0xFFFE
#define SYS_PORT_F_LAT          0x0000
#define SYS_PORT_F_ODC          0x0000

#define SYS_PORT_G_TRIS         0x5FFF
#define SYS_PORT_G_LAT          0x0000
#define SYS_PORT_G_ODC          0x0000


/*** Interrupt System Service Configuration ***/
#define SYS_INT                     true

// *****************************************************************************
// *****************************************************************************
// Section: Driver Configuration
// *****************************************************************************
// *****************************************************************************
/*** Timer Driver Configuration ***/
#define DRV_TMR_INTERRUPT_MODE             true

/*** Timer Driver 0 Configuration ***/
#define DRV_TMR_PERIPHERAL_ID_IDX0          TMR_ID_1
#define DRV_TMR_INTERRUPT_SOURCE_IDX0       INT_SOURCE_TIMER_1
#define DRV_TMR_INTERRUPT_VECTOR_IDX0       INT_VECTOR_T1
#define DRV_TMR_ISR_VECTOR_IDX0             _TIMER_1_VECTOR
#define DRV_TMR_INTERRUPT_PRIORITY_IDX0     INT_PRIORITY_LEVEL1
#define DRV_TMR_INTERRUPT_SUB_PRIORITY_IDX0 INT_SUBPRIORITY_LEVEL0
#define DRV_TMR_CLOCK_SOURCE_IDX0           DRV_TMR_CLKSOURCE_INTERNAL
#define DRV_TMR_PRESCALE_IDX0               TMR_PRESCALE_VALUE_1
#define DRV_TMR_OPERATION_MODE_IDX0         DRV_TMR_OPERATION_MODE_16_BIT
#define DRV_TMR_ASYNC_WRITE_ENABLE_IDX0     false
#define DRV_TMR_POWER_STATE_IDX0            

#define DRV_TMR_PERIPHERAL_ID_IDX1          TMR_ID_2
#define DRV_TMR_INTERRUPT_SOURCE_IDX1       INT_SOURCE_TIMER_2
#define DRV_TMR_INTERRUPT_VECTOR_IDX1       INT_VECTOR_T2
#define DRV_TMR_ISR_VECTOR_IDX1             _TIMER_2_VECTOR
#define DRV_TMR_INTERRUPT_PRIORITY_IDX1     INT_PRIORITY_LEVEL1
#define DRV_TMR_INTERRUPT_SUB_PRIORITY_IDX1 INT_SUBPRIORITY_LEVEL0
#define DRV_TMR_CLOCK_SOURCE_IDX1           DRV_TMR_CLKSOURCE_INTERNAL
#define DRV_TMR_PRESCALE_IDX1               TMR_PRESCALE_VALUE_16
#define DRV_TMR_OPERATION_MODE_IDX1         DRV_TMR_OPERATION_MODE_16_BIT

#define DRV_TMR_ASYNC_WRITE_ENABLE_IDX1     false
#define DRV_TMR_POWER_STATE_IDX1            
/*** Timer Driver 2 Configuration ***/
#define DRV_TMR_PERIPHERAL_ID_IDX2          TMR_ID_3
#define DRV_TMR_INTERRUPT_SOURCE_IDX2       INT_SOURCE_TIMER_3
#define DRV_TMR_INTERRUPT_VECTOR_IDX2       INT_VECTOR_T3
#define DRV_TMR_ISR_VECTOR_IDX2             _TIMER_3_VECTOR
#define DRV_TMR_INTERRUPT_PRIORITY_IDX2     INT_DISABLE_INTERRUPT
#define DRV_TMR_INTERRUPT_SUB_PRIORITY_IDX2 INT_SUBPRIORITY_LEVEL0
#define DRV_TMR_CLOCK_SOURCE_IDX2           DRV_TMR_CLKSOURCE_INTERNAL
#define DRV_TMR_PRESCALE_IDX2               TMR_PRESCALE_VALUE_256
#define DRV_TMR_OPERATION_MODE_IDX2         DRV_TMR_OPERATION_MODE_16_BIT
#define DRV_TMR_ASYNC_WRITE_ENABLE_IDX2     false
#define DRV_TMR_POWER_STATE_IDX2            

 
// *****************************************************************************
// *****************************************************************************
// Section: Middleware & Other Library Configuration
// *****************************************************************************
// *****************************************************************************



// *****************************************************************************
// *****************************************************************************
// Section: Application Configuration
// *****************************************************************************
// *****************************************************************************
/*** Application Defined Pins ***/

/*** Functions for LCD_RD pin ***/
#define LCD_RDToggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_15)
#define LCD_RDOn() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_15)
#define LCD_RDOff() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_15)
#define LCD_RDStateGet() PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_15)
#define LCD_RDStateSet(Value) PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_15, Value)

/*** Functions for TESTPIN pin ***/
#define TESTPINToggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_3)
#define TESTPINOn() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_3)
#define TESTPINOff() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_3)
#define TESTPINStateGet() PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_3)
#define TESTPINStateSet(Value) PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_3, Value)

/*** Functions for BUZZ_CMD pin ***/
#define BUZZ_CMDToggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_1)
#define BUZZ_CMDOn() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_1)
#define BUZZ_CMDOff() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_1)
#define BUZZ_CMDStateGet() PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_1)
#define BUZZ_CMDStateSet(Value) PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_1, Value)

/*** Functions for LIFELED_GREEN pin ***/
#define LIFELED_GREENToggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_15)
#define LIFELED_GREENOn() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_15)
#define LIFELED_GREENOff() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_15)
#define LIFELED_GREENStateGet() PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_15)
#define LIFELED_GREENStateSet(Value) PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_15, Value)

/*** Functions for SR_LED_CLK pin ***/
#define SR_LED_CLKToggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_8)
#define SR_LED_CLKOn() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_8)
#define SR_LED_CLKOff() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_8)
#define SR_LED_CLKStateGet() PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_8)
#define SR_LED_CLKStateSet(Value) PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_8, Value)

/*** Functions for SR_LED_OE_2 pin ***/
#define SR_LED_OE_2Toggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_11)
#define SR_LED_OE_2On() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_11)
#define SR_LED_OE_2Off() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_11)
#define SR_LED_OE_2StateGet() PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_11)
#define SR_LED_OE_2StateSet(Value) PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_11, Value)

/*** Functions for SR_LED_OE_1 pin ***/
#define SR_LED_OE_1Toggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_13)
#define SR_LED_OE_1On() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_13)
#define SR_LED_OE_1Off() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_13)
#define SR_LED_OE_1StateGet() PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_13)
#define SR_LED_OE_1StateSet(Value) PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_13, Value)

/*** Functions for SR_LED_DATA pin ***/
#define SR_LED_DATAToggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_F, PORTS_BIT_POS_0)
#define SR_LED_DATAOn() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_F, PORTS_BIT_POS_0)
#define SR_LED_DATAOff() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_F, PORTS_BIT_POS_0)
#define SR_LED_DATAStateGet() PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_F, PORTS_BIT_POS_0)
#define SR_LED_DATAStateSet(Value) PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_F, PORTS_BIT_POS_0, Value)

/*** Functions for LCD_A0 pin ***/
#define LCD_A0Toggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_13)
#define LCD_A0On() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_13)
#define LCD_A0Off() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_13)
#define LCD_A0StateGet() PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_13)
#define LCD_A0StateSet(Value) PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_13, Value)

/*** Functions for FC3 pin ***/
#define FC3StateGet() PLIB_PORTS_PinGet(PORTS_ID_0, PORT_CHANNEL_F, PORTS_BIT_POS_1)

/*** Functions for SC1 pin ***/
#define SC1StateGet() PLIB_PORTS_PinGet(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_1)

/*** Functions for FC4 pin ***/
#define FC4StateGet() PLIB_PORTS_PinGet(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_0)

/*** Functions for FC5 pin ***/
#define FC5StateGet() PLIB_PORTS_PinGet(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_6)

/*** Functions for FC1 pin ***/
#define FC1StateGet() PLIB_PORTS_PinGet(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_7)

/*** Functions for FC2 pin ***/
#define FC2StateGet() PLIB_PORTS_PinGet(PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_0)

/*** Functions for SC2 pin ***/
#define SC2StateGet() PLIB_PORTS_PinGet(PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_1)

/*** Functions for SC3 pin ***/
#define SC3StateGet() PLIB_PORTS_PinGet(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_14)

/*** Functions for SD_SPI_SC pin ***/
#define SD_SPI_SC_PORT PORT_CHANNEL_D
#define SD_SPI_SC_PIN PORTS_BIT_POS_9
#define SD_SPI_SC_PIN_MASK (0x1 << 9)


/*** Application Instance 0 Configuration ***/

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // _SYSTEM_CONFIG_H
/*******************************************************************************
 End of File
*/
