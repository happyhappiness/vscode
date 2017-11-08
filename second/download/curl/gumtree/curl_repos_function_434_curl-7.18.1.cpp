static CURLcode
Transfer(struct connectdata *conn)
{
  CURLcode result;
  struct SessionHandle *data = conn->data;
  struct SingleRequest *k = &data->req;
  bool done=FALSE;

  if((conn->sockfd == CURL_SOCKET_BAD) &&
     (conn->writesockfd == CURL_SOCKET_BAD))
    /* nothing to read, nothing to write, we're already OK! */
    return CURLE_OK;

  /* we want header and/or body, if neither then don't do this! */
  if(!k->getheader && data->set.opt_no_body)
    return CURLE_OK;

  while(!done) {
    curl_socket_t fd_read;
    curl_socket_t fd_write;

    /* limit-rate logic: if speed exceeds threshold, then do not include fd in
       select set. The current speed is recalculated in each Curl_readwrite()
       call */
    if((k->keepon & KEEP_WRITE) &&
        (!data->set.max_send_speed ||
         (data->progress.ulspeed < data->set.max_send_speed) )) {
      fd_write = conn->writesockfd;
      k->keepon &= ~KEEP_WRITE_HOLD;
    }
    else {
      fd_write = CURL_SOCKET_BAD;
      if(k->keepon & KEEP_WRITE)
        k->keepon |= KEEP_WRITE_HOLD; /* hold it */
    }

    if((k->keepon & KEEP_READ) &&
        (!data->set.max_recv_speed ||
         (data->progress.dlspeed < data->set.max_recv_speed)) ) {
      fd_read = conn->sockfd;
      k->keepon &= ~KEEP_READ_HOLD;
    }
    else {
      fd_read = CURL_SOCKET_BAD;
      if(k->keepon & KEEP_READ)
        k->keepon |= KEEP_READ_HOLD; /* hold it */
    }

    /* pause logic. Don't check descriptors for paused connections */
    if(k->keepon & KEEP_READ_PAUSE)
      fd_read = CURL_SOCKET_BAD;
    if(k->keepon & KEEP_WRITE_PAUSE)
      fd_write = CURL_SOCKET_BAD;

    /* The *_HOLD and *_PAUSE logic is necessary since even though there might
       be no traffic during the select interval, we still call
       Curl_readwrite() for the timeout case and if we limit transfer speed we
       must make sure that this function doesn't transfer anything while in
       HOLD status. */

    switch (Curl_socket_ready(fd_read, fd_write, 1000)) {
    case -1: /* select() error, stop reading */
#ifdef EINTR
      /* The EINTR is not serious, and it seems you might get this more
         ofen when using the lib in a multi-threaded environment! */
      if(SOCKERRNO == EINTR)
        ;
      else
#endif
        done = TRUE; /* no more read or write */
      continue;
    case 0:  /* timeout */
    default: /* readable descriptors */

      result = Curl_readwrite(conn, &done);
      break;
    }
    if(result)
      return result;

    /* "done" signals to us if the transfer(s) are ready */
  }

  return CURLE_OK;
}