#include "mutex.h"

/**
 * @brief Initialise le mutex.
 *
 * Place le mutex dans un état déverrouillé.
 *
 * @param mutex Pointeur vers la structure du mutex à initialiser.
 * @return void
 */
void MUTEX_Init(MUTEX_t *mutex) {
    mutex->locked = 0;
}

/**
 * @brief Verrouille le mutex (attente active).
 *
 * Bloque jusqu'à ce que le mutex soit disponible, puis le verrouille.
 *
 * @param mutex Pointeur vers la structure du mutex à verrouiller.
 * @return void
 */
void MUTEX_Lock(MUTEX_t *mutex) {
    // Boucle jusqu'à ce que le mutex soit libre (section critique très courte)
    while (__sync_lock_test_and_set(&(mutex->locked), 1)) {
        // Attente active (peut être remplacée par yield ou sleep si RTOS)
    }
}

/**
 * @brief Déverrouille le mutex.
 *
 * Libère le verrou du mutex.
 *
 * @param mutex Pointeur vers la structure du mutex à déverrouiller.
 * @return void
 */
void MUTEX_Unlock(MUTEX_t *mutex) {
    __sync_lock_release(&(mutex->locked));
}

/**
 * @brief Tente de verrouiller le mutex sans attendre.
 *
 * @param mutex Pointeur vers la structure du mutex à verrouiller.
 * @return true si le verrou a été acquis, false sinon.
 */
bool MUTEX_TryLock(MUTEX_t *mutex) {
    return (__sync_lock_test_and_set(&(mutex->locked), 1) == 0);
}
