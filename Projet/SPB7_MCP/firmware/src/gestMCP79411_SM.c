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

#include "gestMCP79411_SM.h"
#include "system_config/default/system_config.h"
/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */
#define USE_LED_MEASURE true
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
S_Descr_MCP_SM DescrMCP;





void McpSmInit(bool Fast)
{
    I2C_MCP_SM_Init(&DescrMCP, true);
}
void I2C_MCP_SM_Init(S_Descr_MCP_SM *pDescr, bool Fast)
{

   //pDescr->i2cModuleId = ModuleId;
   pDescr->Mcpstate = MCP_SM_Idle;
   pDescr->McpSequence =  MCP_I2CSEQ_Idle;
   
   
   
   I2C_SM_init(  Fast, &pDescr->I2cSmInfo );
}

void I2C_MCP_SM_Restart(S_Descr_MCP_SM *pDescr) {
   pDescr->Mcpstate = MCP_SM_Idle;
   pDescr->McpSequence =  MCP_I2CSEQ_Idle;
 
}
bool I2C_MCP_SM_IsReady(S_Descr_MCP_SM *pDescr) {
    bool answer = false;
    if (pDescr->Mcpstate == MCP_SM_ready ) {
        answer = true;
    }
    return answer;
}


// Execution de la lecture du registre de température du LM92
// Prévu pour appel cyclique
void I2C_MCP_SM_Execute(S_Descr_MCP_SM *pDescr)
{
    //Déclaration des variables
    int16_t byte;
    bool AckBit;
    static uint8_t cntTx=0;
    static uint8_t cntRx=0;
    
    switch ( pDescr->Mcpstate )  {
        case  MCP_SM_Idle :
            // Passe à Busy
            pDescr->Mcpstate = MCP_SM_Busy;
            pDescr->McpSequence = MCP_I2CSEQ_Start;
            #ifdef USE_LED_MEASURE
                LIFELED_GREENToggle();   // Marque début séquence active
            #endif
        break;

        case  MCP_SM_Busy :
            // Effectue la lecture par étapes
            switch (pDescr->McpSequence)  {
                case MCP_I2CSEQ_Start :
                    // i2c_start();
                    I2C_SM_start( &pDescr->I2cSmInfo);
                    if (I2C_SM_isReady (&pDescr->I2cSmInfo)){
                        pDescr->McpSequence = MCP_I2CSEQ_WriteAddrW;
                        I2C_SM_begin(&pDescr->I2cSmInfo); // redemare la SM
                        #ifdef USE_LED_MEASURE
                            LIFELED_GREENToggle();
                        #endif
                    }
                break;
               
                case MCP_I2CSEQ_WriteAddrW :
                    //  i2c_write(lm92_wr);	 adresse + écriture
                    I2C_SM_write( &pDescr->I2cSmInfo, MCP79411_I2C_ADDR_W, &AckBit);
                    if (I2C_SM_isReady (&pDescr->I2cSmInfo)){
                        pDescr->McpSequence = MCP_I2CSEQ_WriteReg;
                        I2C_SM_begin(&pDescr->I2cSmInfo); // redemare la SM
                        #ifdef USE_LED_MEASURE
                            LIFELED_GREENToggle();
                        #endif
                    }
                break;

                case MCP_I2CSEQ_WriteReg :
                    I2C_SM_write( &pDescr->I2cSmInfo, pDescr->mcp79411.buffers.tx_buffer[0], &AckBit);
                    if (I2C_SM_isReady (&pDescr->I2cSmInfo)){
                        pDescr->McpSequence = MCP_I2CSEQ_ReStart;
                        I2C_SM_begin(&pDescr->I2cSmInfo); // redemare la SM
                        #ifdef USE_LED_MEASURE
                           LIFELED_GREENToggle();
                        #endif
                    }
                break;

                case MCP_I2CSEQ_ReStart :
                    // i2c_reStart();
                    I2C_SM_reStart( &pDescr->I2cSmInfo);
                    if (I2C_SM_isReady (&pDescr->I2cSmInfo)){
                        pDescr->McpSequence = MCP_I2CSEQ_WriteAddrR;
                        I2C_SM_begin(&pDescr->I2cSmInfo); // redemare la SM
                        #ifdef USE_LED_MEASURE
                            LIFELED_GREENToggle();
                        #endif
                    }
                break;
                case MCP_I2CSEQ_WriteAddrR :
                    //  i2c_write(lm92_rd);	 adresse + lecture
                    I2C_SM_write( &pDescr->I2cSmInfo, MCP79411_I2C_ADDR_R, &AckBit);
                    if (I2C_SM_isReady (&pDescr->I2cSmInfo)){
                        pDescr->McpSequence = MCP_I2CSEQ_ReadnByte;
                        I2C_SM_begin(&pDescr->I2cSmInfo); // redemare la SM
                        #ifdef USE_LED_MEASURE
                           LIFELED_GREENToggle();
                        #endif
                    }
                break;
                
                case MCP_I2CSEQ_ReadnByte :
                    //  msb = i2c_read(1); 	// ack
                    I2C_SM_read( &pDescr->I2cSmInfo, true, &pDescr->mcp79411.buffers.rx_buffer[0]);
                    if (I2C_SM_isReady (&pDescr->I2cSmInfo)){
                        pDescr->McpSequence = MCP_I2CSEQ_Stop;
                        I2C_SM_begin(&pDescr->I2cSmInfo); // redémarre la SM
                        #ifdef USE_LED_MEASURE
                           LIFELED_GREENToggle();
                        #endif
                    }
                break;

               

                case MCP_I2CSEQ_Stop :
                    // i2c_stop();
                    I2C_SM_stop(&pDescr->I2cSmInfo);
                    if (I2C_SM_isReady (&pDescr->I2cSmInfo)){
                        // Effectue les calculs
                        
                        pDescr->McpSequence = MCP_I2CSEQ_Idle;
                        I2C_SM_begin(&pDescr->I2cSmInfo); // redemare la SM
                        pDescr->Mcpstate = MCP_SM_ready;
                        #ifdef USE_LED_MEASURE
                            LIFELED_GREENToggle(); // marque fin séquence
                        #endif
                    }
                break;
                 
                case MCP_I2CSEQ_Idle :
                    // ajout pour eviter Warning
                break;
            }
        break;

        case  MCP_SM_ready :
            // Les résultats sont disponibles
            // Attente du Restart de l'utilisateur
            // après lecture des résultats
        break;
    }
       
} // end I2C_LM92_SM_Execute
   

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
static int ExampleLocalFunction(int param1, int param2) {
    return 0;
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
int ExampleInterfaceFunction(int param1, int param2) {
    return 0;
}


/* *****************************************************************************
 End of File
 */
