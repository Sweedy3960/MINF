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

#include "app.h"
#include "stdlib.h"
#include "Driver_SR_SN74HCS596QPWRQ1.h"
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
SERIAL_REG_DATA SregData;


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
void SR_Init(SERIAL_REG_DATA *SRegData) {
    SregData.state = SR_IDLE;
    SregData.cmd_leds = 0b0101010101010101;
     
}

void SR_Update(SERIAL_REG_DATA *SregData) {
    /*
     boucle 1 a 16 
     * mask 0x01 et >>1 
     * 
     
     */
    static bool usingSr=false;
    static uint16_t i=0;
    
    usingSr=true;
 
    
    //put that to init 
    SR_LED_CLKOff();
    SR_SRCLK_FKCDPOff();
    //should be SR_LED_OE_1On but its
    // and activ low so 
    TESTPINOn();//set off 
    //TESTPINOff();//set on 
    SR_LED_OE_2On();//set off 
    
    //data valid at first clk
    SR_LED_DATAStateSet((SregData->cmd_leds & 0x01));   
    
    for (i=0;i<15;i++)
    {
        
        
        //first clk shifting 
        SR_SRCLK_FKCDPOn();
        //APP_WaitStart(0);
        SR_SRCLK_FKCDPOff();
        //latch output is shift clk inverted 
        SR_LED_CLKOn();
        //APP_WaitStart(0);
        SR_LED_CLKOff();
        //setting valid data before next clking 
        SregData->cmd_leds =SregData->cmd_leds>>1;
        SR_LED_DATAStateSet((SregData->cmd_leds & 0x01));   
    }
    TESTPINOff();//set on 
    SR_LED_OE_2Off();//set on
    
    
    
    //try to do a driver 
    /*
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
     */
    
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
void SR_LoadData(SERIAL_REG_DATA *SRegData, uint16_t data) {
    if (SRegData->state == SR_IDLE) {
        SRegData->cmd_leds = data;
        SRegData->state = SR_SHIFTING;
    }
}

void SR_LoadData2(SERIAL_REG_DATA *SRegData, uint8_t data) {
    if (SRegData->state == SR_IDLE) {
        /*/*/
    }
}

/* *****************************************************************************
 End of File
 */
