static bool juggle(curl_socket_t *sockfdp,
                   curl_socket_t listenfd,
                   enum sockmode *mode)
{
  struct timeval timeout;
  fd_set fds_read;
  fd_set fds_write;
  fd_set fds_err;
  curl_socket_t sockfd = CURL_SOCKET_BAD;
  int maxfd = -99;
  ssize_t rc;
  ssize_t nread_socket;
  ssize_t bytes_written;
  ssize_t buffer_len;
  int error = 0;

 /* 'buffer' is this excessively large only to be able to support things like
    test 1003 which tests exceedingly large server response lines */
  unsigned char buffer[17010];
  char data[16];

  if(got_exit_signal) {
    logmsg("signalled to die, exiting...");
    return FALSE;
  }

#ifdef HAVE_GETPPID
  /* As a last resort, quit if sockfilt process becomes orphan. Just in case
     parent ftpserver process has died without killing its sockfilt children */
  if(getppid() <= 1) {
    logmsg("process becomes orphan, exiting");
    return FALSE;
  }
#endif

  timeout.tv_sec = 120;
  timeout.tv_usec = 0;

  FD_ZERO(&fds_read);
  FD_ZERO(&fds_write);
  FD_ZERO(&fds_err);

  FD_SET((curl_socket_t)fileno(stdin), &fds_read);

  switch(*mode) {

  case PASSIVE_LISTEN:

    /* server mode */
    sockfd = listenfd;
    /* there's always a socket to wait for */
    FD_SET(sockfd, &fds_read);
    maxfd = (int)sockfd;
    break;

  case PASSIVE_CONNECT:

    sockfd = *sockfdp;
    if(CURL_SOCKET_BAD == sockfd) {
      /* eeek, we are supposedly connected and then this cannot be -1 ! */
      logmsg("socket is -1! on %s:%d", __FILE__, __LINE__);
      maxfd = 0; /* stdin */
    }
    else {
      /* there's always a socket to wait for */
      FD_SET(sockfd, &fds_read);
#ifdef USE_WINSOCK
      FD_SET(sockfd, &fds_err);
#endif
      maxfd = (int)sockfd;
    }
    break;

  case ACTIVE:

    sockfd = *sockfdp;
    /* sockfd turns CURL_SOCKET_BAD when our connection has been closed */
    if(CURL_SOCKET_BAD != sockfd) {
      FD_SET(sockfd, &fds_read);
#ifdef USE_WINSOCK
      FD_SET(sockfd, &fds_err);
#endif
      maxfd = (int)sockfd;
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

  } /* switch(*mode) */


  do {

    /* select() blocking behavior call on blocking descriptors please */

    rc = select(maxfd + 1, &fds_read, &fds_write, &fds_err, &timeout);

    if(got_exit_signal) {
      logmsg("signalled to die, exiting...");
      return FALSE;
    }

  } while((rc == -1) && ((error = errno) == EINTR));

  if(rc < 0) {
    logmsg("select() failed with error: (%d) %s",
           error, strerror(error));
    return FALSE;
  }

  if(rc == 0)
    /* timeout */
    return TRUE;


  if(FD_ISSET(fileno(stdin), &fds_read)) {
    /* read from stdin, commands/data to be dealt with and possibly passed on
       to the socket

       protocol:

       4 letter command + LF [mandatory]

       4-digit hexadecimal data length + LF [if the command takes data]
       data                       [the data being as long as set above]

       Commands:

       DATA - plain pass-thru data
    */

    if(!read_stdin(buffer, 5))
      return FALSE;

    logmsg("Received %c%c%c%c (on stdin)",
           buffer[0], buffer[1], buffer[2], buffer[3] );

    if(!memcmp("PING", buffer, 4)) {
      /* send reply on stdout, just proving we are alive */
      if(!write_stdout("PONG\n", 5))
        return FALSE;
    }

    else if(!memcmp("PORT", buffer, 4)) {
      /* Question asking us what PORT number we are listening to.
         Replies to PORT with "IPv[num]/[port]" */
      sprintf((char *)buffer, "%s/%hu\n", ipv_inuse, port);
      buffer_len = (ssize_t)strlen((char *)buffer);
      snprintf(data, sizeof(data), "PORT\n%04zx\n", buffer_len);
      if(!write_stdout(data, 10))
        return FALSE;
      if(!write_stdout(buffer, buffer_len))
        return FALSE;
    }
    else if(!memcmp("QUIT", buffer, 4)) {
      /* just die */
      logmsg("quits");
      return FALSE;
    }
    else if(!memcmp("DATA", buffer, 4)) {
      /* data IN => data OUT */

      if(!read_stdin(buffer, 5))
        return FALSE;

      buffer[5] = '\0';

      buffer_len = (ssize_t)strtol((char *)buffer, NULL, 16);
      if (buffer_len > (ssize_t)sizeof(buffer)) {
        logmsg("ERROR: Buffer size (%zu bytes) too small for data size "
               "(%zd bytes)", sizeof(buffer), buffer_len);
        return FALSE;
      }
      logmsg("> %zd bytes data, server => client", buffer_len);

      if(!read_stdin(buffer, buffer_len))
        return FALSE;

      lograw(buffer, buffer_len);

      if(*mode == PASSIVE_LISTEN) {
        logmsg("*** We are disconnected!");
        if(!write_stdout("DISC\n", 5))
          return FALSE;
      }
      else {
        /* send away on the socket */
        bytes_written = swrite(sockfd, buffer, buffer_len);
        if(bytes_written != buffer_len) {
          logmsg("Not all data was sent. Bytes to send: %zd sent: %zd",
                 buffer_len, bytes_written);
        }
      }
    }
    else if(!memcmp("DISC", buffer, 4)) {
      /* disconnect! */
      if(!write_stdout("DISC\n", 5))
        return FALSE;
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


  if((sockfd != CURL_SOCKET_BAD) && (FD_ISSET(sockfd, &fds_read)) ) {

    curl_socket_t newfd = CURL_SOCKET_BAD; /* newly accepted socket */

    if(*mode == PASSIVE_LISTEN) {
      /* there's no stream set up yet, this is an indication that there's a
         client connecting. */
      newfd = accept(sockfd, NULL, NULL);
      if(CURL_SOCKET_BAD == newfd) {
        error = SOCKERRNO;
        logmsg("accept(%d, NULL, NULL) failed with error: (%d) %s",
               sockfd, error, strerror(error));
      }
      else {
        logmsg("====> Client connect");
        if(!write_stdout("CNCT\n", 5))
          return FALSE;
        *sockfdp = newfd; /* store the new socket */
        *mode = PASSIVE_CONNECT; /* we have connected */
      }
      return TRUE;
    }

    /* read from socket, pass on data to stdout */
    nread_socket = sread(sockfd, buffer, sizeof(buffer));

    if(nread_socket > 0) {
      snprintf(data, sizeof(data), "DATA\n%04zx\n", nread_socket);
      if(!write_stdout(data, 10))
        return FALSE;
      if(!write_stdout(buffer, nread_socket))
        return FALSE;

      logmsg("< %zd bytes data, client => server", nread_socket);
      lograw(buffer, nread_socket);
    }

    if(nread_socket <= 0
#ifdef USE_WINSOCK
       || FD_ISSET(sockfd, &fds_err)
#endif
       ) {
      logmsg("====> Client disconnect");
      if(!write_stdout("DISC\n", 5))
        return FALSE;
      sclose(sockfd);
      *sockfdp = CURL_SOCKET_BAD;
      if(*mode == PASSIVE_CONNECT)
        *mode = PASSIVE_LISTEN;
      else
        *mode = ACTIVE_DISCONNECT;
      return TRUE;
    }
  }

  return TRUE;
}