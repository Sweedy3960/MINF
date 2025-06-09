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
#include "mcp79411.h"


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
    static int mcp_state = 0;
    static bool mcp_done = false;
    static int at42qt_state = 0;
    static bool at42qt_done = false;

    /* Check the application's current state. */
    switch ( appData.state )
    {
        /* Application's initial state. */
        case APP_STATE_INIT:
        {
            I2C_SM_init(1);
            APP_InitMcp79411();
            mcp79411_init();
            appData.state = APP_STATE_IDLE;
        }

        case APP_STATE_SERVICE_TASKS:
        {
          
            break;
        }
        case APP_STATE_IDLE:
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
 
void APP_TIMER4_CALLBACK(void)
{
    appData.state = APP_STATE_SERVICE_TASKS;
}
/*******************************************************************************
 End of File
 */

// Wrapper non bloquant pour lecture RTC (à placer dans mcp79411.c si besoin)
void mcp79411_get_time_nb(mcp79411_time* time, int* state, bool* done)
{
    static uint8_t reg_time_bytes[sizeof(mcp79411_TIME_KEEPING)];
    static int reg_state = 0;
    static bool reg_done = false;
    switch (*state) {
        case 0:
            // Lancer la lecture non bloquante du bloc RTC
            mcp79411_rtc_reg_read_nb(MCP79411_REG_RTCC_RTCSEC, reg_time_bytes, sizeof(reg_time_bytes), &reg_state, &reg_done);
            if (reg_done) {
                *state = 1;
                reg_done = false;
            }
            break;
        case 1:
            // Décodage BCD -> décimal
            time->sec = mcp79411_bcd2dec(reg_time_bytes[0] & 0x7F);
            time->min = mcp79411_bcd2dec(reg_time_bytes[1] & 0x7F);
            time->hour = mcp79411_bcd2dec(reg_time_bytes[2] & 0x3F);
            time->wkday = mcp79411_bcd2dec(reg_time_bytes[3] & 0x07);
            time->date = mcp79411_bcd2dec(reg_time_bytes[4] & 0x3F);
            time->mth = mcp79411_bcd2dec(reg_time_bytes[5] & 0x1F);
            time->year = mcp79411_bcd2dec(reg_time_bytes[6]);
            *done = true;
            *state = 0;
            break;
    }
}
// Wrapper non bloquant pour lecture d'un bloc RTC (à placer dans mcp79411.c si besoin)
void mcp79411_rtc_reg_read_nb(uint8_t reg_addr, uint8_t* rx_buffer, uint16_t len, int* state, bool* done)
{
    static int write_state = 0;
    static bool write_done = false;
    static int read_state = 0;
    static bool read_done = false;
    switch (*state) {
        case 0:
            // Ecriture de l'adresse du registre
            mcp79411_rtc_iic_write_nb(&reg_addr, 1, &write_state, &write_done);
            if (write_done) {
                *state = 1;
                write_done = false;
            }
            break;
        case 1:
            // Lecture des données
            mcp79411_rtc_iic_read_nb(rx_buffer, len, &read_state, &read_done);
            if (read_done) {
                *done = true;
                *state = 0;
                read_done = false;
            }
            break;
    }
}
