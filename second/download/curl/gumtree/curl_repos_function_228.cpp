void Curl_destroy_thread_data (struct Curl_async *async)
{
  if (async->hostname)
    free(async->hostname);

  if (async->os_specific) {
    struct thread_data *td = (struct thread_data*) async->os_specific;
    curl_socket_t sock = td->dummy_sock;

    if (sock != CURL_SOCKET_BAD)
      sclose(sock);

    /* destroy the synchronization objects */
    if (td->mutex_waiting)
      CloseHandle(td->mutex_waiting);
    td->mutex_waiting = NULL;
    if (td->event_resolved)
      CloseHandle(td->event_resolved);

    free(async->os_specific);
  }
  async->hostname = NULL;
  async->os_specific = NULL;
}