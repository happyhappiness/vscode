CURLcode Curl_telnet(struct connectdata *conn)
{
  CURLcode code;
  struct SessionHandle *data = conn->data;
  int sockfd = conn->firstsocket;
#ifdef WIN32
  WSAEVENT event_handle;
  WSANETWORKEVENTS events;
  HANDLE stdin_handle;
  HANDLE objs[2];
  DWORD waitret;
#else
  fd_set readfd;
  fd_set keepfd;
#endif
  bool keepon = TRUE;
  char *buf = data->state.buffer;
  ssize_t nread;
  struct TELNET *tn;

  code = init_telnet(conn);
  if(code)
    return code;

  tn = (struct TELNET *)conn->proto.telnet;

  code = check_telnet_options(conn);
  if(code)
    return code;

#ifdef WIN32
  /* We want to wait for both stdin and the socket. Since
  ** the select() function in winsock only works on sockets
  ** we have to use the WaitForMultipleObjects() call.
  */

  /* First, create a sockets event object */
  event_handle = WSACreateEvent();

  /* The get the Windows file handle for stdin */
  stdin_handle = GetStdHandle(STD_INPUT_HANDLE);

  /* Create the list of objects to wait for */
  objs[0] = stdin_handle;
  objs[1] = event_handle;

  /* Tell winsock what events we want to listen to */
  if(WSAEventSelect(sockfd, event_handle, FD_READ|FD_CLOSE) == SOCKET_ERROR) {
    return 0;
  }

  /* Keep on listening and act on events */
  while(keepon) {
    waitret = WaitForMultipleObjects(2, objs, FALSE, INFINITE);
    switch(waitret - WAIT_OBJECT_0)
    {
      case 0:
      {
        unsigned char outbuf[2];
        int out_count = 0;
        ssize_t bytes_written;
        char *buffer = buf;
              
        if(!ReadFile(stdin_handle, buf, 255, (LPDWORD)&nread, NULL)) {
          keepon = FALSE;
          break;
        }
        
        while(nread--) {
          outbuf[0] = *buffer++;
          out_count = 1;
          if(outbuf[0] == CURL_IAC)
            outbuf[out_count++] = CURL_IAC;
          
          Curl_write(conn, conn->firstsocket, outbuf,
                     out_count, &bytes_written);
        }
      }
      break;
      
      case 1:
        if(WSAEnumNetworkEvents(sockfd, event_handle, &events)
           != SOCKET_ERROR)
        {
          if(events.lNetworkEvents & FD_READ)
          {
            /* This reallu OUGHT to check its return code. */
            Curl_read(conn, sockfd, buf, BUFSIZE - 1, &nread);
            
            telrcv(conn, (unsigned char *)buf, nread);
            
            fflush(stdout);
            
            /* Negotiate if the peer has started negotiating,
               otherwise don't. We don't want to speak telnet with
               non-telnet servers, like POP or SMTP. */
            if(tn->please_negotiate && !tn->already_negotiated) {
              negotiate(conn);
              tn->already_negotiated = 1;
            }
          }
          
          if(events.lNetworkEvents & FD_CLOSE)
          {
            keepon = FALSE;
          }
        }
        break;
    }
  }
#else
  FD_ZERO (&readfd);		/* clear it */
  FD_SET (sockfd, &readfd);
  FD_SET (0, &readfd);

  keepfd = readfd;

  while (keepon) {
    struct timeval interval;

    readfd = keepfd;		/* set this every lap in the loop */
    interval.tv_sec = 1;
    interval.tv_usec = 0;

    switch (select (sockfd + 1, &readfd, NULL, NULL, &interval)) {
    case -1:			/* error, stop reading */
      keepon = FALSE;
      continue;
    case 0:			/* timeout */
      break;
    default:			/* read! */
      if(FD_ISSET(0, &readfd)) { /* read from stdin */
        unsigned char outbuf[2];
        int out_count = 0;
        ssize_t bytes_written;
        char *buffer = buf;
        
        nread = read(0, buf, 255);

        while(nread--) {
          outbuf[0] = *buffer++;
          out_count = 1;
          if(outbuf[0] == CURL_IAC)
            outbuf[out_count++] = CURL_IAC;
      
          Curl_write(conn, conn->firstsocket, outbuf,
                     out_count, &bytes_written);
        }
      }

      if(FD_ISSET(sockfd, &readfd)) {
        /* This OUGHT to check the return code... */
        Curl_read(conn, sockfd, buf, BUFSIZE - 1, &nread);

        /* if we receive 0 or less here, the server closed the connection and
           we bail out from this! */
        if (nread <= 0) {
          keepon = FALSE;
          break;
        }

        telrcv(conn, (unsigned char *)buf, nread);

        /* Negotiate if the peer has started negotiating,
           otherwise don't. We don't want to speak telnet with
           non-telnet servers, like POP or SMTP. */
        if(tn->please_negotiate && !tn->already_negotiated) {
          negotiate(conn);
          tn->already_negotiated = 1;
        }
      }
    }
    if(data->set.timeout) {
      struct timeval now;           /* current time */
      now = Curl_tvnow();
      if(Curl_tvdiff(now, conn->created)/1000 >= data->set.timeout) {
        failf(data, "Time-out");
        code = CURLE_OPERATION_TIMEOUTED;
        keepon = FALSE;
      }
    }
  }
#endif
  /* mark this as "no further transfer wanted" */
  Curl_Transfer(conn, -1, -1, FALSE, NULL, -1, NULL);

  return code;
}