// Initializing a Binary Semaphore

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>


// we must define union semun ourselves

union semun {
  int val;
  struct semid_ds *buf;
  unsigned short int *array;
  struct seminfo *__buf;
};

// Obtain a binary semaphore's ID, allocating if necessary

int binary_semaphore_allocation (key_t key, int sem_flags)
{
  return semget (key, 1, sem_flags);
}

// Deallocate a binary semaphore. All users must have finished their use.
// Return -1 on failure

int binary_semaphore_deallocate (int semid)
{
  union semun ignored_argument;
  return semctl (semid, 1, IPC_RMID, ignored_argument);
}

// Initialize a binary semaphore with a value of 1

int binary_semaphore_initialize (int semid)
{
  union semun argument;
  unsigned short values[1];
  values[0] = 1;
  argument.array = values;
  return semctl (semid, 0, SETALL, argument);
}
