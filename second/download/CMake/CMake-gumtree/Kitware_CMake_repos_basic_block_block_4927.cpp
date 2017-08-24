f(s != CURL_SOCKET_TIMEOUT) {

    struct Curl_sh_entry *entry = sh_getentry(&multi->sockhash, s);

    if(!entry)
      /* Unmatched socket, we can't act on it but we ignore this fact.  In
         real-world tests it has been proved that libevent can in fact give
         the application actions even though the socket was just previously
         asked to get removed, so thus we better survive stray socket actions
         and just move on. */
      ;
    else {
      SIGPIPE_VARIABLE(pipe_st);

      data = entry->easy;

      if(data->magic != CURLEASY_MAGIC_NUMBER)
        /* bad bad bad bad bad bad bad */
        return CURLM_INTERNAL_ERROR;

      /* If the pipeline is enabled, take the handle which is in the head of
         the pipeline. If we should write into the socket, take the send_pipe
         head.  If we should read from the socket, take the recv_pipe head. */
      if(data->easy_conn) {
        if((ev_bitmask & CURL_POLL_OUT) &&
           data->easy_conn->send_pipe.head)
          data = data->easy_conn->send_pipe.head->ptr;
        else if((ev_bitmask & CURL_POLL_IN) &&
                data->easy_conn->recv_pipe.head)
          data = data->easy_conn->recv_pipe.head->ptr;
      }

      if(data->easy_conn &&
         !(data->easy_conn->handler->flags & PROTOPT_DIRLOCK))
        /* set socket event bitmask if they're not locked */
        data->easy_conn->cselect_bits = ev_bitmask;

      sigpipe_ignore(data, &pipe_st);
      result = multi_runsingle(multi, now, data);
      sigpipe_restore(&pipe_st);

      if(data->easy_conn &&
         !(data->easy_conn->handler->flags & PROTOPT_DIRLOCK))
        /* clear the bitmask only if not locked */
        data->easy_conn->cselect_bits = 0;

      if(CURLM_OK >= result)
        /* get the socket(s) and check if the state has been changed since
           last */
        singlesocket(multi, data);

      /* Now we fall-through and do the timer-based stuff, since we don't want
         to force the user to have to deal with timeouts as long as at least
         one connection in fact has traffic. */

      data = NULL; /* set data to NULL again to avoid calling
                      multi_runsingle() in case there's no need to */
      now = Curl_tvnow(); /* get a newer time since the multi_runsingle() loop
                             may have taken some time */
    }
  }
  else {
    /* Asked to run due to time-out. Clear the 'lastcall' variable to force
       update_timer() to trigger a callback to the app again even if the same
       timeout is still the one to run after this call. That handles the case
       when the application asks libcurl to run the timeout prematurely. */
    memset(&multi->timer_lastcall, 0, sizeof(multi->timer_lastcall));
  }