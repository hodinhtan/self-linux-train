#include <malloc.h>
#include <pthread.h>
#include <stdio.h>

// the Key used to associate a log file pointer with each thread
static pthread_key_t thread_log_key;

// write MESSAGE  to the log file for the current thread

void write_to_thread_log ( const char* message )
{
  FILE* thread_log = (FILE*) pthread_getspecific (thread_log_key);
  fprintf (thread_log, "%s\n", message);
}

// Close the log file pointer THREAD_LOG

void close_thread_log (void* thread_log)
{
  fclose ((FILE*) thread_log);
}

void* thread_function (void* args)
{
  char thread_log_filename[20];
  FILE* thread_log;

  // Generate the filename for this thread's log file
  sprintf ( thread_log_filename, "thread %d.log", (int) pthread_self () );

  // Open the log file
  thread_log = fopen (thread_log_filename, "w");

  // Store the file pointer in thread-specific data under thread_log_key 
  pthread_setspecific (thread_log_key, thread_log);

  write_to_thread_log ( " Thread starting.");
  
  // Do work here ...
  return NULL;
}

int main ()
{
  int i;
  pthread_t threads[5];

  // create a key to asociate thread log file pointers in thread-specific data.
  // Use close_thread_log to clean up the file pointers.
  pthread_key_create (&thread_log_key, close_thread_log);
  // create thread to do work
  for (i=0;i<5;++i)
    pthread_create (&(threads[i]), NULL, thread_function, NULL);

  for (i=0;i<5;++i)
    pthread_join (threads[i] , NULL);

  return 0;
}

