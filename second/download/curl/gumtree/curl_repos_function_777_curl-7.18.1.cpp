static CURLMcode multi_socket(struct Curl_multi *multi,
                              bool checkall,
                              curl_socket_t s,
                              int ev_bitmask,
                              int *running_handles)
{
  CURLMcode result = CURLM_OK;
  struct SessionHandle *data = NULL;
  struct Curl_tree *t;

  if(checkall) {
    struct Curl_one_easy *easyp;
    /* *perform() deals with running_handles on its own */
    result = curl_multi_perform(multi, running_handles);

    /* walk through each easy handle and do the socket state change magic
       and callbacks */
    easyp=multi->easy.next;
    while(easyp != &multi->easy) {
      singlesocket(multi, easyp);
      easyp = easyp->next;
    }

    /* or should we fall-through and do the timer-based stuff? */
    return result;
  }
  else if(s != CURL_SOCKET_TIMEOUT) {

    struct Curl_sh_entry *entry =
      Curl_hash_pick(multi->sockhash, (char *)&s, sizeof(s));

    if(!entry)
      /* unmatched socket, major problemo! */
      return CURLM_BAD_SOCKET; /* better return code? */

    data = entry->easy;

    if(data->magic != CURLEASY_MAGIC_NUMBER)
      /* bad bad bad bad bad bad bad */
      return CURLM_INTERNAL_ERROR;

    if(data->set.one_easy->easy_conn)  /* set socket event bitmask */
      data->set.one_easy->easy_conn->cselect_bits = ev_bitmask;

    result = multi_runsingle(multi, data->set.one_easy);

    if(data->set.one_easy->easy_conn)
      data->set.one_easy->easy_conn->cselect_bits = 0;

    if(CURLM_OK >= result)
      /* get the socket(s) and check if the state has been changed since
         last */
      singlesocket(multi, data->set.one_easy);

    /* Now we fall-through and do the timer-based stuff, since we don't want
       to force the user to have to deal with timeouts as long as at least one
       connection in fact has traffic. */

    data = NULL; /* set data to NULL again to avoid calling multi_runsingle()
                    in case there's no need to */
  }

  /*
   * The loop following here will go on as long as there are expire-times left
   * to process in the splay and 'data' will be re-assigned for every expired
   * handle we deal with.
   */
  do {
    int key;
    struct timeval now;

    /* the first loop lap 'data' can be NULL */
    if(data) {
      result = multi_runsingle(multi, data->set.one_easy);

      if(CURLM_OK >= result)
        /* get the socket(s) and check if the state has been changed since
           last */
        singlesocket(multi, data->set.one_easy);
    }

    /* Check if there's one (more) expired timer to deal with! This function
       extracts a matching node if there is one */

    now = Curl_tvnow();
    key = now.tv_sec; /* drop the usec part */

    multi->timetree = Curl_splaygetbest(key, multi->timetree, &t);
    if(t) {
      /* assign 'data' to be the easy handle we just removed from the splay
         tree */
      data = t->payload;
      /* clear the expire time within the handle we removed from the
         splay tree */
      data->state.expiretime.tv_sec = 0;
      data->state.expiretime.tv_usec = 0;
    }

  } while(t);

  *running_handles = multi->num_alive;
  return result;
}