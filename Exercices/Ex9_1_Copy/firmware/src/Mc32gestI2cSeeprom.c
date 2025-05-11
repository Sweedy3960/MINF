//--------------------------------------------------------
// Mc32gestI2cEEprom.C
//--------------------------------------------------------
// Gestion I2C de la SEEPROM du MCP79411 (Solution exercice)
//	Description :	Fonctions pour EEPROM MCP79411
//
//	Auteur 		: 	C. HUBER
//      Date            :       26.05.2014
//	Version		:	V1.0
//	Compilateur	:	XC32 V1.31
// Modifications :
//
/*--------------------------------------------------------*/



#include "Mc32gestI2cSeeprom.h"
#include "Mc32_I2cUtilCCS.h"
#include "stdint.h"

// Définition pour MCP79411
#define MCP79411_EEPROM_R    0xAF         // MCP79411 address for read
#define MCP79411_EEPROM_W    0xAE         // MCP79411 address for write
// La EEPROM du 79411 est de 1 Kbits donc 128 octets
#define MCP79411_EEPROM_BEG   0x00         // addr. début EEPROM
#define MCP79411_EEPROM_END   0x7F         // addr. fin EEPROM
#define REG_EEUNLOCK          0x09          // registre eunlock
#define EEUNLOCK_VAL1           0x55
#define EEUNLOCK_VAL2           0xAA
// Definitions du bus (pour mesures)
// #define I2C-SCK  SCL2/RA2      PORTAbits.RA2   pin 58
// #define I2C-SDA  SDa2/RA3      PORTAbits.RA3   pin 59




// Initialisation de la communication I2C et du MCP79411
// ------------------------------------------------

void I2C_InitMCP79411(void)
{
   bool Fast = true;
   i2c_init( Fast );
} //end I2C_InitMCP79411

// Ecriture d'un bloc dans l'EEPROM du MCP79411 
void I2C_WriteSEEPROM(void *SrcData, uint32_t EEpromAddr, uint16_t NbBytes)
{
    uint8_t *pt_tb= (uint8_t*)&SrcData;
    uint8_t iter = 0;
    i2c_start();
    i2c_write(MCP79411_EEPROM_W);
    i2c_write(REG_EEUNLOCK);
    i2c_write(EEUNLOCK_VAL1);
    i2c_stop();
    i2c_start();
    i2c_write(MCP79411_EEPROM_W);
    i2c_write(REG_EEUNLOCK);
    i2c_write(EEUNLOCK_VAL2);
    i2c_stop();
    i2c_start();
    i2c_write(MCP79411_EEPROM_W);
    i2c_write(EEpromAddr);
    for(iter =0;iter<NbBytes;iter++)
    {
        i2c_write(pt_tb[iter]);
    }

} // end I2C_WriteSEEPROM

// Lecture d'un bloc dans l'EEPROM du MCP79411
void I2C_ReadSEEPROM(void *DstData, uint32_t EEpromAddr, uint16_t NbBytes)
{
    uint8_t iter = 0;
    uint8_t *pt_tb=(uint8_t*)&DstData;
 
    i2c_start();
    i2c_write(MCP79411_EEPROM_W);
    i2c_write(EEpromAddr);
    i2c_reStart();
    i2c_write(MCP79411_EEPROM_R);
    for(iter =0; iter<(NbBytes-1);iter ++)
    {
        pt_tb[iter] = i2c_read(1);
    }
    
    pt_tb[NbBytes-1] = i2c_read(0);//no ack 
    i2c_stop();
} // end I2C_ReadSEEPROM
   





 



