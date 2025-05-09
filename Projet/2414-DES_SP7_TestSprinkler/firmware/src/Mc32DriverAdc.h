#ifndef __MC32DRIVERADC_H
#define __MC32DRIVERADC_H
/*--------------------------------------------------------*/
//	Mc32DriverAdc.h
/*--------------------------------------------------------*/
//	Description :	Gestion ADC10 en mode scan
//
//
//	Auteur 		: 	C. Huber
//
//	Version		:	V1.0
//	Compilateur	:	XC32 V1.33 & Harmony V1.00
//
/*--------------------------------------------------------*/

// #include "bsp_config.h"
#include <stdint.h>

// Structure à adapter selon le nombre de canaux
// Limite à 8 avec les buffers alterné

typedef struct {
    uint16_t Chan0;
    uint16_t Chan1;
    uint16_t Chan2;
    uint16_t Chan3;
    uint16_t Chan4;
    uint16_t Chan5;
    uint16_t Chan6;
    uint16_t Chan7;
    uint16_t Chan8;
    uint16_t Chan9;
    uint16_t Chan10;
    uint16_t Chan11;
    uint16_t Chan12;
    uint16_t Chan13;
    uint16_t Chan14;
  
       
} S_ADCResults ;

/*--------------------------------------------------------*/
// Fonction BSP_InitADC10
/*--------------------------------------------------------*/
void BSP_InitADC10(void);

/*--------------------------------------------------------*/
// Fonction BSP_ReadAllADC()
/*--------------------------------------------------------*/
S_ADCResults BSP_ReadAllADC();

#endif
