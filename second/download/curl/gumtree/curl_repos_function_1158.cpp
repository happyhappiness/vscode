static
void destroy_thread_sync_data(struct thread_sync_data * tsd)
{
  if(tsd->mtx) {
    Curl_mutex_destroy(tsd->mtx);
    free(tsd->mtx);
  }

  if(tsd->hostname)
    free(tsd->hostname);

  if(tsd->res)
    Curl_freeaddrinfo(tsd->res);

  memset(tsd,0,sizeof(*tsd));
}