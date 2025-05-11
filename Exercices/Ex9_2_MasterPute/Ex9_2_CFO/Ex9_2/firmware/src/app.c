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
#include "Mc32_I2cUtil_SM.h"
#include "Mc32gestI2cLM92_SM.h"

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
S_Descr_LM92_SM DescrLm92;

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
void APP_UpdateState(APP_STATES NewState)
{
    // Met à jour l'état de l'application avec la nouvelle valeur
    appData.state = NewState;
    
    // Aucune sortie explicite, car la mise à jour est effectuée directement sur la variable d'état globale.
    // La fonction n'a pas de valeur de retour (void).
}

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
            lcd_init();
            lcd_bl_on();
            
            lcd_gotoxy(1,1);
            printf_lcd("Exo9_2");
            lcd_gotoxy(1,2);
            printf_lcd("CFO");
            lcd_gotoxy(1,3);
            printf_lcd("Temp: ");
            
            I2C_LM92_SM_Init(&DescrLm92, true);
            
            DRV_TMR0_Start();
            
            APP_UpdateState(APP_STATE_WAIT); 
            
            break;
        }

        case APP_STATE_SERVICE_TASKS:
        {
            // Exécute une commande pour interagir avec le capteur LM92 via I2C
            I2C_LM92_SM_Execute(&DescrLm92);

            // Vérifie si le capteur LM92 est prêt pour une nouvelle interaction
            if(I2C_LM92_SM_IsReady(&DescrLm92))
            {
                // Déplace le curseur de l'affichage LCD à la colonne 1, ligne 2
                lcd_gotoxy(1,2);

                // Récupère la valeur brute de la température mesurée par le capteur LM92
                DescrLm92.RawTemp = I2C_LM92_SM_GetRawTemp(&DescrLm92);
                // Affiche la valeur brute de la température en format hexadécimal sur l'écran LCD
                printf_lcd("LM92 raw: %04X ", DescrLm92.RawTemp);

                // Déplace le curseur de l'affichage LCD à la colonne 1, ligne 3
                lcd_gotoxy(1,3);

                // Récupère la température en milli degrés mesurée par le capteur LM92
                DescrLm92.TempMilli = I2C_LM92_SM_GetTempMilli(&DescrLm92);
                // Affiche la température en milli degrés sur l'écran LCD en format décimal
                printf_lcd("LM92 Tmilli: %06d", DescrLm92.TempMilli);

                // Déplace le curseur de l'affichage LCD à la colonne 1, ligne 4
                lcd_gotoxy(1,4);

                // Récupère la température en degrés Celsius mesurée par le capteur LM92
                DescrLm92.Temperature = I2C_LM92_SM_GetTemp(&DescrLm92);
                // Affiche la température en degrés Celsius sur l'écran LCD en format flottant
                printf_lcd("LM92 temp: %6.2f ", DescrLm92.Temperature);

                // Redémarre le capteur LM92 pour qu'il soit prêt pour une nouvelle lecture
                I2C_LM92_SM_Restart(&DescrLm92);
            }
            appData.state = APP_STATE_WAIT;
            break;
        }

        /* TODO: implement your application state machine.*/
        
        case APP_STATE_WAIT:

        /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}

 

/*******************************************************************************
 End of File
 */
