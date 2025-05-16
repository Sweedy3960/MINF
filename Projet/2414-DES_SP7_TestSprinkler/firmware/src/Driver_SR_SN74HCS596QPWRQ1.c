/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.c

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */

/* TODO:  Include other files here if needed. */
#include "Driver_SR_SN74HCS596QPWRQ1.h"
#include "app.h"
#include "stdlib.h"
/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

/* ************************************************************************** */
/** Descriptive Data Item Name

  @Summary
    Brief one-line summary of the data item.
    
  @Description
    Full description, explaining the purpose and usage of data item.
    <p>
    Additional description in consecutive paragraphs separated by HTML 
    paragraph breaks, as necessary.
    <p>
    Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.
    
  @Remarks
    Any additional remarks
 */
int global_data;


/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

/* ************************************************************************** */

/** 
  @Function
    int ExampleLocalFunctionName ( int param1, int param2 ) 

  @Summary
    Brief one-line description of the function.

  @Description
    Full description, explaining the purpose and usage of the function.
    <p>
    Additional description in consecutive paragraphs separated by HTML 
    paragraph breaks, as necessary.
    <p>
    Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.

  @Precondition
    List and describe any required preconditions. If there are no preconditions,
    enter "None."

  @Parameters
    @param param1 Describe the first parameter to the function.
    
    @param param2 Describe the second parameter to the function.

  @Returns
    List (if feasible) and describe the return values of the function.
    <ul>
      <li>1   Indicates an error occurred
      <li>0   Indicates an error did not occur
    </ul>

  @Remarks
    Describe any special behavior not described above.
    <p>
    Any additional remarks.

  @Example
    @code
    if(ExampleFunctionName(1, 2) == 0)
    {
        return 3;
    }
 */
void SR_Init(SR_Context *SRegData) {
    SRegData->state = SR_IDLE;
    SRegData->dataToSR = 0b0101010101010101;
    SRegData->SelectedLed = 0x8000; // Start with the MSB
}

void SR_Update() {
    /*
     boucle 1 a 16 
     * mask 0x01 et >>1 
     * 
     
     */
    static uint16_t i=0;
    for (i=0;i<15;i++)
    {
        (cmd_leds & 0x01);
        .cmd_leds>>1;
    }
    
    
    
    
    
    switch (SRegData->state) {
        case SR_IDLE:
            // No operation
            break;
        case SR_SHIFTING:
           
            if (SRegData->dataToSR & SRegData->SelectedLed) {
                
                SR_LED_DATAOn();
            } else {
                
                SR_LED_DATAOn();
            }
            
            SR_SRCLK_FKCDPToggle();
             APP_WaitStart(5);
            SR_SRCLK_FKCDPToggle();
            
            SR_SRCLK_FKCDPOn();

            
            APP_WaitStart(5);

            
            SR_SRCLK_FKCDPOn();

            SRegData->SelectedLed >>= 1;
            if (SRegData->SelectedLed == 0) {
                SRegData->state = SR_LATCHING;
            }
            break;
        case SR_LATCHING:
            
            SR_LED_CLKOn();
            APP_WaitStart(5);

            SR_LED_CLKOff();


            SRegData->state = SR_IDLE;
            break;
    }
}


/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

// *****************************************************************************

/** 
  @Function
    int ExampleInterfaceFunctionName ( int param1, int param2 ) 

  @Summary
    Brief one-line description of the function.

  @Remarks
    Refer to the example_file.h interface header for function usage details.
 */
void SR_LoadData(SR_Context *SRegData, uint16_t data) {
    if (SRegData->state == SR_IDLE) {
        SRegData->dataToSR = data;
        SRegData->SelectedLed = 0x8000;
        SRegData->state = SR_SHIFTING;
    }
}

void SR_LoadData2(SR_Context *SRegData, uint8_t data) {
    if (SRegData->state == SR_IDLE) {
        /*/*/
    }
}

/* *****************************************************************************
 End of File
 */
