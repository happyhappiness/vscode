static void destroy_async_data (struct Curl_async *async)
{
  if(async->hostname)
    free(async->hostname);

  if(async->os_specific) {
    struct thread_data *td = (struct thread_data*) async->os_specific;

    if(td->thread_hnd != curl_thread_t_null)
      Curl_thread_join(&td->thread_hnd);

    destroy_thread_sync_data(&td->tsd);

    free(async->os_specific);
  }
  async->hostname = NULL;
  async->os_specific = NULL;
}