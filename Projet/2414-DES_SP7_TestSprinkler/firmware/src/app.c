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
#include "mcp79411.h"
#include "Mc32DriverAdc.h"
#include "Mc32_I2cUtil_SM.h"
#include "PIC32130_AT42QT2120_I2C.h"
#include "Driver_SR_SN74HCS596QPWRQ1.h"
#include "Mc32gestI2cSeeprom.h"
#include "Mc32_sdFatGest.h"
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
S_AT42QT2120 s_getDataSensor; //Structure pour la rec�ption des datas




// Nouvelle séquence de notes pour la mélodie demandée
float songMelody[] = {
    NOTE_RE, NOTE_MI, NOTE_RE,
    NOTE_RE, NOTE_RE,
    NOTE_RE, NOTE_MI, NOTE_RE,
    NOTE_RE, NOTE_FA, NOTE_SOL, NOTE_FA, NOTE_MI, NOTE_RE
};

#define SONG_LENGTH (sizeof(songMelody)/sizeof(songMelody[0]))


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
    
    static uint8_t osc_status = 1;
    static uint8_t ret;
    
    /* Check the application's current state. */
    switch ( appData.state )
    {
        
        /* Application's initial state. */
        case APP_STATE_INIT:
        {
            // Ensure SPI1 is initialized (only if not already done by system)
           // if (DRV_SPI_Status(SPI_ID_1) != SYS_STATUS_READY) {
               // DRV_SPI_Initialize(DRV_SPI_INDEX_1, (SYS_MODULE_INIT*)NULL);
            //}
            /*
            appData.timeofRTC.sec = 0;
            appData.timeofRTC.sec =6;
            appData.timeofRTC.min =0;
            appData.timeofRTC.wkday=0;
            appData.timeofRTC.hour=0;
            appData.timeofRTC.mth=0;
            appData.timeofRTC.date=0;
              */      
            //ret = mcp79411_set_time(&appData.timeofRTC);
            
            
            //DR
            //mcp79411_get_time(&timeofRTC);
            SR_Init(&appData.sysLeds);
            
            ret = DRV_SPI_Status(SPI_ID_1);
            //DRV_SPI_INIT
            DRV_ADC_Initialize();
            
            
            
            DRV_ADC_Open(); 
            DRV_ADC_Start();
            
           // DRV_TMR2_Start();
            //BSP_InitADC10();
            appData.state = APP_STATE_SERVICE_TASKS;
            LIFELED_GREENOff();
            
        } break;

        case APP_STATE_SERVICE_TASKS:
        {
          
            // Check if SPI1 is ready before SD card operations
            //if (DRV_SPI_Status(SPI_ID_1) != SYS_STATUS_READY) {
                // SPI not ready, skip SD card operations and optionally set an error state or retry
                // You can add a debug LED or log here if needed
               // LIFELED_GREENToggle();
                // Optionally, you can set an error state or retry logic
               // appData.state = APP_ERROR; // Transition to an error state
               // break;
            //}

            /* If an SD card is mounted */
           // if(sd_getState() != APP_MOUNT_DISK){
                /* Wait until SD available */
              //  while(sd_getState() != APP_IDLE){
             //       sd_fat_task();
               // }

                //sd_logger_scheduleWrite(&appData.timeofRTC);



                /* Unmount disk */
               // sd_setState(APP_UNMOUNT_DISK);
                /* Wait until unmounted*/
               // while(sd_getState() != APP_IDLE){
               //     sd_fat_task();
               // }
            //}
            
            ret = DRV_SPI_Status(SPI_ID_1);
         //   if (ret != SYS_STATUS_READY)
          //  {
                              
             //   if (sd_getState() != APP_MOUNT_DISK)
//{
                 //   sd_fat_task();
                   // ret= DRV_USART_Open(DRV_USART_INDEX_0, DRV_IO_INTENT_EXCLUSIVE);
                    //if (ret == DRV_HANDLE_INVALID) {
                        // Unable to open the driver
                        // May be the driver is not initialized or the initialization
                        // is not complete.
                  //  }
                   // DRV_USART_WriteByte(DRV_USART_INDEX_0, 'a');
                    //DRV_USART_Close(DRV_USART_INDEX_0);
               // }
               // sd_fat_task();
            
            //sd_fat_task();
            GetInputsStates();
            //timeofRTC.sec =0;
           // ret =mcp79411_get_time(&timeofRTC);
            //osc_status = mcp79411_get_status(&timeofRTC);
            //ret = mcp79411_set_OscOn(&timeofRTC);
            //osc_status = mcp79411_get_status(&timeofRTC);
                
           // DRV_SDMMC_IsAttached
            
            if (appData.SySwitch.FreeIn1_conf)
            {
                //DRV_TMR0_Start();
                 appData.state = APP_STATE_BUZZER;
            }
            else
            {
                //DRV_TMR0_Stop();
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
                sd_logger_scheduleWrite(&appData.timeofRTC);
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



        case APP_STATE_BUZZER:
        {
            //call to play a song
            PlaySong();
            // Transition back to the service tasks state
            appData.state = APP_STATE_SERVICE_TASKS;
           
        } break;  

        case APP_ERROR:
        {
            /* An error occurred, handle it here */
            // You can set an error LED or log the error
            LIFELED_GREENToggle();
            // Optionally, you can reset the state machine or take other actions
            appData.state = APP_STATE_INIT; // Reset to initial state
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
    appData.SySwitch.SPBIn2_conf=  SC1StateGet();
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
 * Fct d'attente en fct du param d'entr�e en ms 
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
 

void SetTMR0_Frequency(float freq_hz)
{
    uint16_t prescaler_values[] = {1, 2, 4, 8, 16, 32, 64, 256};
    TMR_PRESCALE prescaler_enums[] = {
        TMR_PRESCALE_VALUE_1, TMR_PRESCALE_VALUE_2, TMR_PRESCALE_VALUE_4, TMR_PRESCALE_VALUE_8,
        TMR_PRESCALE_VALUE_16, TMR_PRESCALE_VALUE_32, TMR_PRESCALE_VALUE_64, TMR_PRESCALE_VALUE_256
    };
    uint8_t i =0;

    uint32_t period = 0;
    for (i = 0; i < 8; i++) {
        period = (uint32_t)(PBCLK_FREQ / (prescaler_values[i] * freq_hz)) - 1;
        if (period <= 0xFFFF) {
         
          // Set prescaler
            PLIB_TMR_PrescaleSelect(TMR_ID_1, prescaler_enums[i]);
            // Set period
            DRV_TMR0_PeriodValueSet(period);
            break;
        }
    }
    // Optionally restart timer
    DRV_TMR0_Stop();
    DRV_TMR0_Start();
}


// Function to play a song (blocking, for demo)
void PlaySong(void) {
    static uint16_t songDurations[36] = {
        300,300,300,  300,300,300,  300,300,300,  200,200,200,200,200,200,
        300,300,300,  300,300,300,  300,300,300,  200,200,200,200,200,200,200,200,200,200
    };
    uint8_t i = 0;
    for(i = 0; i < SONG_LENGTH; i++) {
        SetTMR0_Frequency(songMelody[i]);
        DRV_TMR0_Start();
        APP_WaitStart(songDurations[i]);
        DRV_TMR0_Stop();
        APP_WaitStart(40); // Petite pause
    }
}



/*******************************************************************************
 End of File
 */
