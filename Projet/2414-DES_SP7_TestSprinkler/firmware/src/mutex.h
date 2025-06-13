#ifndef MUTEX_H
#define MUTEX_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @struct MUTEX_t
 * @brief Structure représentant un mutex simple (verrou).
 *
 * Le champ 'locked' indique si le mutex est pris (1) ou libre (0).
 */
// Structure du mutex (simple flag 
typedef struct {
    volatile uint8_t locked;
} MUTEX_t;

/**
 * @brief Initialise le mutex (à l'état déverrouillé).
 *
 * @param mutex Pointeur vers la structure du mutex à initialiser.
 * @return void
 */
// Initialise le mutex (à l'état déverrouillé)
void MUTEX_Init(MUTEX_t *mutex);

/**
 * @brief Prend le mutex (bloquant).
 *
 * Bloque jusqu'à ce que le mutex soit disponible, puis le verrouille.
 *
 * @param mutex Pointeur vers la structure du mutex à verrouiller.
 * @return void
 */
// Prend le mutex (bloquant)
void MUTEX_Lock(MUTEX_t *mutex);

/**
 * @brief Relâche le mutex.
 *
 * Libère le verrou du mutex.
 *
 * @param mutex Pointeur vers la structure du mutex à déverrouiller.
 * @return void
 */
// Relâche le mutex
void MUTEX_Unlock(MUTEX_t *mutex);

/**
 * @brief Essaie de prendre le mutex (non bloquant).
 *
 * @param mutex Pointeur vers la structure du mutex à verrouiller.
 * @return true si le verrou a été acquis, false sinon.
 */
// Essaie de prendre le mutex (non bloquant)
bool MUTEX_TryLock(MUTEX_t *mutex);

#endif // MUTEX_H
