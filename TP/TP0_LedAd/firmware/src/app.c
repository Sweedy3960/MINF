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
#include <stdlib.h>
#include <string.h>
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
    
    static char firstTimeSincePowerUp = 0;
    /* Check the application's current state. */
    switch ( appData.state )
    {
        /* Application's initial state. */
        case APP_STATE_INIT:
        {
           
            lcd_init();
            lcd_bl_on();
            printf_lcd("TP0 LED+AD 2024-11");
            lcd_gotoxy(1,2);
            printf_lcd("Clauzel");
            BSP_InitADC10();
            AllLed(LIGHTUP);
            DRV_TMR0_Start();
            APP_UpdateState(APP_STATE_WAIT);       
            break;
        }

        case APP_STATE_SERVICE_TASKS:
        {
            
            appData.AdcRes = BSP_ReadAllADC();
            lcd_gotoxy(1,3);
            
            printf_lcd("Ch0 %4d Ch1 %4d", appData.AdcRes.Chan0, appData.AdcRes.Chan1);
            if(!firstTimeSincePowerUp)
            {
                firstTimeSincePowerUp = 1;
                AllLed(LIGHTOFF);
            }
            
            chenillard();
            APP_UpdateState(APP_STATE_WAIT);
            break;
        }
        case APP_STATE_WAIT:
        {
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

void APP_UpdateState ( APP_STATES newState )
{ 
   appData.state = newState;
}
void APP_Timer1CallBack(void)
{
    static uint32_t i=0;
    if(i>=30)
    {
        i=29;
        APP_UpdateState(APP_STATE_SERVICE_TASKS);
    }
    i++;
    
}

void AllLed(uint8_t state)
{
   
    if (state !=0)
    {
        OFF(LED0_W);
        OFF(LED1_W);
        OFF(LED2_W);
        OFF(LED3_W);
        OFF(LED4_W);
        OFF(LED5_W);
        OFF(LED6_W);
        OFF(LED7_W);
         
    }
    else
    {
        ON(LED0_W);
        ON(LED1_W);
        ON(LED2_W);
        ON(LED3_W);
        ON(LED4_W);
        ON(LED5_W);
        ON(LED6_W);
        ON(LED7_W);
    
    }
}
void chenillard(void)
{
    static char state=0;
    AllLed(LIGHTOFF);
    switch  (state)
    {
        case 0:
            ON(LED0_W);
            state++;
            break;
        case 1:
            ON(LED1_W);
            state++;
            break;
        case 2: 
            ON(LED2_W);
            state++;
            break;  
        case 3:
            ON(LED3_W);
            state++;
            break;
        case 4:
            ON(LED4_W);
            state++;
            break;
        case 5:
            ON(LED5_W);
            state++;
            break;
        case 6: 
            ON(LED6_W);
            state++;
            break;  
        case 7:
            ON(LED7_W);
            state=0;
            break; 
        
    }
    
}

/*******************************************************************************
 End of File
 */
