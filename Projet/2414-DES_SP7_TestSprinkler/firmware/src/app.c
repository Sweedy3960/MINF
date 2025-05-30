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
#include <stdarg.h>
#include <stdio.h>



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
S_AT42QT2120 s_dataSensor; //Structure pour l'envoie des datas
S_AT42QT2120 s_getDataSensor; //Structure pour la rec�ption des datas




// Nouvelle séquence de notes pour la mélodie demandée
float songMelody[10] = {
    //like composing a song "randomly"
    NOTE_DO, NOTE_RE, NOTE_DO, NOTE_RE, NOTE_MI, NOTE_FA,
    NOTE_SOL, NOTE_FA, NOTE_MI, NOTE_RE
};

#define SONG_LENGTH (sizeof(songMelody)/sizeof(songMelody[0]))


uint8_t DebugUART_Enable =0; // Flag to enable/disable debug UART output
uint8_t InitMcp =0;
uint8_t InitADC =1;
uint8_t InitTouchCap =0;



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

void APP_Initialize(void)
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

void APP_Tasks(void)
{
    //timer1 used to buzz RN 
    //timer 2 used to SR LED (trying)

    // SR_LEDS LEDS;
    bool NACK = false;

    static uint8_t osc_status = 1;
    static uint8_t ret;
    static APP_STATES st = APP_STATE_INIT;
    /* Check the application's current state. */
    switch (appData.state)
    {

        /* Application's initial state. */
    case APP_STATE_INIT:
    {
        if(DebugUART_Enable) DebugUART_Print("[SM] Starting INIT functionality\r\n");
        //this init the structures  and configures necessary things
        if(InitMcp)
        {
            APP_InitMcp79411();
        }
        if(InitADC)
        {
            APP_InitADC();
        }
        if(InitTouchCap)
        {
            AT42QT_Init();

        }
        //set the led life on 
        LIFELED_GREENOff();


        //ret = DRV_SPI_Status(SPI_ID_1);
        //DRV_SPI_INIT
        // DRV_TMR2_Start();
        appData.state = APP_STATE_WAIT_START;


    }
    break;

    case APP_STATE_SERVICE_TASKS:
    {
        if(DebugUART_Enable) DebugUART_Print("[SM] Starting SERVICE_TASKS functionality\r\n");
        // Boucle de test : itère sur tous les états de la SM
        for( st= APP_STATE_INIT; st <= APP_STATE_READ_CAPACITIVE_SENSOR; st++) {
            appData.state = st;
            if(DebugUART_Enable) DebugUART_Print("[SM] Test loop: switched to state %d\r\n", st);
            // Appeler APP_Tasks pour exécuter l'état (optionnel, sinon la boucle ne fait que changer l'état)
            // APP_Tasks(); // Décommenter si on veut exécuter la logique de chaque état
        }
       
         //set the led life on 
        LIFELED_GREENToggle();
    }
    break;
    case APP_STATE_WAIT_START:
    {
        if(DebugUART_Enable) DebugUART_Print("[SM] Starting WAIT_START functionality\r\n");
        //call to wait start
        //this is used to wait for a certain time before starting the application
        //this is used to let the system stabilize
        APP_WaitStart(1000);
        //after waiting we can start the application
        appData.state = APP_STATE_READ_SENSOR;
        LIFELED_GREENToggle();
    }
    break;
    case APP_STATE_READ_SENSOR:
    {
        if(DebugUART_Enable) DebugUART_Print("[SM] Starting READ_SENSOR functionality\r\n");
        //we should allways read inputs
      //if any change is detected logg it in SD and update the Serial reg
     
      LIFELED_GREENToggle();
    }
        break;
    case APP_STATE_ERROR:
    {
        if(DebugUART_Enable) DebugUART_Print("[SM] Starting ERROR functionality\r\n");
        //in case of error we can reset the system
        //or we can try to recover from the error
        //for now we will just reset the system
        
        LIFELED_GREENToggle();
    }
    break;
    case APP_STATE_READ_ADC:
    {
        if(DebugUART_Enable) DebugUART_Print("[SM] Starting READ_ADC functionality\r\n");
        //call the ADC fct 
        APP_AdcReadAllSamples();
        //WE NEED TO MODIFY ADC FCT LATER TO CHECK IF IT GOES O WITH A RETURN 
        LIFELED_GREENToggle();
    }
    break;
    case APP_STATE_READ_CONFIG_INPUTS:
    {
        if(DebugUART_Enable) DebugUART_Print("[SM] Starting READ_CONFIG_INPUTS functionality\r\n");
        //call to get the inputs states
        //this is used to get the inputs states from the switches
        //and store them in the appData.SySwitch structure
        //this is used to check if a switch is pressed or not
        //and then take actions accordingly
        APP_GetInputsStates();
        //we need a flag to  know if the inputs have changed with return           
        LIFELED_GREENToggle();

    }
    break;
    case APP_STATE_SERIAL_LEDS:
    {
        if(DebugUART_Enable) DebugUART_Print("[SM] Starting SERIAL_LEDS functionality\r\n");
        //call to manage the serial leds
        //this is used to manage the serial leds
        //and update their states
        LIFELED_GREENToggle();
        
    }
    break;
    case APP_STATE_READ_RTC:
    {
        if(DebugUART_Enable) DebugUART_Print("[SM] Starting READ_RTC functionality\r\n");
        //previously used for debug
        //osc_status = mcp79411_get_status(&timeofRTC);
        //ret = mcp79411_set_OscOn(&timeofRTC);
        //osc_status = mcp79411_get_status(&timeofRTC);
        if(InitMcp)
        {
            mcp79411_get_time(&appData.timeofRTC);
        }   
        //this state should be called if a change appear on 
        //any changes of any inputs 
        //and then we should update the SD logger
        LIFELED_GREENToggle();

    }
    break;
    case APP_STATE_WRITE_SDCARD:
    {
        if(DebugUART_Enable) DebugUART_Print("[SM] Starting WRITE_SDCARD functionality\r\n");
        if(InitMcp)
        {
            sd_logger_scheduleWrite(&appData.timeofRTC);
            // Check if SD card is mounted
            if (sd_getState() == APP_MOUNT_DISK)
            {
                // Perform SD card operations
                sd_fat_task();
            
                // Unmount disk after operations
                sd_setState(APP_UNMOUNT_DISK);

                // Wait until unmounted
                uint32_t sd_timeout = 0;
                uint32_t sd_timeout_max = 1000000; // Limite arbitraire, à ajuster selon besoin
                while (sd_getState() != APP_IDLE)
                {
                    sd_fat_task();
                    sd_timeout++;
                    if(sd_timeout > sd_timeout_max) {
                        if(DebugUART_Enable) DebugUART_Print("[ERR] Timeout SD unmount!\r\n");
                        break;
                    }
                }
            }
            else
            {
                // Handle case where SD card is not mounted
                // You can set an error state or retry logic here
            
            }
        }
    }
    LIFELED_GREENToggle();
    break;

    case APP_STATE_BUZZER:
        {
            if(DebugUART_Enable) DebugUART_Print("[SM] Starting BUZZER functionality\r\n");
            //call to play a song
            APP_PlaySong();
            // Transition back to the service tasks stateB
            LIFELED_GREENToggle();
        }
        
        break;
    case APP_STATE_READ_CAPACITIVE_SENSOR:
    {
        if(DebugUART_Enable) DebugUART_Print("[SM] Starting READ_CAPACITIVE_SENSOR functionality\r\n");
        //call the capacitive sensor fct 
        //this is used to read the capacitive sensor
        //and store the data in the s_dataSensor structure
        //this is used to check if a key is pressed or not
         if(InitTouchCap)
        {
            s_dataSensor.valKey0to7 = AT42QT_Read_Key0to7(NACK);
            s_dataSensor.valKey8to11 = AT42QT_Read_Key8to11(NACK);
        }
        LIFELED_GREENToggle();

    }
        break;

    case APP_STATE_REPEAT:
    {
        if(DebugUART_Enable) DebugUART_Print("[SM] Starting REPEAT functionality\r\n");
        ///here we should repeat inputs to outputs if needed 
        //depending on SPB conf we should repecurt input to output
        if(appData.SySwitch.SPBIn1_conf.state == SPB_IN_REPEAT)
        {
            //repeat input 1 to output 1
            if(DebugUART_Enable) DebugUART_Print("[SM] Repeating SPBIn1 to output 1\r\n");
            //call a fct to modify appstatesleds.syssled.cmdleds
            //call a fct to modify appdata.cmdrelayout(need to be created)

        }
        else
        {
            
        } 
        LIFELED_GREENToggle();
    }
    break;
    default:
        {
            if(DebugUART_Enable) DebugUART_Print("[SM] Entered DEFAULT state\r\n");
            /* TODO: Handle error in application's state machine. */
            break;
        }
    
    }
}
    void APP_GetInputsStates(void)
    {


        //SPB's outpus derrranement states 
        appData.SySwitch.SPBIn1_conf.state = SC3StateGet();
        appData.SySwitch.SPBIn2_conf.state = SC2StateGet();
        appData.SySwitch.SPBIn2_conf.state = SC1StateGet();
        appData.SySwitch.FreeIn1_conf.state = FC1StateGet();
        appData.SySwitch.FreeIn2_conf.state = FC2StateGet();
        appData.SySwitch.FreeIn3_conf.state = FC3StateGet();
        appData.SySwitch.FreeIn4_conf.state = FC4StateGet();
        appData.SySwitch.FreeIn5_conf.state = FC5StateGet();
    }

    void APP_AdcReadAllSamples(void)
    {
        uint8_t i = 0;
        static uint8_t SampleReadyToRead;
        SampleReadyToRead = DRV_ADC_SamplesAvailable();

        if (SampleReadyToRead)
        {
            for (i = 0; i < 14; i++)
            {
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
    void APP_WaitStart(uint16_t waitingTime_ms)
    {

        appData.AppDelay = waitingTime_ms - 1;
        DRV_TMR3_Start();
        appData.APP_DelayTimeIsRunning = 1;
        // Garde-fou : timeout logiciel (2x le temps demandé)
        uint32_t timeout = 0;
        uint32_t timeout_max = (uint32_t)waitingTime_ms * 2;
        while (appData.APP_DelayTimeIsRunning)
        {
            timeout++;
            if(timeout > timeout_max) {
                if(DebugUART_Enable) DebugUART_Print("[ERR] Timeout dans APP_WaitStart !\r\n");
                break;
            }
        }
        DRV_TMR3_Stop();
    }

    void APP_TIMER4_CALLBACK(void)
    {
        if (appData.AppDelay > 0)
        {
            appData.AppDelay--;
        }
        else
        {
            appData.APP_DelayTimeIsRunning = 0;
        }

    }

    void APP_SetTMR0_Frequency(float freq_hz)
    {
        //we should verify if prescaler value is disponible for the TMR used
        uint16_t prescaler_values[] = {1, 2, 4, 8, 16, 32, 64, 256};
        TMR_PRESCALE prescaler_enums[] = {
            TMR_PRESCALE_VALUE_1, TMR_PRESCALE_VALUE_2, TMR_PRESCALE_VALUE_4, TMR_PRESCALE_VALUE_8,
            TMR_PRESCALE_VALUE_16, TMR_PRESCALE_VALUE_32, TMR_PRESCALE_VALUE_64, TMR_PRESCALE_VALUE_256
        };
        uint8_t i = 0;

        uint32_t period = 0;
        for (i = 0; i < 8; i++)
        {
            period = (uint32_t) (PBCLK_FREQ / (prescaler_values[i] * freq_hz)) - 1;
            if (period <= 0xFFFF)
            {

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

    void APP_PlaySong(void)
    {
        static uint16_t songDurations[10] = {
            500, 700, 500, 700, 700,
            700, 700, 700, 700, 1000
        };
        uint8_t i = 0;
        for (i = 0; i < SONG_LENGTH; i++)
        {
            APP_SetTMR0_Frequency(songMelody[i]);
            DRV_TMR0_Start();
            APP_WaitStart(songDurations[i]);
            DRV_TMR0_Stop();
            APP_WaitStart(40); // Petite pause
        }
    }

    void APP_InitMcp79411(void)
    {
        appData.timeofRTC.sec = 0;
        appData.timeofRTC.min = 0;
        appData.timeofRTC.sec = 1;
        appData.timeofRTC.hour = 0;
        appData.timeofRTC.mth = 0;
        appData.timeofRTC.date = 0;
        appData.timeofRTC.year = 0;
        mcp79411_set_time(&appData.timeofRTC);
        //mcp79411_get_time(&appData.timeofRTC);
    }

    void APP_InitADC(void)
    {
        uint8_t i;
        // Initialize ADC driver
        DRV_ADC_Initialize();
        // Open ADC driver
        DRV_ADC_Open();
        // Start ADC driver
        DRV_ADC_Start();

        // Initialize ADC samples
        for (i = 0; i < 14; i++)
        {
            appData.valAD[i] = 0;
        }
    }


// Fonction simple pour envoyer une chaîne sur l'UART (à adapter selon ton driver)
void DebugUART_Print(const char *format, ...) {
    char buffer[128];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    char *p = buffer;
    while (*p) {
        // Attendre que le buffer soit prêt
        while (!PLIB_USART_TransmitterIsEmpty(USART_ID_1));
        PLIB_USART_TransmitterByteSend(USART_ID_1, *p);
        ++p;
    }
}


void APP_SetRealyOut(void/*&appdata.cmdRealayOut cmd*/)
{
    uint8_t i;
    //this fct is used to set the relay outputs
    //we should use the appData.cmdRealayOut structure to set the relay outputs
    for(i=0;i<9;i++)
    {
        //set the relay output
        //we should use the appData.cmdRealayOut structure to set the relay outputs
        //this is used to set the relay outputs
        //and update the serial reg
        // = cmd[i];
         //mke an array with the good call for set the outpout
    }
  


}






    /*******************************************************************************
     End of File
     */
