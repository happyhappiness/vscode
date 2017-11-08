static int select_ws(int nfds, fd_set *readfds, fd_set *writefds,
                     fd_set *exceptfds, struct timeval *timeout)
{
  DWORD milliseconds, wait, idx;
  WSAEVENT wsaevent, *wsaevents;
  WSANETWORKEVENTS wsanetevents;
  HANDLE handle, *handles;
  curl_socket_t sock, *fdarr, *wsasocks;
  long networkevents;
  int error, fds;
  DWORD nfd = 0, wsa = 0;
  int ret = 0;

  /* check if the input value is valid */
  if(nfds < 0) {
    errno = EINVAL;
    return -1;
  }

  /* check if we got descriptors, sleep in case we got none */
  if(!nfds) {
    Sleep((timeout->tv_sec * 1000) + (timeout->tv_usec / 1000));
    return 0;
  }

  /* allocate internal array for the original input handles */
  fdarr = malloc(nfds * sizeof(curl_socket_t));
  if(fdarr == NULL) {
    errno = ENOMEM;
    return -1;
  }

  /* allocate internal array for the internal event handles */
  handles = malloc(nfds * sizeof(HANDLE));
  if(handles == NULL) {
    errno = ENOMEM;
    return -1;
  }

  /* allocate internal array for the internal socket handles */
  wsasocks = malloc(nfds * sizeof(curl_socket_t));
  if(wsasocks == NULL) {
    errno = ENOMEM;
    return -1;
  }

  /* allocate internal array for the internal WINSOCK2 events */
  wsaevents = malloc(nfds * sizeof(WSAEVENT));
  if(wsaevents == NULL) {
    errno = ENOMEM;
    return -1;
  }

  /* loop over the handles in the input descriptor sets */
  for(fds = 0; fds < nfds; fds++) {
    networkevents = 0;
    handles[nfd] = 0;

    if(FD_ISSET(fds, readfds))
      networkevents |= FD_READ|FD_ACCEPT|FD_CLOSE;

    if(FD_ISSET(fds, writefds))
      networkevents |= FD_WRITE|FD_CONNECT;

    if(FD_ISSET(fds, exceptfds))
      networkevents |= FD_OOB|FD_CLOSE;

    /* only wait for events for which we actually care */
    if(networkevents) {
      fdarr[nfd] = curlx_sitosk(fds);
      if(fds == fileno(stdin)) {
        handles[nfd] = CreateThread(NULL, 0,
                                    &select_ws_stdin_wait_thread,
                                    GetStdHandle(STD_INPUT_HANDLE),
                                    0, NULL);
      }
      else if(fds == fileno(stdout)) {
        handles[nfd] = GetStdHandle(STD_OUTPUT_HANDLE);
      }
      else if(fds == fileno(stderr)) {
        handles[nfd] = GetStdHandle(STD_ERROR_HANDLE);
      }
      else {
        wsaevent = WSACreateEvent();
        if(wsaevent != WSA_INVALID_EVENT) {
          error = WSAEventSelect(fds, wsaevent, networkevents);
          if(error != SOCKET_ERROR) {
            handles[nfd] = wsaevent;
            wsasocks[wsa] = curlx_sitosk(fds);
            wsaevents[wsa] = wsaevent;
            wsa++;
          }
          else {
            handles[nfd] = (HANDLE) curlx_sitosk(fds);
            WSACloseEvent(wsaevent);
          }
        }
      }
      nfd++;
    }
  }

  /* convert struct timeval to milliseconds */
  if(timeout) {
    milliseconds = ((timeout->tv_sec * 1000) + (timeout->tv_usec / 1000));
  }
  else {
    milliseconds = INFINITE;
  }

  /* wait for one of the internal handles to trigger */
  wait = WaitForMultipleObjectsEx(nfd, handles, FALSE, milliseconds, FALSE);

  /* loop over the internal handles returned in the descriptors */
  for(idx = 0; idx < nfd; idx++) {
    handle = handles[idx];
    sock = fdarr[idx];
    fds = curlx_sktosi(sock);

    /* check if the current internal handle was triggered */
    if(wait != WAIT_FAILED && (wait - WAIT_OBJECT_0) <= idx &&
       WaitForSingleObjectEx(handle, 0, FALSE) == WAIT_OBJECT_0) {
      /* first handle stdin, stdout and stderr */
      if(fds == fileno(stdin)) {
        /* stdin is never ready for write or exceptional */
        FD_CLR(sock, writefds);
        FD_CLR(sock, exceptfds);
      }
      else if(fds == fileno(stdout) || fds == fileno(stderr)) {
        /* stdout and stderr are never ready for read or exceptional */
        FD_CLR(sock, readfds);
        FD_CLR(sock, exceptfds);
      }
      else {
        /* try to handle the event with the WINSOCK2 functions */
        error = WSAEnumNetworkEvents(fds, handle, &wsanetevents);
        if(error != SOCKET_ERROR) {
          /* remove from descriptor set if not ready for read/accept/close */
          if(!(wsanetevents.lNetworkEvents & (FD_READ|FD_ACCEPT|FD_CLOSE)))
            FD_CLR(sock, readfds);

          /* remove from descriptor set if not ready for write/connect */
          if(!(wsanetevents.lNetworkEvents & (FD_WRITE|FD_CONNECT)))
            FD_CLR(sock, writefds);

          /* HACK:
           * use exceptfds together with readfds to signal
           * that the connection was closed by the client.
           *
           * Reason: FD_CLOSE is only signaled once, sometimes
           * at the same time as FD_READ with data being available.
           * This means that recv/sread is not reliable to detect
           * that the connection is closed.
           */
          /* remove from descriptor set if not exceptional */
          if(!(wsanetevents.lNetworkEvents & (FD_OOB|FD_CLOSE)))
            FD_CLR(sock, exceptfds);
        }
      }

      /* check if the event has not been filtered using specific tests */
      if(FD_ISSET(sock, readfds) || FD_ISSET(sock, writefds) ||
         FD_ISSET(sock, exceptfds)) {
        ret++;
      }
    }
    else {
      /* remove from all descriptor sets since this handle did not trigger */
      FD_CLR(sock, readfds);
      FD_CLR(sock, writefds);
      FD_CLR(sock, exceptfds);
    }
  }

  for(idx = 0; idx < wsa; idx++) {
    WSAEventSelect(wsasocks[idx], NULL, 0);
    WSACloseEvent(wsaevents[idx]);
  }

  free(wsaevents);
  free(wsasocks);
  free(handles);
  free(fdarr);

  return ret;
}