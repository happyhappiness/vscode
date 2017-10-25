static unsigned __stdcall gethostbyname_thread (void *arg)
{
  struct connectdata *conn = (struct connectdata*) arg;
  struct thread_data *td = (struct thread_data*) conn->async.os_specific;
  struct hostent *he;
  int    rc = 0;

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

  /* Sharing the same _iob[] element with our parent thread should
   * hopefully make printouts synchronised. I'm not sure it works
   * with a static runtime lib (MSVC's libc.lib).
   */
#ifndef _WIN32_WCE
  *stderr = *td->stderr_file;
#endif

  WSASetLastError (conn->async.status = NO_DATA); /* pending status */
  he = gethostbyname (conn->async.hostname);

  /* is the thread initiator still waiting for us ? */
  if (WaitForSingleObject(mutex_waiting, 0) == WAIT_TIMEOUT) {
    /* yes, it is */

    /* Mark that we have obtained the information, and that we are
     * calling back with it.
     */
    SetEvent(td->event_resolved);

    if (he) {
      rc = Curl_addrinfo4_callback(conn, CURL_ASYNC_SUCCESS, he);
    }
    else {
      rc = Curl_addrinfo4_callback(conn, (int)WSAGetLastError(), NULL);
    }
    TRACE(("Winsock-error %d, addr %s\n", conn->async.status,
           he ? inet_ntoa(*(struct in_addr*)he->h_addr) : "unknown"));
  }

  /* clean up */
  CloseHandle(mutex_waiting);

  return (rc);
  /* An implicit _endthreadex() here */
}