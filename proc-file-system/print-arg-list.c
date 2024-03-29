#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

// prints the argument list , one argument to a line, of the process given by PID
void print_process_arg_list (pid_t pid)
{
  int fd;
  char filename[24];
  char arg_list[1024];
  size_t length;
  char* next_arg;

  // generate the naem of the cmdline file for the process
  snprintf (filename, sizeof (filename), "/proc/%d/cmdline", (int) pid);
  // read the contents of the file
  fd = open (filename, O_RDONLY);
  length = read (fd, arg_list, sizeof (arg_list));
  close (fd);
  
  // read does not NUL-terminate the buffer, so do it here
  arg_list[length] = '\0';

  // Loop over arguments. arguments are separated by NULs
  next_arg = arg_list;
  while (next_arg < arg_list + length) {
  // Print the argument. Each is NUL-terminated, so just treat it like an ordinary string
    printf ("%s\n", next_arg);
    // advance to the next argument. since each argument is NUL-terminated, 
    // strlen counts the length of the next argument, not the entire argument list
    next_arg += strlen (next_arg) + 1;
  }
}

int main (int argc, char* argv[])
{
  pid_t pid = (pid_t) atoi (argv[1]);
  print_process_arg_list(pid);
  return 0;
}
