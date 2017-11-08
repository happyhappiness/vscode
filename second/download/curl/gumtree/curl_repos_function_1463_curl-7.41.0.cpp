CURLMcode curl_multi_perform(CURLM *multi_handle, int *running_handles)
{
  struct Curl_multi *multi=(struct Curl_multi *)multi_handle;
  struct SessionHandle *data;
  CURLMcode returncode=CURLM_OK;
  struct Curl_tree *t;
  struct timeval now = Curl_tvnow();

  if(!GOOD_MULTI_HANDLE(multi))
    return CURLM_BAD_HANDLE;

  data=multi->easyp;
  while(data) {
    CURLMcode result;
    struct WildcardData *wc = &data->wildcard;
    SIGPIPE_VARIABLE(pipe_st);

    if(data->set.wildcardmatch) {
      if(!wc->filelist) {
        CURLcode ret = Curl_wildcard_init(wc); /* init wildcard structures */
        if(ret)
          return CURLM_OUT_OF_MEMORY;
      }
    }

    sigpipe_ignore(data, &pipe_st);
    result = multi_runsingle(multi, now, data);
    sigpipe_restore(&pipe_st);

    if(data->set.wildcardmatch) {
      /* destruct wildcard structures if it is needed */
      if(wc->state == CURLWC_DONE || result)
        Curl_wildcard_dtor(wc);
    }

    if(result)
      returncode = result;

    data = data->next; /* operate on next handle */
  }

  /*
   * Simply remove all expired timers from the splay since handles are dealt
   * with unconditionally by this function and curl_multi_timeout() requires
   * that already passed/handled expire times are removed from the splay.
   *
   * It is important that the 'now' value is set at the entry of this function
   * and not for the current time as it may have ticked a little while since
   * then and then we risk this loop to remove timers that actually have not
   * been handled!
   */
  do {
    multi->timetree = Curl_splaygetbest(now, multi->timetree, &t);
    if(t)
      /* the removed may have another timeout in queue */
      (void)add_next_timeout(now, multi, t->payload);

  } while(t);

  *running_handles = multi->num_alive;

  if(CURLM_OK >= returncode)
    update_timer(multi);

  return returncode;
}