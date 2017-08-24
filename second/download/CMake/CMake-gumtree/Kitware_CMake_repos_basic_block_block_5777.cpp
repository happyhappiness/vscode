{
  CURLcode result;
  struct Curl_easy *data = conn->data;
  curl_socket_t sockfd = conn->sock[FIRSTSOCKET];
#ifdef USE_WINSOCK
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
  int err;
#else
  int interval_ms;
  struct pollfd pfd[2];
  int poll_cnt;
  curl_off_t total_dl = 0;
  curl_off_t total_ul = 0;
#endif
  ssize_t nread;
  struct timeval now;
  bool keepon = TRUE;
  char *buf = data->state.buffer;
  struct TELNET *tn;

  *done = TRUE; /* unconditionally */

  result = init_telnet(conn);
  if(result)
    return result;

  tn = (struct TELNET *)data->req.protop;

  result = check_telnet_options(conn);
  if(result)
    return result;

#ifdef USE_WINSOCK
  /*
  ** This functionality only works with WinSock >= 2.0.  So,
  ** make sure we have it.
  */
  result = check_wsock2(data);
  if(result)
    return result;

  /* OK, so we have WinSock 2.0.  We need to dynamically */
  /* load ws2_32.dll and get the function pointers we need. */
  wsock2 = Curl_load_library(TEXT("WS2_32.DLL"));
  if(wsock2 == NULL) {
    failf(data, "failed to load WS2_32.DLL (%d)", ERRNO);
    return CURLE_FAILED_INIT;
  }

  /* Grab a pointer to WSACreateEvent */
  create_event_func = GetProcAddress(wsock2, "WSACreateEvent");
  if(create_event_func == NULL) {
    failf(data, "failed to find WSACreateEvent function (%d)", ERRNO);
    FreeLibrary(wsock2);
    return CURLE_FAILED_INIT;
  }

  /* And WSACloseEvent */
  close_event_func = GetProcAddress(wsock2, "WSACloseEvent");
  if(close_event_func == NULL) {
    failf(data, "failed to find WSACloseEvent function (%d)", ERRNO);
    FreeLibrary(wsock2);
    return CURLE_FAILED_INIT;
  }

  /* And WSAEventSelect */
  event_select_func = GetProcAddress(wsock2, "WSAEventSelect");
  if(event_select_func == NULL) {
    failf(data, "failed to find WSAEventSelect function (%d)", ERRNO);
    FreeLibrary(wsock2);
    return CURLE_FAILED_INIT;
  }

  /* And WSAEnumNetworkEvents */
  enum_netevents_func = GetProcAddress(wsock2, "WSAEnumNetworkEvents");
  if(enum_netevents_func == NULL) {
    failf(data, "failed to find WSAEnumNetworkEvents function (%d)", ERRNO);
    FreeLibrary(wsock2);
    return CURLE_FAILED_INIT;
  }

  /* We want to wait for both stdin and the socket. Since
  ** the select() function in winsock only works on sockets
  ** we have to use the WaitForMultipleObjects() call.
  */

  /* First, create a sockets event object */
  event_handle = (WSAEVENT)create_event_func();
  if(event_handle == WSA_INVALID_EVENT) {
    failf(data, "WSACreateEvent failed (%d)", SOCKERRNO);
    FreeLibrary(wsock2);
    return CURLE_FAILED_INIT;
  }

  /* Tell winsock what events we want to listen to */
  if(event_select_func(sockfd, event_handle, FD_READ|FD_CLOSE) ==
     SOCKET_ERROR) {
    close_event_func(event_handle);
    FreeLibrary(wsock2);
    return CURLE_OK;
  }

  /* The get the Windows file handle for stdin */
  stdin_handle = GetStdHandle(STD_INPUT_HANDLE);

  /* Create the list of objects to wait for */
  objs[0] = event_handle;
  objs[1] = stdin_handle;

  /* If stdin_handle is a pipe, use PeekNamedPipe() method to check it,
     else use the old WaitForMultipleObjects() way */
  if(GetFileType(stdin_handle) == FILE_TYPE_PIPE ||
     data->set.is_fread_set) {
    /* Don't wait for stdin_handle, just wait for event_handle */
    obj_count = 1;
    /* Check stdin_handle per 100 milliseconds */
    wait_timeout = 100;
  }
  else {
    obj_count = 2;
    wait_timeout = 1000;
  }

  /* Keep on listening and act on events */
  while(keepon) {
    const DWORD buf_size = (DWORD)data->set.buffer_size;
    waitret = WaitForMultipleObjects(obj_count, objs, FALSE, wait_timeout);
    switch(waitret) {
    case WAIT_TIMEOUT:
    {
      for(;;) {
        if(data->set.is_fread_set) {
          size_t n;
          /* read from user-supplied method */
          n = data->state.fread_func(buf, 1, buf_size, data->state.in);
          if(n == CURL_READFUNC_ABORT) {
            keepon = FALSE;
            result = CURLE_READ_ERROR;
            break;
          }

          if(n == CURL_READFUNC_PAUSE)
            break;

          if(n == 0)                        /* no bytes */
            break;

          readfile_read = (DWORD)n; /* fall thru with number of bytes read */
        }
        else {
          /* read from stdin */
          if(!PeekNamedPipe(stdin_handle, NULL, 0, NULL,
                            &readfile_read, NULL)) {
            keepon = FALSE;
            result = CURLE_READ_ERROR;
            break;
          }

          if(!readfile_read)
            break;

          if(!ReadFile(stdin_handle, buf, buf_size,
                       &readfile_read, NULL)) {
            keepon = FALSE;
            result = CURLE_READ_ERROR;
            break;
          }
        }

        result = send_telnet_data(conn, buf, readfile_read);
        if(result) {
          keepon = FALSE;
          break;
        }
      }
    }
    break;

    case WAIT_OBJECT_0 + 1:
    {
      if(!ReadFile(stdin_handle, buf, buf_size,
                   &readfile_read, NULL)) {
        keepon = FALSE;
        result = CURLE_READ_ERROR;
        break;
      }

      result = send_telnet_data(conn, buf, readfile_read);
      if(result) {
        keepon = FALSE;
        break;
      }
    }
    break;

    case WAIT_OBJECT_0:

      events.lNetworkEvents = 0;
      if(SOCKET_ERROR == enum_netevents_func(sockfd, event_handle, &events)) {
        err = SOCKERRNO;
        if(err != EINPROGRESS) {
          infof(data, "WSAEnumNetworkEvents failed (%d)", err);
          keepon = FALSE;
          result = CURLE_READ_ERROR;
        }
        break;
      }
      if(events.lNetworkEvents & FD_READ) {
        /* read data from network */
        result = Curl_read(conn, sockfd, buf, data->set.buffer_size, &nread);
        /* read would've blocked. Loop again */
        if(result == CURLE_AGAIN)
          break;
        /* returned not-zero, this an error */
        else if(result) {
          keepon = FALSE;
          break;
        }
        /* returned zero but actually received 0 or less here,
           the server closed the connection and we bail out */
        else if(nread <= 0) {
          keepon = FALSE;
          break;
        }

        result = telrcv(conn, (unsigned char *) buf, nread);
        if(result) {
          keepon = FALSE;
          break;
        }

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
      break;

    }

    if(data->set.timeout) {
      now = Curl_tvnow();
      if(Curl_tvdiff(now, conn->created) >= data->set.timeout) {
        failf(data, "Time-out");
        result = CURLE_OPERATION_TIMEDOUT;
        keepon = FALSE;
      }
    }
  }

  /* We called WSACreateEvent, so call WSACloseEvent */
  if(!close_event_func(event_handle)) {
    infof(data, "WSACloseEvent failed (%d)", SOCKERRNO);
  }

  /* "Forget" pointers into the library we're about to free */
  create_event_func = NULL;
  close_event_func = NULL;
  event_select_func = NULL;
  enum_netevents_func = NULL;

  /* We called LoadLibrary, so call FreeLibrary */
  if(!FreeLibrary(wsock2))
    infof(data, "FreeLibrary(wsock2) failed (%d)", ERRNO);
#else
  pfd[0].fd = sockfd;
  pfd[0].events = POLLIN;

  if(data->set.is_fread_set) {
    poll_cnt = 1;
    interval_ms = 100; /* poll user-supplied read function */
  }
  else {
    /* really using fread, so infile is a FILE* */
    pfd[1].fd = fileno((FILE *)data->state.in);
    pfd[1].events = POLLIN;
    poll_cnt = 2;
    interval_ms = 1 * 1000;
  }

  while(keepon) {
    switch(Curl_poll(pfd, poll_cnt, interval_ms)) {
    case -1:                    /* error, stop reading */
      keepon = FALSE;
      continue;
    case 0:                     /* timeout */
      pfd[0].revents = 0;
      pfd[1].revents = 0;
      /* fall through */
    default:                    /* read! */
      if(pfd[0].revents & POLLIN) {
        /* read data from network */
        result = Curl_read(conn, sockfd, buf, data->set.buffer_size, &nread);
        /* read would've blocked. Loop again */
        if(result == CURLE_AGAIN)
          break;
        /* returned not-zero, this an error */
        if(result) {
          keepon = FALSE;
          break;
        }
        /* returned zero but actually received 0 or less here,
           the server closed the connection and we bail out */
        else if(nread <= 0) {
          keepon = FALSE;
          break;
        }

        total_dl += nread;
        Curl_pgrsSetDownloadCounter(data, total_dl);
        result = telrcv(conn, (unsigned char *)buf, nread);
        if(result) {
          keepon = FALSE;
          break;
        }

        /* Negotiate if the peer has started negotiating,
           otherwise don't. We don't want to speak telnet with
           non-telnet servers, like POP or SMTP. */
        if(tn->please_negotiate && !tn->already_negotiated) {
          negotiate(conn);
          tn->already_negotiated = 1;
        }
      }

      nread = 0;
      if(poll_cnt == 2) {
        if(pfd[1].revents & POLLIN) { /* read from in file */
          nread = read(pfd[1].fd, buf, data->set.buffer_size);
        }
      }
      else {
        /* read from user-supplied method */
        nread = (int)data->state.fread_func(buf, 1, data->set.buffer_size,
                                            data->state.in);
        if(nread == CURL_READFUNC_ABORT) {
          keepon = FALSE;
          break;
        }
        if(nread == CURL_READFUNC_PAUSE)
          break;
      }

      if(nread > 0) {
        result = send_telnet_data(conn, buf, nread);
        if(result) {
          keepon = FALSE;
          break;
        }
        total_ul += nread;
        Curl_pgrsSetUploadCounter(data, total_ul);
      }
      else if(nread < 0)
        keepon = FALSE;

      break;
    } /* poll switch statement */

    if(data->set.timeout) {
      now = Curl_tvnow();
      if(Curl_tvdiff(now, conn->created) >= data->set.timeout) {
        failf(data, "Time-out");
        result = CURLE_OPERATION_TIMEDOUT;
        keepon = FALSE;
      }
    }

    if(Curl_pgrsUpdate(conn)) {
      result = CURLE_ABORTED_BY_CALLBACK;
      break;
    }
  }
#endif
  /* mark this as "no further transfer wanted" */
  Curl_setup_transfer(conn, -1, -1, FALSE, NULL, -1, NULL);

  return result;
}