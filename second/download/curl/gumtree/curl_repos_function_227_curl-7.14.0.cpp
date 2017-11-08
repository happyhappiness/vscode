static unsigned __stdcall getaddrinfo_thread (void *arg)
{
  struct connectdata *conn = (struct connectdata*) arg;
  struct thread_data *td   = (struct thread_data*) conn->async.os_specific;
  struct addrinfo    *res;
  char   service [NI_MAXSERV];
  int    rc;

  /* Duplicate the passed mutex handle.
   * This allows us to use it even after the container gets destroyed
   * due to a resolver timeout.
   */
  HANDLE mutex_waiting = NULL;
  HANDLE curr_proc = GetCurrentProcess();

  if (!DuplicateHandle(curr_proc, td->mutex_waiting,
                       curr_proc, &mutex_waiting, 0, FALSE,
                       DUPLICATE_SAME_ACCESS)) {
    /* failed to duplicate the mutex, no point in continuing */
    return -1;
  }

#ifndef _WIN32_WCE
  *stderr = *td->stderr_file;
#endif

  itoa(conn->async.port, service, 10);

  WSASetLastError(conn->async.status = NO_DATA); /* pending status */

  rc = getaddrinfo(conn->async.hostname, service, &td->hints, &res);

  /* is the thread initiator still waiting for us ? */
  if (WaitForSingleObject(mutex_waiting, 0) == WAIT_TIMEOUT) {
    /* yes, it is */

    /* Mark that we have obtained the information, and that we are
     * calling back with it.
     */
    SetEvent(td->event_resolved);

    if (rc == 0) {
#ifdef DEBUG_THREADING_GETADDRINFO
      dump_addrinfo (conn, res);
#endif
      rc = Curl_addrinfo6_callback(conn, CURL_ASYNC_SUCCESS, res);
    }
    else {
      rc = Curl_addrinfo6_callback(conn, (int)WSAGetLastError(), NULL);
      TRACE(("Winsock-error %d, no address\n", conn->async.status));
    }
  }

  /* clean up */
  CloseHandle(mutex_waiting);

  return (rc);
  /* An implicit _endthreadex() here */
}