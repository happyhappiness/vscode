static int select_ws(int nfds, fd_set *readfds, fd_set *writefds,
                     fd_set *exceptfds, struct timeval *timeout)
{
  DWORD milliseconds, wait, idx;
  WSANETWORKEVENTS wsanetevents;
  struct select_ws_data *data;
  HANDLE handle, *handles;
  curl_socket_t sock;
  long networkevents;
  WSAEVENT wsaevent;
  int error, fds;
  HANDLE waitevent = NULL;
  DWORD nfd = 0, thd = 0, wsa = 0;
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

  /* create internal event to signal waiting threads */
  waitevent = CreateEvent(NULL, TRUE, FALSE, NULL);
  if(!waitevent) {
    errno = ENOMEM;
    return -1;
  }

  /* allocate internal array for the internal data */
  data = malloc(nfds * sizeof(struct select_ws_data));
  if(data == NULL) {
    errno = ENOMEM;
    return -1;
  }

  /* allocate internal array for the internal event handles */
  handles = malloc(nfds * sizeof(HANDLE));
  if(handles == NULL) {
    free(data);
    errno = ENOMEM;
    return -1;
  }

  /* clear internal arrays */
  memset(data, 0, nfds * sizeof(struct select_ws_data));
  memset(handles, 0, nfds * sizeof(HANDLE));

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
      data[nfd].fd = curlx_sitosk(fds);
      if(fds == fileno(stdin)) {
        handle = GetStdHandle(STD_INPUT_HANDLE);
        handle = select_ws_wait(handle, waitevent);
        handles[nfd] = handle;
        data[thd].thread = handle;
        thd++;
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
            handle = (HANDLE) wsaevent;
            handles[nfd] = handle;
            data[wsa].wsasock = curlx_sitosk(fds);
            data[wsa].wsaevent = wsaevent;
            wsa++;
          }
          else {
            WSACloseEvent(wsaevent);
            handle = (HANDLE) curlx_sitosk(fds);
            handle = select_ws_wait(handle, waitevent);
            handles[nfd] = handle;
            data[thd].thread = handle;
            thd++;
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

  /* signal the event handle for the waiting threads */
  SetEvent(waitevent);

  /* loop over the internal handles returned in the descriptors */
  for(idx = 0; idx < nfd; idx++) {
    handle = handles[idx];
    sock = data[idx].fd;
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
        