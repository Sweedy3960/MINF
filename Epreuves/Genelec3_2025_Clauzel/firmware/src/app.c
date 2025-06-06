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
#include "peripheral/usart/plib_usart.h"
#include "Mc32DriverLcd.h"
#include "peripheral/ic/plib_ic.h"
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
    //var pour affichache décomposer
    //it would be smarter to make not a ms but like 10us for tmr2
    uint8_t tempHautUP; //au dessus de .
    uint8_t tempHautDown; // au dessous de .
    uint8_t i; //boucle for iterator
    uint16_t valRel = 0;
    /* Check the application's current state. */
    switch (appData.state) {
            /* Application's initial state. */
        case APP_STATE_INIT:
        {
            // init des périphérique
            DRV_TMR0_Start();
            DRV_TMR1_Start();
            DRV_IC0_Start();

            lcd_init();
            lcd_bl_on();
            //affichage init 
            printf_lcd("Epr.MINF MesPulse");
            // A adapter pour les 2 noms sur 2 lignes
            lcd_gotoxy(C1, L2);
            printf_lcd("Clauzel ");
            appData.usrState = APP_USART_SEND;
            for (i = 0; i < 3; i++) {
                appData.ArrayValue[i] = 0;
            }
            appData.ArrayValue[3] = '\0';

            APP_UpdateState(APP_STATE_IDLE);
            break;
        }

        case APP_STATE_SERVICE_TASKS:
        {
            // ...


            BSP_LEDOn(BSP_LED_1);
            switch (appData.usrState) {
                case APP_CALC:
                    // durée imp 1ms-> 0% 2ms ->100% : 10us/%
                    // pente * consigne +offset  
                       valRel = (appData.Thaut * 100000)-100;


                    break;
                case APP_DISP:
                    //ligne 3 en ms et 4 en % 
                    lcd_gotoxy(C1, L3);
                    tempHautUP = (uint8_t) appData.Thaut; //to lose .xxx
                    tempHautDown = ((appData.Thaut - tempHautUP)*100); //pour 2 after . 
                    //met en forme 
                    itoa(&appData.ArrayValue[0],tempHautUP,10);
                    appData.ArrayValue[1]='.';
                    itoa(&appData.ArrayValue[2],tempHautDown,10);
                    //affiche Ton 
                    printf_lcd("t_On: %d.%d ms", tempHautUP, tempHautDown);
                    lcd_gotoxy(C1, L4);
                    
                    //afiche rel should be the same as tempHautDown
                    //printf_lcd("rel. : %2d %", valRel);
        
                    
                    printf_lcd("rel. : %2d %", tempHautDown);
                    break;
                case APP_USART_SEND:
                    //msie en forme 
                    //3char +%+0x0d +0x0A 
                    if (!DRV_USART_TransmitBufferIsFull(DRV_USART_INDEX_0)) {
                        /*
                        //this send the Ton in ms to the usart (not asked im dumb))
                        for (i = 0; i <= 3; i++) {
                            DRV_USART_WriteByte(DRV_USART_INDEX_0, appData.ArrayValue[i]);
                        }
                        DRV_USART_WriteByte(DRV_USART_INDEX_0, 0x0D);
                        DRV_USART_WriteByte(DRV_USART_INDEX_0, 0x0A);
                        */
                        
                        itoa(appData.ArrayValue,valRel,10);
                        
                        for (i = 0; i < 3; i++) {
                            //0->2 = 3 
                            DRV_USART_WriteByte(DRV_USART_INDEX_0, appData.ArrayValue[i]);
                        }   
                        DRV_USART_WriteByte(DRV_USART_INDEX_0, 0x0D);
                        DRV_USART_WriteByte(DRV_USART_INDEX_0, 0x0A);
                        
                    }


                    break;

            }
            BSP_LEDOff(BSP_LED_1);

            break;
        }
        case APP_STATE_IDLE:
            //do nothing
            break;

            /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}

void APP_TIMER1_CALLBACK(void) {
    static uint16_t cntCadence = 0;


    if (cntCadence % _1SECMS == 0) {
        cntCadence = 0;
        APP_UpdateState(APP_STATE_SERVICE_TASKS);

    } else {
        cntCadence++;
    }



}

void APP_UpdateState(APP_STATES NewState) {
    appData.state = NewState;
}

void APP_IC_CALLBACK(void) {

    int16_t Capt2Falling;
    uint16_t Capt2Rising;
    uint16_t PeriodeTick, ThighTick;
    static uint16_t OldCaptRising;
    float PeriodeSignal;
    float Thigh;

    // IC3 correspond à RD10
    if (PORTDbits.RD10 == 1) {

        // Obtient capture du flanc montant
        Capt2Rising = PLIB_IC_Buffer16BitGet(IC_ID_3);
        // Calcul de la période
        PeriodeTick = Capt2Rising - OldCaptRising;
        // mise à jour memo capture au flanc montant
        OldCaptRising = Capt2Rising;
        PeriodeSignal = PeriodeTick * 0.4 / 1000; // en ms
        // 0.4 us par Tick
        // Fourni à l'application
        appData.Periode = PeriodeSignal;
        PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_INPUT_CAPTURE_3);
        BSP_LEDToggle(BSP_LED_1);
    } else {
        // Obtient capture du flanc descendant
        Capt2Falling = PLIB_IC_Buffer16BitGet(IC_ID_3);
        // Calcul du Thigh
        ThighTick = Capt2Falling - OldCaptRising;
        Thigh = (ThighTick * 0.4) / 1000; // en ms
        // 0.4 us par Tick
        // Fourni à l'application
        appData.Thaut = Thigh;



    }
}
/*******************************************************************************
End of File
 */
