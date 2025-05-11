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
#include "bsp.h"
#include "Mc32DriverLcd.h"
#include "Mc32DriverAdcAlt.h"

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
     * parameters.
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

    /* Check the application's current state. */
    switch ( appData.state )
    {
        /* Application's initial state. */
        case APP_STATE_INIT:
        {
            DRV_TMR0_Start();
            lcd_init();
            lcd_bl_on();
            
            appData.Elapsedms = 0;
            PLIB_PORTS_PinDirectionOutputSet( PORTS_ID_0,LIGNE1_PORT, LIGNE1_BIT );
            PLIB_PORTS_PinDirectionOutputSet( PORTS_ID_0,LIGNE2_PORT, LIGNE2_BIT );
            PLIB_PORTS_PinDirectionOutputSet( PORTS_ID_0,LIGNE3_PORT, LIGNE3_BIT );
            PLIB_PORTS_PinDirectionOutputSet( PORTS_ID_0,LIGNE4_PORT, LIGNE4_BIT );
            
            PLIB_PORTS_Clear(PORTS_ID_0,LIGNE1_PORT, LIGNE1_BIT);
            PLIB_PORTS_Clear( PORTS_ID_0,LIGNE2_PORT, LIGNE2_BIT);
            PLIB_PORTS_Clear( PORTS_ID_0,LIGNE3_PORT, LIGNE3_BIT);
            PLIB_PORTS_Clear( PORTS_ID_0,LIGNE4_PORT, LIGNE4_BIT );
            APP_UpdateState( APP_STATE_WAIT);
            
            break;
        }

        case APP_STATE_SERVICE_TASKS:
        {
            lcd_bl_on();
            appData.Elapsedms = 0; 
            printf_lcd("C1: %3d",  appData.EtatCol1);
            printf_lcd("C2: %3d",  appData.EtatCol2);
            printf_lcd("C3: %3d",  appData.EtatCol3);
            printf_lcd("C4: %3d",  appData.EtatCol3);
            printf_lcd("C5: %3d",  appData.EtatPec12Pb);
            APP_UpdateState(APP_STATE_WAIT);
            break;
        }
        case APP_STATE_WAIT:
        {
            if ( appData.Elapsedms>1000)
            {
                lcd_bl_off();
            }
            break;  
        }

        /* TODO: implement your application state machine.*/
        

        /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}
void APP_UpdateState(APP_STATES newState)
{
    appData.state = newState;
}

 

/*******************************************************************************
 End of File
 */
