static bool init_resolve_thread(struct connectdata *conn,
                                const char *hostname, int port,
                                const struct addrinfo *hints)
{
  struct thread_data *td = calloc(1, sizeof(struct thread_data));
  int err = RESOLVER_ENOMEM;

  conn->async.os_specific = (void *)td;
  if(!td)
    goto err_exit;

  conn->async.port = port;
  conn->async.done = FALSE;
  conn->async.status = 0;
  conn->async.dns = NULL;
  td->thread_hnd = curl_thread_t_null;

  if(!init_thread_sync_data(td, hostname, port, hints))
    goto err_exit;

  free(conn->async.hostname);
  conn->async.hostname = strdup(hostname);
  if(!conn->async.hostname)
    goto err_exit;

#ifdef HAVE_GETADDRINFO
  td->thread_hnd = Curl_thread_create(getaddrinfo_thread, &td->tsd);
#else
  td->thread_hnd = Curl_thread_create(gethostbyname_thread, &td->tsd);
#endif

  if(!td->thread_hnd) {
    err = errno;
    goto err_exit;
  }

  return TRUE;

 err_exit:
  destroy_async_data(&conn->async);

  errno = err;
  return FALSE;
}