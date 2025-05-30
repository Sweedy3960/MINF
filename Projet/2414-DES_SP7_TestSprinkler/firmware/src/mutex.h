#ifndef MUTEX_H
#define MUTEX_H

#include <stdint.h>
#include <stdbool.h>

// Structure du mutex (simple flag 
typedef struct {
    volatile uint8_t locked;
} MUTEX_t;

// Initialise le mutex (à l'état déverrouillé)
void MUTEX_Init(MUTEX_t *mutex);

// Prend le mutex (bloquant)
void MUTEX_Lock(MUTEX_t *mutex);

// Relâche le mutex
void MUTEX_Unlock(MUTEX_t *mutex);

// Essaie de prendre le mutex (non bloquant)
bool MUTEX_TryLock(MUTEX_t *mutex);

#endif // MUTEX_H
