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
#include "Mc32_I2cUtil_SM.h"
#include "PIC32130_AT42QT2120_I2C.h"
#include "Driver_SR_SN74HCS596QPWRQ1.h"
#include "Mc32gestI2cSeeprom.h"
#include "mcp79411.h"
#include "mcp79411_interface.h"
#include "Mc32_I2cUtilCCS.h"


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
S_AT42QT2120 s_newDataSensor; //Structure pour envoie des nouvelles datas
S_AT42QT2120 s_dataSensor;    //Structure pour l'envoie des datas
S_AT42QT2120 s_getDataSensor; //Structure pour la recéption des datas

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

   // SR_LEDS LEDS;
    bool NACK = false;
    mcp79411_time timeofRTC;
    static uint8_t ret;
    
    /* Check the application's current state. */
    switch ( appData.state )
    {
        
        /* Application's initial state. */
        case APP_STATE_INIT:
        {
            //AT42QT_Init();
            //SR_LED_OE_2On(); //éteind
            //TESTPINOn(); //étein
            
            
            i2c_init(1);
            AT42QT_Init();
           // mcp79411_init();
            //mcp79411_TIME_KEEPING time;
            //time.bytes= 0;
            // 
            //I2C_InitMCP79411();
           // mcp79411_time time;
            //time.min = 1;
            mcp79411_init();
            ret = mcp79411_set_time(&timeofRTC);
            
            
            SR_Init(&appData.sysLeds);
            
            
            DRV_ADC_Initialize();
            
            
            
            DRV_ADC_Open(); 
            DRV_ADC_Start();
            
            DRV_TMR2_Start();
            //BSP_InitADC10();
            appData.state = APP_STATE_SERVICE_TASKS;
            LIFELED_GREENOff();
            
        } break;

        case APP_STATE_SERVICE_TASKS:
        {
            GetInputsStates();
            //et =mcp79411_get_time(&timeofRTC);
            
            
            if (appData.SySwitch.FreeIn1_conf)
            {
                DRV_TMR0_Start();
            }
            else
            {
                DRV_TMR0_Stop();
                //appData.valAD=BSP_ReadAllADC();
            }
            
            //SR_LoadData(appData.SR_leds ,0);
            
            if (appData.SySwitch.FreeIn2_conf)
            {
                SR_Update(&appData.sysLeds);
                APP_WaitStart(1000);
                //appData.sysLeds.cmd_leds = 0xFFFF;
                
            }
            if(appData.SySwitch.FreeIn3_conf)
            {
                //SPB_OUT3_CMDToggle();
            }
            else
            {
            
            }
          //AdcReadAllSamples();
            if (appData.SySwitch.FreeIn4_conf) {
 
                s_dataSensor.valKey8to11 = AT42QT_Read_Key8to11(NACK);
                s_dataSensor.valKey0to7 = AT42QT_Read_Key0to7(NACK);
            }
           
            
            
            
            
            
         
            
        } break;

        /* TODO: implement your application state machine.*/
        

        /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}

void GetInputsStates(void) {
    
    
    
    appData.SySwitch.SPBIn3_conf = SC3StateGet();
    appData.SySwitch.SPBIn2_conf = SC2StateGet();
    appData.SySwitch.SPBIn2_conf= SC1StateGet();
    appData.SySwitch.FreeIn1_conf= FC1StateGet();
    appData.SySwitch.FreeIn2_conf= FC2StateGet();
    appData.SySwitch.FreeIn3_conf= FC3StateGet();
    appData.SySwitch.FreeIn4_conf= FC4StateGet();
    appData.SySwitch.FreeIn5_conf= FC5StateGet();
    

}
 void AdcReadAllSamples(void)
 {
    uint8_t i =0;
    static uint8_t SampleReadyToRead;
    SampleReadyToRead = DRV_ADC_SamplesAvailable();
 
            if (SampleReadyToRead) {
                for (i = 0; i < 14; i++) {
                    appData.valAD[i] = DRV_ADC_SamplesRead(i);

 
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
 




/*
 * Fct d'attente en fct du param d'entrée en ms 
 * utilisation du timer 1 attente = 1ms
*/
void APP_WaitStart(uint16_t waitingTime_ms) {

    appData.AppDelay = waitingTime_ms - 1;
    DRV_TMR3_Start();
    appData.APP_DelayTimeIsRunning = 1;
    while (appData.APP_DelayTimeIsRunning) {
    }
    DRV_TMR3_Stop();
}
   void APP_TIMER4_CALLBACK(void){
    if (appData.AppDelay > 0) {
        appData.AppDelay--;
    } else {
        appData.APP_DelayTimeIsRunning = 0;
    }
    
  }
 
/*******************************************************************************
 End of File
 */
