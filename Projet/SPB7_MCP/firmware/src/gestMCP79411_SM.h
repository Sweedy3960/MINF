/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.h

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

#ifndef GestI2CMC_SM_H
#define GestI2CMC_SM_H

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif
#include "Mc32_I2cUtil_SM.h"

    /* ************************************************************************** */
    /* ************************************************************************** */
    /* Section: Constants                                                         */
    /* ************************************************************************** */
    /* ************************************************************************** */

    /*  A brief description of a section can be given directly below the section
        banner.
     */


    /* ************************************************************************** */
    /** Descriptive Constant Name

      @Summary
        Brief one-line summary of the constant.
    
      @Description
        Full description, explaining the purpose and usage of the constant.
        <p>
        Additional description in consecutive paragraphs separated by HTML 
        paragraph breaks, as necessary.
        <p>
        Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.
    
      @Remarks
        Any additional remarks
     */
#define EXAMPLE_CONSTANT 0
#ifndef NULL_PTR
#define NULL_PTR ((void*)0)

#define MCP79411_BUFFER_MAX     256
#define MCP79411_REG_ADDR_LEN   1

#define MCP79411_DEC_MAX        0x99
#define MCP79411_DECADE         10
#define MCP79411_4BIT_SHIFT     4
#define MCP79411_HIGH_4BIT_MASK    0X0fu
    /**reg define**/
#define MCP79411_REG_RTCC_RTCSEC       0x00
#define MCP79411_REG_RTCC_RTCMIN       0x01
#define MCP79411_REG_RTCC_RTCHOUR      0x02
#define MCP79411_REG_RTCC_RTCWKDAY     0x03
#define MCP79411_REG_RTCC_RTCDATE      0x04
#define MCP79411_REG_RTCC_RTCMTH       0x05
#define MCP79411_REG_RTCC_RTCYEAR      0x06
#define MCP79411_REG_RTCC_CONTROL      0x07
#define MCP79411_REG_RTCC_OSCTRIM      0x08
#define MCP79411_REG_RTCC_EEUNLOCK     0x09
#define MCP79411_REG_RTCC_ALM0SEC      0x0A
#define MCP79411_REG_RTCC_ALM0MIN      0x0B
#define MCP79411_REG_RTCC_ALM0HOUR     0x0C
#define MCP79411_REG_RTCC_ALM0WKDAY    0x0D
#define MCP79411_REG_RTCC_ALM0DATE     0x0E
#define MCP79411_REG_RTCC_ALM0MTH      0x0F
#define MCP79411_REG_RTCC_ALM1SEC      0x11
#define MCP79411_REG_RTCC_ALM1MIN      0x12
#define MCP79411_REG_RTCC_ALM1HOUR     0x13
#define MCP79411_REG_RTCC_ALM1WKDAY    0x14
#define MCP79411_REG_RTCC_ALM1DATE     0x15
#define MCP79411_REG_RTCC_ALM1MTH      0x16
#define MCP79411_REG_RTCC_PWRDNMIN     0x18
#define MCP79411_REG_RTCC_PWRDNHOUR    0x19
#define MCP79411_REG_RTCC_PWRDNDATE    0x1A
#define MCP79411_REG_RTCC_PWRDNMTH     0x1B
#define MCP79411_REG_RTCC_PWRUPMIN     0x1C
#define MCP79411_REG_RTCC_PWRUPHOUR    0x1D
#define MCP79411_REG_RTCC_PWRUPDATE    0x1E
#define MCP79411_REG_RTCC_PWRUPMTH     0x1F
#define MCP79411_I2C_ADDR_W  0xDE
#define MCP79411_I2C_ADDR_R  0xDF

    typedef union {

        struct {
            char SQWFS : 2;
            char CRSTRIM : 1;
            char EXTOSC : 1;
            char ALM0EN : 1;
            char ALM1EN : 1;
            char SQWEN : 1;
            char OUT : 1;
        } bits;
        unsigned char ctrl_byte;
    } mcp79411_CONTROL;

    typedef union {

        struct {
            char TRIMVA : 7;
            char SIGN : 1;
        } bits;
        unsigned char osctrim_byte;
    } mcp79411_OSCTRIM;

    typedef union {

        struct {

            struct {
                char SEC : 7;
                char ST : 1;
            } RTCSEC_bits;

            struct {
                char MIN : 7;
                char RES : 1;
            } RTCMIN_bits;

            struct {
                char HOUR : 5;
                char AM_PM : 1;
                char b12_24 : 1;
                char RES : 1;
            } RTCHOUR_bits;

            struct {
                char WKDAY : 3;
                char VBATEN : 1;
                char PWRFAIL : 1;
                char OSCRUN : 1;
                char RES : 2;
            } RTCWKDAY_bits;

            struct {
                char DATE : 6;
                char RES : 2;
            } RTCDATE_bits;

            struct {
                char MTH : 5;
                char LPYR : 1;
                char RES : 2;
            } RTCMTH_bits;

            struct {
                char YEAR : 8;
            } RTCYEAR_bits;
        } regs;
        unsigned char time_bytes[7];
    } mcp79411_TIME_KEEPING;

    typedef union {

        struct {

            struct {
                char SEC : 7;
                char RES : 1;
            } ALMXSEC_bits;

            struct {
                char MIN : 7;
                char RES : 1;
            } ALMXMIN_bits;

            struct {
                char HOUR : 5;
                char AM_PM : 1;
                char b12_24 : 1;
                char RES : 1;
            } ALMXHOUR_bits;

            struct {
                char WKDAY : 3;
                char ALMXIF : 1;
                char ALMXMSK : 3;
                char ALMPOL : 1;
            } ALMXWKDAY_bits;

            struct {
                char DATE;
            } ALMXDATE_bits;

            struct {
                char MTH : 5;
                char RES : 3;
            } ALMXMTH_bits;
        } regs;
        unsigned char bytes[6];
    } mcp79411_ALARMS;
    // enumeration  Etat principal

    typedef enum {
        MCP_SM_Idle, MCP_SM_Busy, MCP_SM_ready
    } E_MCP_state;
typedef struct {
    char sec;
    char min;
    char hour;
    char wkday;
    char date;
    char mth;
    char year;
}mcp79411_time;

typedef struct{
    char sec;
    char min;
    char hour;
    char wkday;
    char date;
    char mth;    
}mcp79411_alarm;

    typedef struct {

        struct {
            unsigned char tx_buffer[MCP79411_BUFFER_MAX];
            unsigned char rx_buffer[MCP79411_BUFFER_MAX];
        } buffers;
    } mcp79411_obj;


    // enumeration  Etapes de la séquence

    typedef enum {
        MCP_I2CSEQ_Idle,
        MCP_I2CSEQ_Start,
        MCP_I2CSEQ_WriteAddrW,
        MCP_I2CSEQ_WriteReg,
        MCP_I2CSEQ_ReStart,
        MCP_I2CSEQ_WriteAddrR,
        MCP_I2CSEQ_ReadnByte,
        MCP_I2CSEQ_Stop,
    } E_MCP_Sequence;
    // Descripteur MCP pour traitement par machine d'état

    typedef struct {
        // I2C_MODULE i2cModuleId;         // Id du Module I2C
        E_MCP_state Mcpstate; // Etat principal
        E_MCP_Sequence McpSequence; // Etapes de la séquence
        S_Descr_I2C_SM I2cSmInfo; // Descripteur pour fonction I2C_SM
        mcp79411_obj  mcp79411;

    } S_Descr_MCP_SM;
    
    extern S_Descr_MCP_SM DescrMCP;     // descripteur MCP
    
    
void McpSmInit(bool Fast);

// prototypes des fonctions
void I2C_MCP_SM_Init(S_Descr_MCP_SM *pDescr, bool Fast);
void I2C_MCP_SM_Execute(S_Descr_MCP_SM *pDescr);
void I2C_MCP_SM_Restart(S_Descr_MCP_SM *pDescr);
bool I2C_MCP_SM_IsReady(S_Descr_MCP_SM *pDescr);


    
    // *****************************************************************************
    // *****************************************************************************
    // Section: Data Types
    // *****************************************************************************
    // *****************************************************************************

    /*  A brief description of a section can be given directly below the section
        banner.
     */


    // *****************************************************************************

    /** Descriptive Data Type Name

      @Summary
        Brief one-line summary of the data type.
    
      @Description
        Full description, explaining the purpose and usage of the data type.
        <p>
        Additional description in consecutive paragraphs separated by HTML 
        paragraph breaks, as necessary.
        <p>
        Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.

      @Remarks
        Any additional remarks
        <p>
        Describe enumeration elements and structure and union members above each 
        element or member.
     */
    typedef struct _example_struct_t {
        /* Describe structure member. */
        int some_number;

        /* Describe structure member. */
        bool some_flag;

    } example_struct_t;


    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    // *****************************************************************************

    /*  A brief description of a section can be given directly below the section
        banner.
     */

    // *****************************************************************************
    /**
      @Function
        int ExampleFunctionName ( int param1, int param2 ) 

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
    int ExampleFunction(int param1, int param2);


    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif 
#endif 
/* ****#define GestI2CMC_SM_H**********************************
 End of File
 */
