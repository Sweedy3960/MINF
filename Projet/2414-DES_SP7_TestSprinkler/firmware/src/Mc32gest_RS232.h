#ifndef Mc32Gest_RS232_H
#define Mc32Gest_RS232_H
/*--------------------------------------------------------*/
// Mc32Gest_RS232.h
/*--------------------------------------------------------*/
//	Description :	emission et reception sp�cialis�e
//			        pour TP2 2016-2017
//
//	Auteur 		: 	C. HUBER
//
//	Version		:	V1.3
//	Compilateur	:	XC32 V1.42 + Harmony 1.08
//
/*--------------------------------------------------------*/

#include <stdint.h>
#include "GesFifoTh32.h"


/*--------------------------------------------------------*/
// D�finition des fonctions prototypes
/*--------------------------------------------------------*/

// prototypes des fonctions
/**
 * @brief Initialise les FIFOs de communication série (réception et émission).
 *
 * Cette fonction initialise les descripteurs et les buffers des FIFOs utilisés pour la communication série.
 * Elle configure également la ligne RTS pour contrôler l'accès à l'émission.
 *
 * @return void
 */
void InitFifoComm(void);

/**
 * @brief Envoie un message via la FIFO d'émission série.
 *
 * Cette fonction place un message dans la FIFO d'émission si de la place est disponible,
 * puis gère le contrôle de flux matériel (CTS) pour déclencher l'interruption d'émission si nécessaire.
 *
 * @param pData Pointeur vers le tableau de données à envoyer.
 * @return void
 */
void SendMessage(int8_t *pData);
#define MAXMSGFAUX 10
// Descripteur des fifos
extern S_fifo descrFifoRX;
extern S_fifo descrFifoTX;

#endif
