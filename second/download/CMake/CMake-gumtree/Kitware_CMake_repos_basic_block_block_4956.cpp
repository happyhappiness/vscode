{
      multistate(data, CURLM_STATE_CONNECT);

      /* Remove this node from the list */
      Curl_llist_remove(&multi->pending, e, NULL);

      /* Make sure that the handle will be processed soonish. */
      Curl_expire(data, 0, EXPIRE_RUN_NOW);
    }