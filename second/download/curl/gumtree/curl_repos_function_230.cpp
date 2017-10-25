CURLcode Curl_wait_for_resolv(struct connectdata *conn,
                              struct Curl_dns_entry **entry)
{
  struct thread_data   *td = (struct thread_data*) conn->async.os_specific;
  struct SessionHandle *data = conn->data;
  long   timeout;
  DWORD  status, ticks;
  CURLcode rc;

  curlassert (conn && td);

  /* now, see if there's a connect timeout or a regular timeout to
     use instead of the default one */
  timeout =
    conn->data->set.connecttimeout ? conn->data->set.connecttimeout :
    conn->data->set.timeout ? conn->data->set.timeout :
    CURL_TIMEOUT_RESOLVE; /* default name resolve timeout */
  ticks = GetTickCount();

  /* wait for the thread to resolve the name */
  status = WaitForSingleObject(td->event_resolved, 1000UL*timeout);

  /* mark that we are now done waiting */
  ReleaseMutex(td->mutex_waiting);

  /* close our handle to the mutex, no point in hanging on to it */
  CloseHandle(td->mutex_waiting);
  td->mutex_waiting = NULL;

  /* close the event handle, it's useless now */
  CloseHandle(td->event_resolved);
  td->event_resolved = NULL;

  /* has the resolver thread succeeded in resolving our query ? */
  if (status == WAIT_OBJECT_0) {
    /* wait for the thread to exit, it's in the callback sequence */
    if (WaitForSingleObject(td->thread_hnd, 5000) == WAIT_TIMEOUT) {
      TerminateThread(td->thread_hnd, 0);
      conn->async.done = TRUE;
      td->thread_status = (DWORD)-1;
      TRACE(("%s() thread stuck?!, ", THREAD_NAME));
    }
    else {
      /* Thread finished before timeout; propagate Winsock error to this
       * thread.  'conn->async.done = TRUE' is set in
       * Curl_addrinfo4/6_callback().
       */
      WSASetLastError(conn->async.status);
      GetExitCodeThread(td->thread_hnd, &td->thread_status);
      TRACE(("%s() status %lu, thread retval %lu, ",
             THREAD_NAME, status, td->thread_status));
    }
  }
  else {
    conn->async.done = TRUE;
    td->thread_status = (DWORD)-1;
    TRACE(("%s() timeout, ", THREAD_NAME));
  }

  TRACE(("elapsed %lu ms\n", GetTickCount()-ticks));

  CloseHandle(td->thread_hnd);

  if(entry)
    *entry = conn->async.dns;

  rc = CURLE_OK;

  if (!conn->async.dns) {
    /* a name was not resolved */
    if (td->thread_status == CURLE_OUT_OF_MEMORY) {
      rc = CURLE_OUT_OF_MEMORY;
      failf(data, "Could not resolve host: %s", curl_easy_strerror(rc));
    }
    else if (td->thread_status == (DWORD)-1 || conn->async.status == NO_DATA) {
      failf(data, "Resolving host timed out: %s", conn->host.name);
      rc = CURLE_OPERATION_TIMEDOUT;
    }
    else if(conn->async.done) {
      failf(data, "Could not resolve host: %s; %s",
            conn->host.name, Curl_strerror(conn,conn->async.status));
      rc = CURLE_COULDNT_RESOLVE_HOST;
    }
    else
      rc = CURLE_OPERATION_TIMEDOUT;
  }

  Curl_destroy_thread_data(&conn->async);

  if(!conn->async.dns)
    conn->bits.close = TRUE;

  return (rc);
}