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
#include "peripheral/oc/plib_oc.h"
#include "peripheral/usart/plib_usart.h"
#include "stdint.h"
#include "string.h"

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

void APP_Initialize(void) {
    /* Place the App state machine in its initial state. */
    appData.state = APP_STATE_INIT;

}

/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */
void APP_Tasks(void) {
    // *** Variables locales ***

    // ...

    /* Check the application's current state. */
    switch (appData.state) {
            /* Application's initial state. */
        case APP_STATE_INIT:
        {
            // *** initialisation ***
            DRV_TMR1_Start();
            DRV_TMR0_Start();
            DRV_OC0_Start();
            DRV_USART0_Initialize();
            lcd_init();
            lcd_bl_on();
            lcd_gotoxy(C1, L1);
            printf_lcd("TE2 MINF GenPwmUart");
            lcd_gotoxy(C1, L2);
            printf_lcd("clauzel");
            // ...
            APP_UpdateState(APP_STATE_WAIT);
            break;
        }

        case APP_STATE_WAIT:
        {
            //rien à faire...
            break;
        }

        case APP_STATE_SERVICE_TASKS:
        {
            // Tâches cycliques
            //récupere 3 char 
            uint8_t ctring[3];
            char value[3];
            uint8_t iter = 0;
            uint8_t jiter = 0;
            if (PLIB_USART_ReceiverDataIsAvailable(USART_ID_1)) {
                for (iter = 0; iter <= 2; iter++) {
                    ctring[iter] = (PLIB_USART_ReceiverByteReceive(USART_ID_1));
                }
                for (jiter = 0; jiter<= 2; jiter++) {
                    value[jiter] = atoi((const char*)ctring[jiter]);
                    
                }
                if ((value[0] <0x30) ||value[0] >0x39 )
                    {
                        sendNock();
                    }
                    else
                    {
                        sendok(ctring);
                        lcd_gotoxy(C1, L4);
                        printf_lcd("r.c: %s", ctring);
                        PLIB_OC_PulseWidth16BitSet(OC_ID_2, (int)value * VALMAXCNT /100);
                        // ...
                    }
                
                
                




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
    void APP_UpdateState(APP_STATES newState) {
        appData.state = newState;
    }
    
    void callback_TMR1(void) 
    {
        APP_UpdateState(APP_STATE_SERVICE_TASKS);

    }
    void sendok(uint8_t *_ctring)
    {
         
        char stringOK[8]="OK";
        
        uint8_t iter=0;
        strcat(stringOK,(const char*)_ctring);
        for (iter = 0; iter < 8;iter++)
        {    
            PLIB_USART_TransmitterByteSend(USART_ID_1,stringOK[iter]);
        }
    }
    
    
    void sendNock(void)
    {
        char stringNOK[6] = "NOK/n";
        uint8_t iter=0;
        for (iter = 0; iter < 6;iter++)
        {    
            PLIB_USART_TransmitterByteSend(USART_ID_1,stringNOK[iter]);
        }
    }
    /*******************************************************************************
     End of File
     */
