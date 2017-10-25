static CURLcode
Transfer(struct connectdata *conn)
{
  CURLcode result;
  struct Curl_transfer_keeper *k = &conn->keep;
  bool done=FALSE;

  if(!(conn->protocol & PROT_FILE))
    /* Only do this if we are not transferring FILE:, since the file: treatment
       is different*/
    Curl_readwrite_init(conn);

  if((conn->sockfd == CURL_SOCKET_BAD) &&
     (conn->writesockfd == CURL_SOCKET_BAD))
    /* nothing to read, nothing to write, we're already OK! */
    return CURLE_OK;

  /* we want header and/or body, if neither then don't do this! */
  if(!conn->bits.getheader && conn->bits.no_body)
    return CURLE_OK;

  while (!done) {
    curl_socket_t fd_read;
    curl_socket_t fd_write;
    int interval_ms;

    interval_ms = 1 * 1000;

    if(k->keepon & KEEP_READ)
      fd_read = conn->sockfd;
    else
      fd_read = CURL_SOCKET_BAD;

    if(k->keepon & KEEP_WRITE)
      fd_write = conn->writesockfd;
    else
      fd_write = CURL_SOCKET_BAD;

    switch (Curl_select(fd_read, fd_write, interval_ms)) {
    case -1: /* select() error, stop reading */
#ifdef EINTR
      /* The EINTR is not serious, and it seems you might get this more
         ofen when using the lib in a multi-threaded environment! */
      if(errno == EINTR)
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