static unsigned __stdcall getaddrinfo_thread (void *arg)
{
  struct connectdata *conn = (struct connectdata*) arg;
  struct thread_data *td   = (struct thread_data*) conn->async.os_specific;
  struct addrinfo    *res;
  char   service [NI_MAXSERV];
  int    rc;
  struct addrinfo hints = td->hints;

  /* Duplicate the passed mutex handle.
   * This allows us to use it even after the container gets destroyed
   * due to a resolver timeout.
   */
  struct thread_sync_data tsd = { 0,0,0,NULL };
  if (!init_thread_sync_data(td, conn->async.hostname, &tsd)) {
    /* thread synchronization data initialization failed */
    return -1;
  }

#ifndef _WIN32_WCE
  *stderr = *td->stderr_file;
#endif

  itoa(conn->async.port, service, 10);

  WSASetLastError(conn->async.status = NO_DATA); /* pending status */

  /* Signaling that we have initialized all copies of data and handles we
     need */
  SetEvent(td->event_thread_started);

  rc = getaddrinfo(tsd.hostname, service, &hints, &res);

  /* is parent thread waiting for us and are we able to access conn members? */
  if (acquire_thread_sync(&tsd)) {
    /* Mark that we have obtained the information, and that we are calling
       back with it. */
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
    release_thread_sync(&tsd);
  }

  /* clean up */
  destroy_thread_sync_data(&tsd);

  return (rc);
  /* An implicit _endthreadex() here */
}