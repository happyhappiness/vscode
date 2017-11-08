CURLcode Curl_telnet(struct connectdata *conn, bool *done)
{
  CURLcode code;
  struct SessionHandle *data = conn->data;
  curl_socket_t sockfd = conn->sock[FIRSTSOCKET];
#ifdef WIN32
  HMODULE wsock2;
  WSOCK2_FUNC close_event_func;
  WSOCK2_FUNC create_event_func;
  WSOCK2_FUNC event_select_func;
  WSOCK2_FUNC enum_netevents_func;
  WSAEVENT event_handle;
  WSANETWORKEVENTS events;
  HANDLE stdin_handle;
  HANDLE objs[2];
  DWORD  obj_count;
  DWORD  wait_timeout;
  DWORD waitret;
  DWORD readfile_read;
#else
  int interval_ms;
  struct pollfd pfd[2];
#endif
  ssize_t nread;
  bool keepon = TRUE;
  char *buf = data->state.buffer;
  struct TELNET *tn;

  *done = TRUE; /* uncontionally */

  code = init_telnet(conn);
  if(code)
    return code;

  tn = (struct TELNET *)conn->proto.telnet;

  code = check_telnet_options(conn);
  if(code)
    return code;

#ifdef WIN32
  /*
  ** This functionality only works with WinSock >= 2.0.  So,
  ** make sure have it.
  */
  code = check_wsock2(data);
  if (code)
    return code;

  /* OK, so we have WinSock 2.0.  We need to dynamically */
  /* load ws2_32.dll and get the function pointers we need. */
  wsock2 = LoadLibrary("WS2_32.DLL");
  if (wsock2 == NULL) {
    failf(data,"failed to load WS2_32.DLL (%d)",GetLastError());
    return CURLE_FAILED_INIT;
  }

  /* Grab a pointer to WSACreateEvent */
  create_event_func = GetProcAddress(wsock2,"WSACreateEvent");
  if (create_event_func == NULL) {
    failf(data,"failed to find WSACreateEvent function (%d)",
          GetLastError());
    FreeLibrary(wsock2);
    return CURLE_FAILED_INIT;
  }

  /* And WSACloseEvent */
  close_event_func = GetProcAddress(wsock2,"WSACloseEvent");
  if (create_event_func == NULL) {
    failf(data,"failed to find WSACloseEvent function (%d)",
          GetLastError());
    FreeLibrary(wsock2);
    return CURLE_FAILED_INIT;
  }

  /* And WSAEventSelect */
  event_select_func = GetProcAddress(wsock2,"WSAEventSelect");
  if (event_select_func == NULL) {
    failf(data,"failed to find WSAEventSelect function (%d)",
          GetLastError());
    FreeLibrary(wsock2);
    return CURLE_FAILED_INIT;
  }

  /* And WSAEnumNetworkEvents */
  enum_netevents_func = GetProcAddress(wsock2,"WSAEnumNetworkEvents");
  if (enum_netevents_func == NULL) {
    failf(data,"failed to find WSAEnumNetworkEvents function (%d)",
          GetLastError());
    FreeLibrary(wsock2);
    return CURLE_FAILED_INIT;
  }

  /* We want to wait for both stdin and the socket. Since
  ** the select() function in winsock only works on sockets
  ** we have to use the WaitForMultipleObjects() call.
  */

  /* First, create a sockets event object */
  event_handle = (WSAEVENT)create_event_func();
  if (event_handle == WSA_INVALID_EVENT) {
    failf(data,"WSACreateEvent failed (%d)",WSAGetLastError());
    FreeLibrary(wsock2);
    return CURLE_FAILED_INIT;
  }

  /* The get the Windows file handle for stdin */
  stdin_handle = GetStdHandle(STD_INPUT_HANDLE);

  /* Create the list of objects to wait for */
  objs[0] = event_handle;
  objs[1] = stdin_handle;

  /* Tell winsock what events we want to listen to */
  if(event_select_func(sockfd, event_handle, FD_READ|FD_CLOSE) == SOCKET_ERROR) {
    close_event_func(event_handle);
    FreeLibrary(wsock2);
    return 0;
  }

  /* If stdin_handle is a pipe, use PeekNamedPipe() method to check it,
     else use the old WaitForMultipleObjects() way */
  if(GetFileType(stdin_handle) == FILE_TYPE_PIPE) {
    /* Don't wait for stdin_handle, just wait for event_handle */
    obj_count = 1;
    /* Check stdin_handle per 100 milliseconds */
    wait_timeout = 100;
  } else {
    obj_count = 2;
    wait_timeout = INFINITE;
  }

  /* Keep on listening and act on events */
  while(keepon) {
    waitret = WaitForMultipleObjects(obj_count, objs, FALSE, wait_timeout);
    switch(waitret) {
    case WAIT_TIMEOUT:
    {
      unsigned char outbuf[2];
      int out_count = 0;
      ssize_t bytes_written;
      char *buffer = buf;

      while(1) {
        if(!PeekNamedPipe(stdin_handle, NULL, 0, NULL, &readfile_read, NULL)) {
          keepon = FALSE;
          break;
        }
        nread = readfile_read;

        if(!nread)
          break;

        if(!ReadFile(stdin_handle, buf, sizeof(data->state.buffer),
                     &readfile_read, NULL)) {
          keepon = FALSE;
          break;
        }
        nread = readfile_read;

        while(nread--) {
          outbuf[0] = *buffer++;
          out_count = 1;
          if(outbuf[0] == CURL_IAC)
            outbuf[out_count++] = CURL_IAC;

          Curl_write(conn, conn->sock[FIRSTSOCKET], outbuf,
                     out_count, &bytes_written);
        }
      }
    }
    break;

    case WAIT_OBJECT_0 + 1:
    {
      unsigned char outbuf[2];
      int out_count = 0;
      ssize_t bytes_written;
      char *buffer = buf;

      if(!ReadFile(stdin_handle, buf, sizeof(data->state.buffer),
                   &readfile_read, NULL)) {
        keepon = FALSE;
        break;
      }
      nread = readfile_read;

      while(nread--) {
        outbuf[0] = *buffer++;
        out_count = 1;
        if(outbuf[0] == CURL_IAC)
          outbuf[out_count++] = CURL_IAC;

        Curl_write(conn, conn->sock[FIRSTSOCKET], outbuf,
                   out_count, &bytes_written);
      }
    }
    break;

    case WAIT_OBJECT_0:
      if(enum_netevents_func(sockfd, event_handle, &events)
         != SOCKET_ERROR) {
        if(events.lNetworkEvents & FD_READ) {
          /* This reallu OUGHT to check its return code. */
          (void)Curl_read(conn, sockfd, buf, BUFSIZE - 1, &nread);

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

        if(events.lNetworkEvents & FD_CLOSE) {
          keepon = FALSE;
        }
      }
      break;
    }
  }

  /* We called WSACreateEvent, so call WSACloseEvent */
  if (close_event_func(event_handle) == FALSE) {
    infof(data,"WSACloseEvent failed (%d)",WSAGetLastError());
  }

  /* "Forget" pointers into the library we're about to free */
  create_event_func = NULL;
  close_event_func = NULL;
  event_select_func = NULL;
  enum_netevents_func = NULL;

  /* We called LoadLibrary, so call FreeLibrary */
  if (!FreeLibrary(wsock2))
    infof(data,"FreeLibrary(wsock2) failed (%d)",GetLastError());
#else
  pfd[0].fd = sockfd;
  pfd[0].events = POLLIN;
  pfd[1].fd = 0;
  pfd[1].events = POLLIN;
  interval_ms = 1 * 1000;

  while (keepon) {
    switch (Curl_poll(pfd, 2, interval_ms)) {
    case -1:                    /* error, stop reading */
      keepon = FALSE;
      continue;
    case 0:                     /* timeout */
      break;
    default:                    /* read! */
      if(pfd[1].revents & POLLIN) { /* read from stdin */
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

          Curl_write(conn, conn->sock[FIRSTSOCKET], outbuf,
                     out_count, &bytes_written);
        }
      }

      if(pfd[0].revents & POLLIN) {
        /* This OUGHT to check the return code... */
        (void)Curl_read(conn, sockfd, buf, BUFSIZE - 1, &nread);

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