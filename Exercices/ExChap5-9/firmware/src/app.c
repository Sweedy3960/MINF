/*******************************************************************************
  MPLAB Harmony Application Source File
  
  Company:
    Microchip Technology Inc.
  
  File Name:
    app.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It 
    implements the logic of the application's state machine and it may call 
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
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


// *****************************************************************************
// *****************************************************************************
// Section: Included Files 
// *****************************************************************************
// *****************************************************************************

#include "app.h"
#include "Mc32DriverLcd.h"
#include "Mc32_I2cUtilCCS.h"
#include "Mc32gestI2cLM92.h"
#include "Mc32gestSpiDac.h"
#include "peripheral/oc/plib_oc.h"
// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_Initialize function.
    
    Application strings and buffers are be defined outside this structure.
*/

APP_DATA appData;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************


/* TODO:  Add any necessary local functions.
*/


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    appData.state = APP_STATE_INIT;

    
    /* TODO: Initialize your application's state machine and other
     * paramete
     */
}


/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Tasks ( void )
{
    static uint32_t Temp;
    static float RealTemp;
    uint32_t  a;
    /* Check the application's current state. */
    switch ( appData.state )
    {
        /* Application's initial state. */
        case APP_STATE_INIT:
        {
            lcd_init();
            lcd_bl_on();
            I2C_InitLM92();
            SPI_InitLTC2604();
            DRV_TMR0_Start();
            DRV_TMR1_Start();
            DRV_OC0_Start();
            
            lcd_gotoxy(1,1);
            printf_lcd("Ex Rev chap 5 à 9");
            lcd_gotoxy(1,2);
            printf_lcd("clauzel");
            appData.state = APP_STATE_WAIT;
        }

        case APP_STATE_SERVICE_TASKS:
        {
            BSP_LEDOn(BSP_LED_1);
            
            Temp = I2C_ReadRawTempLM92();
            LM92_ConvRawToDeg(Temp,&RealTemp);
            lcd_gotoxy(1,3);        
            printf_lcd("Temp = %.1f", RealTemp);
            Temp = (RealTemp * COEF ) + origdec ; 
            PLIB_OC_PulseWidth16BitSet(OC_ID_2,(Temp/100)*40000);
s            a = ((65536/20)*RealTemp);
            
            //SPI_WriteToDac(0,);// monitemp en V 
         
            //SPI_WriteToDac(1,Temp/10+0.5);//moni Rc en V  
            BSP_LEDOff(BSP_LED_1);
            break;
        }

        /* TODO: implement your application state machine.*/
        case APP_STATE_WAIT:
        {
            break;
        }
        /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}
void APP_GEN_UpdateState ( APP_STATES NewState )
{
    appData.state = NewState;
}

void APP_Timer1_CallBack(void)
{
    static delayCnt = 0;
    
    BSP_LEDToggle(BSP_LED_0);
    if (delayCnt % 5 == 0) 
    {
        delayCnt = 0;
        APP_GEN_UpdateState(APP_STATE_SERVICE_TASKS);
    }
    delayCnt++;

}

/*******************************************************************************
 End of File
 */
