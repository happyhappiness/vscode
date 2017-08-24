e(!done) {
    CURLMsg *msg;
    struct socketmonitor *m;
    struct pollfd *f;
    struct pollfd fds[4];
    int numfds=0;
    int pollrc;
    int i;
    struct timeval before;
    struct timeval after;

    /* populate the fds[] array */
    for(m = ev->list, f=&fds[0]; m; m = m->next) {
      f->fd = m->socket.fd;
      f->events = m->socket.events;
      f->revents = 0;
      /* fprintf(stderr, "poll() %d check socket %d\n", numfds, f->fd); */
      f++;
      numfds++;
    }

    /* get the time stamp to use to figure out how long poll takes */
    before = curlx_tvnow();

    /* wait for activity or timeout */
    pollrc = Curl_poll(fds, numfds, (int)ev->ms);

    after = curlx_tvnow();

    ev->msbump = FALSE; /* reset here */

    if(0 == pollrc) {
      /* timeout! */
      ev->ms = 0;
      /* fprintf(stderr, "call curl_multi_socket_action(TIMEOUT)\n"); */
      mcode = curl_multi_socket_action(multi, CURL_SOCKET_TIMEOUT, 0,
                                       &ev->running_handles);
    }
    else if(pollrc > 0) {
      /* loop over the monitored sockets to see which ones had activity */
      for(i = 0; i< numfds; i++) {
        if(fds[i].revents) {
          /* socket activity, tell libcurl */
          int act = poll2cselect(fds[i].revents); /* convert */
          infof(multi->easyp, "call curl_multi_socket_action(socket %d)\n",
                fds[i].fd);
          mcode = curl_multi_socket_action(multi, fds[i].fd, act,
                                           &ev->running_handles);
        }
      }

      if(!ev->msbump) {
        /* If nothing updated the timeout, we decrease it by the spent time.
         * If it was updated, it has the new timeout time stored already.
         */
        time_t timediff = curlx_tvdiff(after, before);
        if(timediff > 0) {
          if(timediff > ev->ms)
            ev->ms = 0;
          else
            ev->ms -= (long)timediff;
        }
      }
    }
    else
      return CURLE_RECV_ERROR;

    if(mcode)
      return CURLE_URL_MALFORMAT; /* TODO: return a proper error! */

    /* we don't really care about the "msgs_in_queue" value returned in the
       second argument */
    msg = curl_multi_info_read(multi, &pollrc);
    if(msg) {
      result = msg->data.result;
      done = TRUE;
    }
  }