static unsigned __stdcall gethostbyname_thread (void *arg)
{
  struct connectdata *conn = (struct connectdata*) arg;
  struct thread_data *td = (struct thread_data*) conn->async.os_specific;
  struct hostent *he;
  int    rc = 0;

  /* Duplicate the passed mutex and event handles.
   * This allows us to use it even after the container gets destroyed
   * due to a resolver timeout.
   */
  struct thread_sync_data tsd = { 0,0,0,NULL };

  if(!init_thread_sync_data(td, conn->async.hostname, &tsd)) {
    /* thread synchronization data initialization failed */
    return (unsigned)-1;
  }

  conn->async.status = NO_DATA;  /* pending status */
  SET_SOCKERRNO(conn->async.status);

  /* Signaling that we have initialized all copies of data and handles we
     need */
  SetEvent(td->event_thread_started);

  he = gethostbyname (tsd.hostname);

  /* is parent thread waiting for us and are we able to access conn members? */
  if(acquire_thread_sync(&tsd)) {
    /* Mark that we have obtained the information, and that we are calling
     * back with it. */
    SetEvent(td->event_resolved);
    if(he) {
      rc = Curl_addrinfo4_callback(conn, CURL_ASYNC_SUCCESS, he);
    }
    else {
      rc = Curl_addrinfo4_callback(conn, SOCKERRNO, NULL);
    }
    TRACE(("Winsock-error %d, addr %s\n", conn->async.status,
           he ? inet_ntoa(*(struct in_addr*)he->h_addr) : "unknown"));
    release_thread_sync(&tsd);
  }

  /* clean up */
  destroy_thread_sync_data(&tsd);

  return (rc);
  /* An implicit _endthreadex() here */
}