#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

// REturns the process ID of the calling processes, as determined from
// the /proc/self symlink

pid_t get_pid_from_proc_self ()
{
  char target[32];
  int pid;
  // read the target of the symbolic link
  readlink ("/proc/self", target, sizeof (target));
  // the target is a directory named for the process ID
  sscanf (target, "%d", &pid);
  return (pid_t) pid;
}

int main()
{
  printf ("/proc/self reports process id %d \n",
        (int) get_pid_from_proc_self ());
  printf ("getpid() reports process id %d\n", (int) getpid ());

  return 0;
}
