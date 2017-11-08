void Curl_destroy_thread_data (struct Curl_async *async)
{
  if(async->hostname)
    free(async->hostname);

  if(async->os_specific) {
    struct thread_data *td = (struct thread_data*) async->os_specific;
    curl_socket_t sock = td->dummy_sock;

    if(td->mutex_terminate && td->event_terminate) {
      /* Signaling resolver thread to terminate */
      if(WaitForSingleObject(td->mutex_terminate, INFINITE) == WAIT_OBJECT_0) {
        SetEvent(td->event_terminate);
        ReleaseMutex(td->mutex_terminate);
      }
      else {
        /* Something went wrong - just ignoring it */
      }
    }

    if(td->mutex_terminate)
      CloseHandle(td->mutex_terminate);
    if(td->event_terminate)
      CloseHandle(td->event_terminate);
    if(td->event_thread_started)
      CloseHandle(td->event_thread_started);

    if(sock != CURL_SOCKET_BAD)
      sclose(sock);

    /* destroy the synchronization objects */
    if(td->mutex_waiting)
      CloseHandle(td->mutex_waiting);
    td->mutex_waiting = NULL;
    if(td->event_resolved)
      CloseHandle(td->event_resolved);

    if(td->thread_hnd)
      CloseHandle(td->thread_hnd);

    free(async->os_specific);
  }
  async->hostname = NULL;
  async->os_specific = NULL;
}