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
#include "app_eventbus.h"
#include "app_taskctrl.h"
#include "appReg.h"


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

APP_REG_DATA appRegData;

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

void APP_REG_Initialize(void) {
    /* Place the App state machine in its initial state. */
    appRegData.Regstate = APP_REG_STATE_INIT;


    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
}

extern app_task_ctrl_t ledTaskCtrl;

/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Reg_Tasks(void) {

    /* Check the application's current state. */
    switch (appRegData.Regstate) {
            /* Application's initial state. */
        case APP_REG_STATE_INIT:
        {

            SR_Init(&appRegData.sysLeds);

            appRegData.Regstate = APP_REG_STATE_SERVICE_TASKS;

            break;
        }

        case APP_REG_STATE_SERVICE_TASKS:
        {
            if (!ledTaskCtrl.isActive)
                break;

            if (appRegData.lastSysLeds.cmd_leds != appRegData.sysLeds.cmd_leds) {
                //set the flag 
                ledTaskCtrl.isDirty = true;

            }


            appRegData.Regstate = APP_REG_STATE_IDLE;
            break;
        }

            /* TODO: implement your application state machine.*/
        case APP_REG_STATE_IDLE:
        {
            if (ledTaskCtrl.isDirty) {



                touchTaskCtrl.isActive = false; // disable touch task while updating display
                displayTaskCtrl.isActive = false;
                SR_Update(&appRegData.sysLeds);
                ledTaskCtrl.isDirty = false; // clear after updating
                touchTaskCtrl.isActive = true; // disable touch task while updating display
                displayTaskCtrl.isActive = true;
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
}

void APP_WaitStart(uint16_t waitingTime_ms) {

    appRegData.AppDelay = waitingTime_ms - 1;
    DRV_TMR3_Start();
    appRegData.APP_DelayTimeIsRunning = 1;
    // Garde-fou : timeout logiciel (2x le temps demandé)


    while (appRegData.APP_DelayTimeIsRunning) {

    }
    DRV_TMR3_Stop();
}

void APP_TIMER4_CALLBACK(void) {
    if (appRegData.AppDelay > 0) {
        appRegData.AppDelay--;
    } else {
        appRegData.APP_DelayTimeIsRunning = 0;
    }

}

void APP_SER_SET_CMD_LED(uint16_t cmd) {

    appRegData.sysLeds.cmd_leds = cmd;
}

void App_LED_HandleTouch(uint16_t *touchStates) {
    // static uint16_t lastTouchStates = 0;
    // mettre � jour l?affichage selon les touches d�tect�es
    // Par exemple?: changer l'�tat du menu
    // Pour l?instant, on se contente de marquer la t�che display comme "dirty"

    ledTaskCtrl.isDirty = true;
    switch (*touchStates) {
            //SIMPLE TOUCH
        case KEY_UP_L_MASK:
            APP_SER_SET_CMD_LED(~(*touchStates));
        case KEY_MID_L_MASK:
            APP_SER_SET_CMD_LED(~(*touchStates));

        case KEY_DOWN_L_MASK:

            APP_SER_SET_CMD_LED(~(*touchStates));
        case KEY_UP_C_MASK:

            APP_SER_SET_CMD_LED(~(*touchStates));
        case KEY_DOWN_C_MASK:

            APP_SER_SET_CMD_LED(~(*touchStates));
        case KEY_UP_R_MASK:

            APP_SER_SET_CMD_LED(~(*touchStates));
        case KEY_MID_R_MASK:
            APP_SER_SET_CMD_LED(~(*touchStates));

        case KEY_DOWN_R_MASK:
            APP_SER_SET_CMD_LED(~(*touchStates));
            break;
        default:
            break;
    }

    //lastTouchStates = *touchStates;
}
/*******************************************************************************
 End of File
 */
