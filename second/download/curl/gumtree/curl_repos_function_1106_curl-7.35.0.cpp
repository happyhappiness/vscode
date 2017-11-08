static unsigned int CURL_STDCALL gethostbyname_thread (void *arg)
{
  struct thread_sync_data *tsd = (struct thread_sync_data *)arg;

  tsd->res = Curl_ipv4_resolve_r(tsd->hostname, tsd->port);

  if(!tsd->res) {
    tsd->sock_error = SOCKERRNO;
    if(tsd->sock_error == 0)
      tsd->sock_error = RESOLVER_ENOMEM;
  }

  Curl_mutex_acquire(tsd->mtx);
  tsd->done = 1;
  Curl_mutex_release(tsd->mtx);

  return 0;
}