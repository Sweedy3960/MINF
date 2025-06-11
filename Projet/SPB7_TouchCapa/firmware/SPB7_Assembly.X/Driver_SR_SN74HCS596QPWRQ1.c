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

#include "appReg.h"
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
//SERIAL_REG_DATA SregData;


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
    SRegData->state = SR_IDLE;
    SRegData->cmd_leds = 0xFFFF;
    SR_LED_CLKOff();
    SR_SRCLK_FKCDPOff();
    //should be SR_LED_OE_1On but its
    // and activ low so 
    //TESTPINOn();//set off 
    //TESTPINOff();//set on 
    SR_LED_OE_2On();//set off 
    SR_LED_OE_1On();
    //return  SRegData;
}

void SR_Update(SERIAL_REG_DATA *SregData) {
    /*
     boucle 1 a 16 
     * mask 0x01 et >>1 
     * 
     
     */
    //static bool usingSr=false;
    static uint16_t i=0;
    uint16_t cmd_led_save = SregData->cmd_leds;
    //usingSr=true;
    //guess issue 
    //SR_LED_DATAStateSet(0) all on 
    //SR_LED_DATAStateSet(1) all on exept LED9  
    //
    //outputs of 
    // TESTPINOn();//set off 
    //TESTPINOff();//set on 
    SR_LED_OE_2On();//set off 
    SR_LED_OE_1On();
    //data valid at first clk
    SR_LED_DATAStateSet((cmd_led_save & 0x01));   
    APP_WaitStart(1);
    for (i=0;i<16;i++)
    {
        
        
        //first clk shifting 
        SR_SRCLK_FKCDPOn();
        APP_WaitStart(1);
        //latch output is shift clk inverted 
        
        
        SR_SRCLK_FKCDPOff();
        
       
        SR_LED_CLKOn();
        //APP_WaitStart(1);
        
         
        APP_WaitStart(1);
        SR_LED_CLKOff();
        //setting valid data before next clking 
        //SregData->cmd_leds = 0x0000;
        APP_WaitStart(1);
        cmd_led_save =cmd_led_save>>1;
        SR_LED_DATAStateSet((cmd_led_save & 0x01));
      
        APP_WaitStart(1);
    }
    APP_WaitStart(1);
    
   
     cmd_led_save = SregData->cmd_leds ;
    
    SR_LED_OE_2Off();//set on
    SR_LED_OE_1Off();//set on
    //try to do a driver 
   
    
}

/* *****************************************************************************
 End of File
 */
