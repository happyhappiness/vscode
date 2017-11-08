static CURLcode
Transfer(struct connectdata *conn)
{
  struct SessionHandle *data = conn->data;
  CURLcode result;
  struct Curl_transfer_keeper *k = &conn->keep;
  bool done=FALSE;

  Curl_readwrite_init(conn);

  if((conn->sockfd == -1) && (conn->writesockfd == -1))
    /* nothing to read, nothing to write, we're already OK! */
    return CURLE_OK;

  /* we want header and/or body, if neither then don't do this! */
  if(!conn->bits.getheader && data->set.no_body)
    return CURLE_OK;

  k->writefdp = &k->writefd; /* store the address of the set */
  k->readfdp = &k->readfd;   /* store the address of the set */

  while (!done) {
    struct timeval interval;
    k->readfd = k->rkeepfd;  /* set these every lap in the loop */
    k->writefd = k->wkeepfd;
    interval.tv_sec = 1;
    interval.tv_usec = 0;

    switch (select (k->maxfd, k->readfdp, k->writefdp, NULL, &interval)) {
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
      result = Curl_readwrite(conn, &done);
      break;

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