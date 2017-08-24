{
  struct Curl_easy *data = conn->data;
  struct thread_data   *td = (struct thread_data*) conn->async.os_specific;
  int done = 0;

  *entry = NULL;

  if(!td) {
    DEBUGASSERT(td);
    return CURLE_COULDNT_RESOLVE_HOST;
  }

  Curl_mutex_acquire(td->tsd.mtx);
  done = td->tsd.done;
  Curl_mutex_release(td->tsd.mtx);

  if(done) {
    getaddrinfo_complete(conn);

    if(!conn->async.dns) {
      CURLcode result = resolver_error(conn);
      destroy_async_data(&conn->async);
      return result;
    }
    destroy_async_data(&conn->async);
    *entry = conn->async.dns;
  }
  else {
    /* poll for name lookup done with exponential backoff up to 250ms */
    time_t elapsed = Curl_tvdiff(Curl_tvnow(), data->progress.t_startsingle);
    if(elapsed < 0)
      elapsed = 0;

    if(td->poll_interval == 0)
      /* Start at 1ms poll interval */
      td->poll_interval = 1;
    else if(elapsed >= td->interval_end)
      /* Back-off exponentially if last interval expired  */
      td->poll_interval *= 2;

    if(td->poll_interval > 250)
      td->poll_interval = 250;

    td->interval_end = elapsed + td->poll_interval;
    Curl_expire(conn->data, td->poll_interval, EXPIRE_ASYNC_NAME);
  }

  return CURLE_OK;
}