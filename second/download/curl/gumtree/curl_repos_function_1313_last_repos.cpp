static bool init_resolve_thread(struct connectdata *conn,
                                const char *hostname, int port,
                                const struct addrinfo *hints)
{
  struct thread_data *td = calloc(1, sizeof(struct thread_data));
  int err = ENOMEM;

  conn->async.os_specific = (void *)td;
  if(!td)
    goto errno_exit;

  conn->async.port = port;
  conn->async.done = FALSE;
  conn->async.status = 0;
  conn->async.dns = NULL;
  td->thread_hnd = curl_thread_t_null;

  if(!init_thread_sync_data(td, hostname, port, hints)) {
    conn->async.os_specific = NULL;
    free(td);
    goto errno_exit;
  }

  free(conn->async.hostname);
  conn->async.hostname = strdup(hostname);
  if(!conn->async.hostname)
    goto err_exit;

  /* The thread will set this to 1 when complete. */
  td->tsd.done = 0;

#ifdef HAVE_GETADDRINFO
  td->thread_hnd = Curl_thread_create(getaddrinfo_thread, &td->tsd);
#else
  td->thread_hnd = Curl_thread_create(gethostbyname_thread, &td->tsd);
#endif

  if(!td->thread_hnd) {
    /* The thread never started, so mark it as done here for proper cleanup. */
    td->tsd.done = 1;
    err = errno;
    goto err_exit;
  }

  return TRUE;

 err_exit:
  destroy_async_data(&conn->async);

 errno_exit:
  errno = err;
  return FALSE;
}