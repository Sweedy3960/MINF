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

/**
 * @struct S_ADCResults
 * @brief Structure contenant les résultats de conversion de tous les canaux ADC.
 *
 * Chaque champ ChanX correspond à la valeur convertie du canal analogique X.
 *
 * @var S_ADCResults::Chan0
 * Valeur convertie du canal analogique 0
 * @var S_ADCResults::Chan1
 * Valeur convertie du canal analogique 1
 * @var S_ADCResults::Chan2
 * Valeur convertie du canal analogique 2
 * @var S_ADCResults::Chan3
 * Valeur convertie du canal analogique 3
 * @var S_ADCResults::Chan4
 * Valeur convertie du canal analogique 4
 * @var S_ADCResults::Chan5
 * Valeur convertie du canal analogique 5
 * @var S_ADCResults::Chan6
 * Valeur convertie du canal analogique 6
 * @var S_ADCResults::Chan7
 * Valeur convertie du canal analogique 7
 * @var S_ADCResults::Chan8
 * Valeur convertie du canal analogique 8
 * @var S_ADCResults::Chan9
 * Valeur convertie du canal analogique 9
 * @var S_ADCResults::Chan10
 * Valeur convertie du canal analogique 10
 * @var S_ADCResults::Chan11
 * Valeur convertie du canal analogique 11
 * @var S_ADCResults::Chan12
 * Valeur convertie du canal analogique 12
 * @var S_ADCResults::Chan13
 * Valeur convertie du canal analogique 13
 * @var S_ADCResults::Chan14
 * Valeur convertie du canal analogique 14
 */
typedef struct {
    uint16_t Chan0;   /**< Valeur convertie du canal analogique 0 */
    uint16_t Chan1;   /**< Valeur convertie du canal analogique 1 */
    uint16_t Chan2;   /**< Valeur convertie du canal analogique 2 */
    uint16_t Chan3;   /**< Valeur convertie du canal analogique 3 */
    uint16_t Chan4;   /**< Valeur convertie du canal analogique 4 */
    uint16_t Chan5;   /**< Valeur convertie du canal analogique 5 */
    uint16_t Chan6;   /**< Valeur convertie du canal analogique 6 */
    uint16_t Chan7;   /**< Valeur convertie du canal analogique 7 */
    uint16_t Chan8;   /**< Valeur convertie du canal analogique 8 */
    uint16_t Chan9;   /**< Valeur convertie du canal analogique 9 */
    uint16_t Chan10;  /**< Valeur convertie du canal analogique 10 */
    uint16_t Chan11;  /**< Valeur convertie du canal analogique 11 */
    uint16_t Chan12;  /**< Valeur convertie du canal analogique 12 */
    uint16_t Chan13;  /**< Valeur convertie du canal analogique 13 */
    uint16_t Chan14;  /**< Valeur convertie du canal analogique 14 */
  
       
} S_ADCResults ;

/*--------------------------------------------------------*/
// Fonction BSP_InitADC10
/*--------------------------------------------------------*/
/**
 * @brief Initialise le driver ADC.
 *
 * Cette fonction configure et initialise le module ADC pour la lecture des canaux analogiques.
 *
 * @return void
 */
void BSP_InitADC10(void);

/**
 * @brief Ouvre le driver ADC.
 *
 * Cette fonction prépare le module ADC pour la lecture des échantillons.
 *
 * @return void
 */
void DRV_ADC_Open(void);

/**
 * @brief Démarre la conversion ADC.
 *
 * Cette fonction lance la conversion analogique-numérique sur les canaux configurés.
 *
 * @return void
 */
void DRV_ADC_Start(void);

/**
 * @brief Vérifie si des échantillons ADC sont disponibles.
 *
 * @return uint8_t 1 si des échantillons sont prêts, 0 sinon.
 */
uint8_t DRV_ADC_SamplesAvailable(void);

/**
 * @brief Lit la valeur d'un canal ADC.
 *
 * @param channel Numéro du canal à lire.
 * @return uint16_t Valeur convertie du canal ADC.
 */
uint16_t DRV_ADC_SamplesRead(uint8_t channel);

/**
 * @brief Lit toutes les valeurs des canaux ADC.
 *
 * Cette fonction lit les valeurs converties de tous les canaux ADC configurés.
 *
 * @return S_ADCResults Structure contenant les valeurs de tous les canaux ADC.
 */
S_ADCResults BSP_ReadAllADC();

#endif
