static int juggle(curl_socket_t *sockfdp,
                  curl_socket_t listenfd,
                  enum sockmode *mode)
{
  struct timeval timeout;
  fd_set fds_read;
  fd_set fds_write;
  fd_set fds_err;
  curl_socket_t maxfd;
  int r;
  unsigned char buffer[256]; /* FIX: bigger buffer */
  char data[256];
  int sockfd;

  timeout.tv_sec = 120;
  timeout.tv_usec = 0;

  FD_ZERO(&fds_read);
  FD_ZERO(&fds_write);
  FD_ZERO(&fds_err);

  FD_SET(fileno(stdin), &fds_read);

  switch(*mode) {
  case PASSIVE_LISTEN:
    /* server mode */
    sockfd = listenfd;
    /* there's always a socket to wait for */
    FD_SET(sockfd, &fds_read);
    maxfd = sockfd;
    break;

  case PASSIVE_CONNECT:
    sockfd = *sockfdp;
    if(-1 == sockfd) {
      /* eeek, we are supposedly connected and then this cannot be -1 ! */
      logmsg("socket is -1! on %s:%d", __FILE__, __LINE__);
      maxfd = 0; /* stdin */
    }
    else {
      /* there's always a socket to wait for */
      FD_SET(sockfd, &fds_read);
      maxfd = sockfd;
    }
    break;

  case ACTIVE:
    sockfd = *sockfdp;

    /* sockfd turns CURL_SOCKET_BAD when our connection has been closed */
    if(sockfd != CURL_SOCKET_BAD) {
      FD_SET(sockfd, &fds_read);
      maxfd = sockfd;
    }
    else {
      logmsg("No socket to read on");
      maxfd = 0;
    }
    break;

  case ACTIVE_DISCONNECT:
    logmsg("disconnected, no socket to read on");
    maxfd = 0;
    sockfd = CURL_SOCKET_BAD;
    break;
  }

  do {
    r = select(maxfd + 1, &fds_read, &fds_write, &fds_err, &timeout);
  } while((r == -1) && (ourerrno() == EINTR));

  switch(r) {
  case -1:
    return FALSE;

  case 0: /* timeout! */
    return TRUE;
  }


  if(FD_ISSET(fileno(stdin), &fds_read)) {
    size_t nread;
    /* read from stdin, commands/data to be dealt with and possibly passed on
       to the socket

       protocol:

       4 letter command + LF [mandatory]

       4-digit hexadecimal data length + LF [if the command takes data]
       data                       [the data being as long as set above]

       Commands:

       DATA - plain pass-thru data
    */
    nread = read(fileno(stdin), buffer, 5);
    if(5 == nread) {

      logmsg("Received %c%c%c%c (on stdin)",
             buffer[0], buffer[1], buffer[2], buffer[3] );

      if(!memcmp("PING", buffer, 4)) {
        /* send reply on stdout, just proving we are alive */
        write(fileno(stdout), "PONG\n", 5);
      }

      else if(!memcmp("PORT", buffer, 4)) {
        /* question asking us what PORT number we are listening to.
           Replies with PORT with "IPv[num]/[port]" */
        sprintf((char *)buffer, "IPv%d/%d\n", use_ipv6?6:4, port);
        r = (int)strlen((char *)buffer);
        sprintf(data, "PORT\n%04x\n", r);
        write(fileno(stdout), data, 10);
        write(fileno(stdout), buffer, r);
      }
      else if(!memcmp("QUIT", buffer, 4)) {
        /* just die */
        logmsg("quits");
        return FALSE;
      }
      else if(!memcmp("DATA", buffer, 4)) {
        /* data IN => data OUT */
        long len;

        if(5 != read(fileno(stdin), buffer, 5))
          return FALSE;

        len = strtol((char *)buffer, NULL, 16);
        if(len != read(fileno(stdin), buffer, len))
          return FALSE;

        logmsg("> %d bytes data, server => client", len);
        lograw(buffer, (int)len);

        if(*mode == PASSIVE_LISTEN) {
          logmsg("*** We are disconnected!");
          write(fileno(stdout), "DISC\n", 5);
        }
        else
          /* send away on the socket */
          swrite(sockfd, buffer, len);
      }
      else if(!memcmp("DISC", buffer, 4)) {
        /* disconnect! */
        write(fileno(stdout), "DISC\n", 5);
        if(sockfd != CURL_SOCKET_BAD) {
          logmsg("====> Client forcibly disconnected");
          sclose(sockfd);
          *sockfdp = CURL_SOCKET_BAD;
          if(*mode == PASSIVE_CONNECT)
            *mode = PASSIVE_LISTEN;
          else
            *mode = ACTIVE_DISCONNECT;
        }
        else
          logmsg("attempt to close already dead connection");
        return TRUE;
      }
    }
    else {
      logmsg("read %d from stdin, exiting", (int)nread);
      return FALSE;
    }
  }

  if((sockfd != CURL_SOCKET_BAD) && (FD_ISSET(sockfd, &fds_read)) ) {

    if(*mode == PASSIVE_LISTEN) {
      /* there's no stream set up yet, this is an indication that there's a
         client connecting. */
      sockfd = accept(sockfd, NULL, NULL);
      if(-1 == sockfd)
        logmsg("accept() failed\n");
      else {
        logmsg("====> Client connect");
        write(fileno(stdout), "CNCT\n", 5);
        *sockfdp = sockfd; /* store the new socket */
        *mode = PASSIVE_CONNECT; /* we have connected */
      }
      return TRUE;
    }

    /* read from socket, pass on data to stdout */
    r = sread(sockfd, buffer, sizeof(buffer));

    if(r <= 0) {
      logmsg("====> Client disconnect");
      write(fileno(stdout), "DISC\n", 5);
      sclose(sockfd);
      *sockfdp = CURL_SOCKET_BAD;
      if(*mode == PASSIVE_CONNECT)
        *mode = PASSIVE_LISTEN;
      else
        *mode = ACTIVE_DISCONNECT;
      return TRUE;
    }

    sprintf(data, "DATA\n%04x\n", r);
    write(fileno(stdout), data, 10);
    write(fileno(stdout), buffer, r);

    logmsg("< %d bytes data, client => server", r);
    lograw(buffer, r);
  }

  return TRUE;
}