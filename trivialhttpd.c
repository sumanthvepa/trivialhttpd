/*
 * trivialhttpd: A trivial web server
 *
 * Copyright (C) 2015 Sumanth Vepa.
 *
 * This file is part of trivialhttpd.
 *
 * trivialhttpd is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Pulic License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* Port number on which this server runs */
static const int PORT = 8004; 

/* Size of the listen backlog. Value taken from 
   Steven's example programs. */
static const int LISTENQ = 1024;

/* HTTP response as a format string for a printf statement. */
static const char *response = "HTTP/1.1 200 OK\nContent-Length: %d\n"
                            "Content-Type: text/html; charset=UTF-8\n"
                            "Connection: close\n\n%s";
static const char *content = "<html>"
                               "<head>"
                                 "<title>Celebrating 25 years of WWW</title>"
                               "</head>"
                               "<body>"
                                 "<h1>Celebrating 25 years of WWW</h1>"
                                 "<p>"
                                 "The world&pos;s first website was launched "
                                 "on December 20, 1990 at "
                                 "<a href=\"http://info.cern.ch/\">"
                                 "http://info.cern.ch</a>. This simple "
                                 "web server celebrates that event."
                                 "</p>"
                               "</body>"
                             "</html>\n";

static int nconsnl = 0;
static bool consecutive_newlines(
  const char *buffer, int bufsize)
{
  int n;
  for (n = 0; n < bufsize; ++n) {
    if (buffer[n] == '\r') continue;
    if (buffer[n] == '\n') {
      ++nconsnl;
    } else {
      nconsnl = 0;
    }
    if (nconsnl > 1) return true;
  }

  return false;
}

int main(int argc, const char *argv[])
{
  int n, listenfd, connfd;
  struct sockaddr_in servaddr;
  int out_buffer_len = strlen(response) + strlen(content) - 4 + 3;
  char in_buffer[1024];
  char *out_buffer = calloc(out_buffer_len+1, sizeof(char));

  /* Keep the response ready. So it can be sent as soon as a
     request is received. */
  snprintf(out_buffer, out_buffer_len+1, response, strlen(content), content);
  out_buffer_len = strlen(out_buffer);

  /* Listen for incomming connections */
  listenfd = socket(AF_INET, SOCK_STREAM, 0);

  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(PORT);


  bind(listenfd, (const struct sockaddr *)&servaddr, sizeof(servaddr));
  listen(listenfd, LISTENQ); 

  /* When a connection arrives, read the reques and send out the 
     response. This trivial server sends out the same response
     regardless of what the request is.
  */
  while(true) {
    connfd = accept(listenfd, 0, 0);
    while ((n = read(connfd, in_buffer, 1024)) > 0) {
      in_buffer[n] = 0;
      fprintf(stderr, "%s\n", in_buffer);
      if (consecutive_newlines(in_buffer, n)) break;
    }
    write(connfd, out_buffer, out_buffer_len);
    close(connfd);
  }

  free(out_buffer);
  return 0;
}
