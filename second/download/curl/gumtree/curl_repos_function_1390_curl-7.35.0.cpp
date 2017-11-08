static CURLMcode
multi_addtimeout(struct curl_llist *timeoutlist,
                 struct timeval *stamp)
{
  struct curl_llist_element *e;
  struct timeval *timedup;
  struct curl_llist_element *prev = NULL;

  timedup = malloc(sizeof(*timedup));
  if(!timedup)
    return CURLM_OUT_OF_MEMORY;

  /* copy the timestamp */
  memcpy(timedup, stamp, sizeof(*timedup));

  if(Curl_llist_count(timeoutlist)) {
    /* find the correct spot in the list */
    for(e = timeoutlist->head; e; e = e->next) {
      struct timeval *checktime = e->ptr;
      long diff = curlx_tvdiff(*checktime, *timedup);
      if(diff > 0)
        break;
      prev = e;
    }

  }
  /* else
     this is the first timeout on the list */

  if(!Curl_llist_insert_next(timeoutlist, prev, timedup)) {
    free(timedup);
    return CURLM_OUT_OF_MEMORY;
  }

  return CURLM_OK;
}