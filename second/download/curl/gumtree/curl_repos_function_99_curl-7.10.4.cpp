CURLcode Curl_is_connected(struct connectdata *conn,
                           int sockfd,
                           bool *connected)
{
  int rc;
  struct SessionHandle *data = conn->data;

  *connected = FALSE; /* a very negative world view is best */

  if(data->set.timeout || data->set.connecttimeout) {
    /* there is a timeout set */

    /* Evaluate in milliseconds how much time that has passed */
    long has_passed = Curl_tvdiff(Curl_tvnow(), data->progress.start);

    /* subtract the most strict timeout of the ones */
    if(data->set.timeout && data->set.connecttimeout) {
      if (data->set.timeout < data->set.connecttimeout)
        has_passed -= data->set.timeout*1000;
      else 
        has_passed -= data->set.connecttimeout*1000;
    }
    else if(data->set.timeout)
      has_passed -= data->set.timeout*1000;
    else
      has_passed -= data->set.connecttimeout*1000;

    if(has_passed > 0 ) {
      /* time-out, bail out, go home */
      failf(data, "Connection time-out");
      return CURLE_OPERATION_TIMEOUTED;
    }
  }
  if(conn->bits.tcpconnect) {
    /* we are connected already! */
    *connected = TRUE;
    return CURLE_OK;
  }

  /* check for connect without timeout as we want to return immediately */
  rc = waitconnect(sockfd, 0);

  if(0 == rc) {
    int err = socketerror(sockfd);
    if ((0 == err) || (EISCONN == err)) {
      /* we are connected, awesome! */
      *connected = TRUE;
      return CURLE_OK;
    }
    /* nope, not connected for real */
    failf(data, "Connection failed, socket error: %d", err);
    return CURLE_COULDNT_CONNECT;
  }
  else if(1 != rc) {
    int error = ourerrno();
    failf(data, "Failed connect to %s:%d, errno: %d",
          conn->hostname, conn->port, error);
    return CURLE_COULDNT_CONNECT;
  }
  /*
   * If the connection phase is "done" here, we should attempt to connect
   * to the "next address" in the Curl_hostaddr structure that we resolved
   * before. But we don't have that struct around anymore and we can't just
   * keep a pointer since the cache might in fact have gotten pruned by the
   * time we want to read this... Alas, we don't do this yet.
   */

  return CURLE_OK;
}