{
    /* this handle is "alive" so we need to count down the total number of
       alive connections when this is removed */
    multi->num_alive--;

    /* When this handle gets removed, other handles may be able to get the
       connection */
    Curl_multi_process_pending_handles(multi);
  }