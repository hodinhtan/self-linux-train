#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>

// Pirnt hthe contents of the home page for the server's socket
// return an indication of success

void get_home_page (int socket_fd)
{
  char buffer[10000];
  ssize_t number_characters_read;

  // Send the HTTP GET command for the home page
  sprintf (buffer, "GET /\n");
  write (socket_fd, buffer, strlen (buffer));
  // REad from the socket. the call to read may not 
  // return all the data at one, so keep trying until we run out
  while (1) {
    number_characters_read = read (socket_fd, buffer, 10000);
    if (number_characters_read == 0) 
      return;
    // write the data to standard output
    fwrite (buffer, sizeof (char), number_characters_read, stdout);
  }
}

int main (int argc, char* const argv[])
{
  int socket_fd;
  struct sockaddr_in name;
  struct hostent* hostinfo;

  // Create the socket
  socket_fd = socket (PF_INET, SOCK_STREAM, 0);
  // Store the server's name in the socket address
  name.sin_family = AF_INET;
  // Convert from strings to nubmers
  hostinfo = gethostbyname (argv[1]);
  if (hostinfo == NULL)
    return 1;
  else 
    name.sin_addr = *((struct in_addr *) hostinfo->h_addr);
  // web servers use port 80
  name.sin_port = htons (80);
  // connect to the web server 
  if (connect (socket_fd, &name, sizeof (struct sockaddr_in)) == -1) {
    perror ("connect");
    return 1;
  }
  // REtrieve the server's home page
  get_home_page (socket_fd);

  return 0;
}
