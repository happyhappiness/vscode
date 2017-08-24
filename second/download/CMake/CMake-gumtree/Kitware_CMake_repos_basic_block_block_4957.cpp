{
    struct Curl_easy *data = e->ptr;
    struct curl_llist_element *next = e->next;

    if(data->mstate == CURLM_STATE_CONNECT_PEND) {
      multistate(data, CURLM_STATE_CONNECT);

      /* Remove this node from the list */
      Curl_llist_remove(&multi->pending, e, NULL);

      /* Make sure that the handle will be processed soonish. */
      Curl_expire(data, 0, EXPIRE_RUN_NOW);
    }

    e = next; /* operate on next handle */
  }