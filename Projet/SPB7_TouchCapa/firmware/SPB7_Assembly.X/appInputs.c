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

#include "appInputs.h"
#include "app_taskctrl.h"
#include "app_eventbus.h"

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

APP_INPUTS_DATA appInputsData;

// Contrôle de tâche pour appInputs
extern app_task_ctrl_t inputsTaskCtrl;



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

void APP_Inputs_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    appInputsData.state = APP_INPUTS_STATE_INIT;

    
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

void APP_Inputs_Tasks ( void )
{
    //in case adc init causing problems
// if (!inputsTaskCtrl.isActive) 
//                break;
    /* Check the application's current state. */
    switch ( appInputsData.state )
    {
        /* Application's initial state. */
        case APP_INPUTS_STATE_INIT:
        {
            uint8_t i;
            // Initialize ADC driver
            DRV_ADC_Initialize();
            // Open ADC driver
            DRV_ADC_Open();
            // Start ADC driver
            DRV_ADC_Start();
            
            DRV_TMR2_Start();
            DRV_TMR1_Start();
            // Initialize ADC samples
            for (i = 0; i < 14; i++)
            {
                appInputsData.valAD[i] = 0;
            }
            appInputsData.state = APP_INPUTS_STATE_SERVICE_TASKS;
            break;
            
        }       
    case APP_INPUTS_STATE_SERVICE_TASKS:
        {
           
            if (!inputsTaskCtrl.isActive) 
                break;
           
            // Désactiver les autres tâches pendant la lecture
            touchTaskCtrl.isActive = false;
            displayTaskCtrl.isActive = false;
            ledTaskCtrl.isActive = false;
            // Lire les échantillons ADC
            // et mettre à jour les états des entrées

            APP_AdcReadAllSamples();
            APP_GetInputsStates();
           
            
            
            if (appInputsData.SySwitch.switchStates!=appInputsData.LastSySwitch.switchStates)
            {//||(test ad val) {
                //set the flag 
                appInputsData.evtToPubWasConf =true;
                inputsTaskCtrl.isDirty = true;
                appInputsData.LastSySwitch.switchStates = appInputsData.SySwitch.switchStates;
            }

            
           
            // Calcul d'un état global pour détection de changement 
            
            //si changement detecter mettr enn dirty 
            
           
            // Passer à l'état de service
            appInputsData.state = APP_INPUTS_STATE_IDLE;
            break;
        }   
    case APP_INPUTS_STATE_IDLE:
        {
            if (inputsTaskCtrl.isDirty) {
                // Publier l'événement sur le bus
                if(appInputsData.evtToPubWasConf)
                {
                    App_EventBus_Publish(EVT_INPUTS, &appInputsData.SySwitch.switchStates);
                }
                if(appInputsData.evtToPubWasAD)
                {
                    App_EventBus_Publish(EVT_INPUTS, &appInputsData.SySwitch.switchStates);
                }
                inputsTaskCtrl.isDirty = false;//clear
                 // Réactiver les autres tâches
                touchTaskCtrl.isActive = true;
                displayTaskCtrl.isActive = true;
                ledTaskCtrl.isActive = true;
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
void APP_AdcReadAllSamples(void)
{
    uint8_t i = 0;
    static uint8_t SampleReadyToRead;
    SampleReadyToRead = DRV_ADC_SamplesAvailable();
    if (SampleReadyToRead) {
        inputsTaskCtrl.isDirty = true; // ADC est "dirty" pendant la lecture
        for (i = 0; i < 14; i++) {
            appInputsData.valAD[i] = DRV_ADC_SamplesRead(i);
        }
    }
}

  void APP_GetInputsStates(void)
    {


        //SPB's outpus derrranement states 
        appInputsData.SySwitch.SPBIn1_conf = SC3StateGet();
        appInputsData.SySwitch.SPBIn2_conf = SC2StateGet();
        appInputsData.SySwitch.SPBIn2_conf = SC1StateGet();
        appInputsData.SySwitch.FreeIn1_conf = FC1StateGet();
        appInputsData.SySwitch.FreeIn2_conf = FC2StateGet();
        appInputsData.SySwitch.FreeIn3_conf = FC3StateGet();
        appInputsData.SySwitch.FreeIn4_conf = FC4StateGet();
        appInputsData.SySwitch.FreeIn5_conf = FC5StateGet();
        
        
    }
  
  
  void APP_TIMER_AD_CALL_BACK(void)
{
    // 200ms call back, on veut lire à chaque fois car c'est lent
    appInputsData.state = APP_INPUTS_STATE_SERVICE_TASKS;
    // Activer la tâche inputs
    inputsTaskCtrl.isActive = true;
}


/*******************************************************************************
 End of File
 */
