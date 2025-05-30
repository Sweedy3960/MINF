#include "mutex.h"

void MUTEX_Init(MUTEX_t *mutex) {
    mutex->locked = 0;
}

void MUTEX_Lock(MUTEX_t *mutex) {
    // Boucle jusqu'à ce que le mutex soit libre (section critique très courte)
    while (__sync_lock_test_and_set(&(mutex->locked), 1)) {
        // Attente active (peut être remplacée par yield ou sleep si RTOS)
    }
}

void MUTEX_Unlock(MUTEX_t *mutex) {
    __sync_lock_release(&(mutex->locked));
}

bool MUTEX_TryLock(MUTEX_t *mutex) {
    return (__sync_lock_test_and_set(&(mutex->locked), 1) == 0);
}
