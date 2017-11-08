static CURLMcode multi_timeout(struct Curl_multi *multi,
                               long *timeout_ms)
{
  if(multi->timetree) {
    /* we have a tree of expire times */
    struct timeval now = Curl_tvnow();

    /* splay the lowest to the bottom */
    multi->timetree = Curl_splay(0, multi->timetree);

    /* At least currently, the splay key is a time_t for the expire time */
    *timeout_ms = (multi->timetree->key - now.tv_sec) * 1000 -
      now.tv_usec/1000;
    if(*timeout_ms < 0)
      /* 0 means immediately */
      *timeout_ms = 0;
  }
  else
    *timeout_ms = -1;

  return CURLM_OK;
}