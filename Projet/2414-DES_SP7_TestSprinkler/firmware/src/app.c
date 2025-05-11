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
#include "stdint.h"
#include "stdbool.h"
#include "Mc32DriverAdc.h"
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
    //timer1 used to buzz RN 
    //timer 2 used to SR LED (trying)
    static uint8_t value; 
    SR_LEDS LEDS;
    static uint8_t SampleReadyToRead;
    uint8_t i; 
    /* Check the application's current state. */
    switch ( appData.state )
    {
        /* Application's initial state. */
        case APP_STATE_INIT:
        {
            LEDS.LED8 = 0;
            LEDS.LED11 = 0;
            LEDS.LED4 = 0;
            LEDS.LED12 = 0;
            LEDS.LED6 = 0;
            LEDS.LED3 = 0;
            //SR2
            LEDS.LED10 = 0;
            LEDS.LED7 = 0;
            LEDS.LED1 = 0;
            LEDS.LED13 = 0;
            LEDS.LED0 = 0;
            LEDS.LED14 = 0;
            LEDS.LED5 = 0;
            DRV_ADC_Initialize();
            DRV_ADC_Open(); 
            DRV_ADC_Start();
            
            DRV_TMR2_Start();
            //BSP_InitADC10();
            appData.state = APP_STATE_SERVICE_TASKS;
            LIFELED_GREENOff();
        }

        case APP_STATE_SERVICE_TASKS:
        {
            
            //SR_LED_OE_1Toggle();
            //TESTPINToggle();
            value = SC3StateGet();
            TESTPINStateSet(value);
            //BUZZ_CMDToggle();
            if (value)
            {
                DRV_TMR0_Start();
            }
            else
            {
                DRV_TMR0_Stop();
                //appData.valAD=BSP_ReadAllADC();
            }
            SampleReadyToRead = DRV_ADC_SamplesAvailable();

            if (SampleReadyToRead) {
                SR_LED_OE_2Toggle();
                for (i = 0; i < 14; i++) {
                    appData.valAD[i] = DRV_ADC_SamplesRead(i);
                    

                }
                
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

 void APP_TIMER1_CALLBACK(void)
 {
     //between 1khz and 4khz 
     //timer should be set to 4khz 
     //with loop if necessary 
     
    BUZZ_CMDToggle();
 }
 void APP_SERIAL_LEDS_CMD(void)
{
    /*SR REG : 25times per sec 13CLK -- 325HZ  
         output disable -> send data -> output disable 
            
     * 
     * SR_LED_OE_1Toggle();
     * is remplaced by 
     * TESTPINStateSet();     
     */
    static uint8_t state =0;
    static uint8_t i =0;
    SR_LED_CLKOff();
    SR_LED_OE_2Off();
    TESTPINOff();
    for (i=0;i<14;i++)
    {
        SR_LED_DATAStateSet(1);
        SR_LED_CLKToggle();
        SR_LED_CLKToggle();
    }
    SR_LED_OE_2On();
    TESTPINOn();
    
    
 }


/*******************************************************************************
 End of File
 */
