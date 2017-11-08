CURLcode Curl_readwrite_init(struct connectdata *conn)
{
  struct SessionHandle *data = conn->data;
  struct Curl_transfer_keeper *k = &conn->keep;

  /* NB: the content encoding software depends on this initialization of
     Curl_transfer_keeper. */
  memset(k, 0, sizeof(struct Curl_transfer_keeper));

  k->start = Curl_tvnow(); /* start time */
  k->now = k->start;   /* current time is now */
  k->header = TRUE; /* assume header */
  k->httpversion = -1; /* unknown at this point */

  data = conn->data; /* there's the root struct */
  k->buf = data->state.buffer;
  k->uploadbuf = data->state.uploadbuffer;
  k->maxfd = (conn->sockfd>conn->writesockfd?
              conn->sockfd:conn->writesockfd)+1;
  k->hbufp = data->state.headerbuff;
  k->ignorebody=FALSE;

  Curl_pgrsTime(data, TIMER_PRETRANSFER);
  Curl_speedinit(data);

  Curl_pgrsSetUploadCounter(data, 0);
  Curl_pgrsSetDownloadCounter(data, 0);

  if (!conn->bits.getheader) {
    k->header = FALSE;
    if(conn->size > 0)
      Curl_pgrsSetDownloadSize(data, conn->size);
  }
  /* we want header and/or body, if neither then don't do this! */
  if(conn->bits.getheader || !conn->bits.no_body) {

    if(conn->sockfd != CURL_SOCKET_BAD) {
      k->keepon |= KEEP_READ;
    }

    if(conn->writesockfd != CURL_SOCKET_BAD) {
      /* HTTP 1.1 magic:

         Even if we require a 100-return code before uploading data, we might
         need to write data before that since the REQUEST may not have been
         finished sent off just yet.

         Thus, we must check if the request has been sent before we set the
         state info where we wait for the 100-return code
      */
      if (data->set.expect100header &&
          (conn->proto.http->sending == HTTPSEND_BODY)) {
        /* wait with write until we either got 100-continue or a timeout */
        k->write_after_100_header = TRUE;
        k->start100 = k->start;
      }
      else {
        if(data->set.expect100header)
          /* when we've sent off the rest of the headers, we must await a
             100-continue */
          k->wait100_after_headers = TRUE;
        k->keepon |= KEEP_WRITE;
      }
    }
  }

  return CURLE_OK;
}