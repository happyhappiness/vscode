CURLMcode curl_multi_perform(CURLM *multi_handle, int *running_handles)
{
  struct Curl_multi *multi=(struct Curl_multi *)multi_handle;
  struct Curl_one_easy *easy;
  CURLMcode returncode=CURLM_OK;
  struct Curl_tree *t;

  if(!GOOD_MULTI_HANDLE(multi))
    return CURLM_BAD_HANDLE;

  easy=multi->easy.next;
  while(easy != &multi->easy) {
    CURLMcode result;

    result = multi_runsingle(multi, easy);
    if(result)
      returncode = result;

    easy = easy->next; /* operate on next handle */
  }

  /*
   * Simply remove all expired timers from the splay since handles are dealt
   * with unconditionally by this function and curl_multi_timeout() requires
   * that already passed/handled expire times are removed from the splay.
   */
  do {
    struct timeval now = Curl_tvnow();
    int key = now.tv_sec; /* drop the usec part */

    multi->timetree = Curl_splaygetbest(key, multi->timetree, &t);
    if(t) {
      struct SessionHandle *d = t->payload;
      struct timeval* tv = &d->state.expiretime;

      /* clear the expire times within the handles that we remove from the
         splay tree */
      tv->tv_sec = 0;
      tv->tv_usec = 0;
    }

  } while(t);

  *running_handles = multi->num_alive;

  if( CURLM_OK >= returncode )
    update_timer(multi);
  return returncode;
}