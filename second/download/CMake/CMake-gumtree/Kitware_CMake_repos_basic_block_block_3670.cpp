{
  struct thread_sync_data *tsd = &td->tsd;

  memset(tsd, 0, sizeof(*tsd));

  tsd->td = td;
  tsd->port = port;
#ifdef HAVE_GETADDRINFO
  DEBUGASSERT(hints);
  tsd->hints = *hints;
#else
  (void) hints;
#endif

  tsd->mtx = malloc(sizeof(curl_mutex_t));
  if(tsd->mtx == NULL)
    goto err_exit;

  Curl_mutex_init(tsd->mtx);

  tsd->sock_error = CURL_ASYNC_SUCCESS;

  /* Copying hostname string because original can be destroyed by parent
   * thread during gethostbyname execution.
   */
  tsd->hostname = strdup(hostname);
  if(!tsd->hostname)
    goto err_exit;

  return 1;

 err_exit:
  /* Memory allocation failed */
  destroy_thread_sync_data(tsd);
  return 0;
}