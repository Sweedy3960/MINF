/*******************************************************************************
  MPLAB Harmony Application Header File

  Company:
    Microchip Technology Inc.

  File Name:
    app.h

  Summary:
    This header file provides prototypes and definitions for the application.

  Description:
    This header file provides function prototypes and data type definitions for
    the application.  Some of these are required by the system (such as the
    "APP_Initialize" and "APP_Tasks" prototypes) and some of them are only used
    internally by the application (such as the "APP_STATES" definition).  Both
    are defined here for convenience.
*******************************************************************************/

//DOM-IGNORE-BEGIN
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
//DOM-IGNORE-END

#ifndef _APP_DISP_H
#define _APP_DISP_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "system_config.h"
#include "system_definitions.h"
#include "Display.h"
#include"LCD_Driver.h"
#include "ugui.h"
#include "ugui_config.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
// DOM-IGNORE-END 
#define DC_MODE false
#define AC_MODE true

// *****************************************************************************
// *****************************************************************************
// Section: Type Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application states

  Summary:
    Application states enumeration

  Description:
    This enumeration defines the valid application states.  These states
    determine the behavior of the application at various times.
*/

typedef enum
{
	/* Application's state machine's initial state. */
	APP_DISP_STATE_INIT=0,
	APP_DISP_STATE_SERVICE_TASKS,

	/* TODO: Define states used by the application state machine. */

} APP_DISP_STATES;


// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    Application strings and buffers are be defined outside this structure.
 */

typedef struct
{
    /* The application's current state */
    APP_DISP_STATES state;
    
	bool needDisplayUpdate;
	uint8_t positionCursor;
	uint8_t positionList;
    uint16_t TimerScreen;
    bool dispInit;
    uint8_t currentScreen;
    /* TODO: Define any additional data used by the application. */

} APP_DISP_DATA;
typedef enum
{
	MODULE_1 = 1,
	MODULE_2,
	MODULE_3,
	MODULE_4,
	MODULE_5,
	MODULE_6,
	MODULE_7,
} E_MODULE_ID;
typedef enum
{
	EMPTY = 0,
	MODULE_23132,
}E_MODULE_MODEL;

typedef struct
{
	E_MODULE_ID id;
	E_MODULE_MODEL model;
} MODULE_SLOT_DATA;


// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Routines
// *****************************************************************************
// *****************************************************************************
/* These routines are called by drivers when certain events occur.
*/
	
// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Summary:
     MPLAB Harmony application initialization routine.

  Description:
    This function initializes the Harmony application.  It places the 
    application in its initial state and prepares it to run so that its 
    APP_Tasks function can be called.

  Precondition:
    All other system initialization routines should be called before calling
    this routine (in "SYS_Initialize").

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    APP_Initialize();
    </code>

  Remarks:
    This routine must be called from the SYS_Initialize function.
*/

/**
 * @brief Initialise l'application Display.
 *
 * Cette fonction initialise l'application Display et la place dans son état initial.
 * @return void
 */
void APP_Disp_Initialize ( void );

/**
 * @brief Callback du timer 5 pour l'affichage.
 *
 * Cette fonction est appelée lors de l'interruption du timer 5 pour gérer les événements liés à l'affichage.
 * @return void
 */
void APP_DISP_TIMER5_CALLBACK(void);

/**
 * @brief Fonction principale des tâches Display.
 *
 * Cette fonction gère la machine d'état et la logique principale de l'application Display.
 * @return void
 */
void APP_Disp_Tasks( void );

/**
 * @brief Permet d'éditer le nom d'un signal dans l'IHM.
 *
 * @param index Index du signal à éditer.
 * @return void
 */
void EditSignalName_IHM(int index);

/**
 * @brief Change l'écran affiché.
 *
 * @param newScreen Nouvel écran à afficher.
 * @param touchStates États tactiles.
 * @param forceUpdate Forcer la mise à jour de l'affichage.
 * @return void
 */
void App_Display_ChangeScreen(uint8_t newScreen, uint16_t *touchStates, bool forceUpdate);

/**
 * @brief Gère les entrées pour l'affichage.
 *
 * @param InputsStates États des entrées.
 * @return void
 */
void App_Display_HandleInputs(uint16_t *InputsStates);

/**
 * @brief Gère les entrées tactiles pour l'affichage.
 *
 * @param touchStates États tactiles.
 * @return void
 */
void App_Display_HandleTouch(uint16_t *touchStates);

#endif /* _APP_H */

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

/*******************************************************************************
 End of File
 */

