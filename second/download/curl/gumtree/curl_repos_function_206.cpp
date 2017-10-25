CURLcode Curl_is_connected(struct connectdata *conn,
                           int sockindex,
                           bool *connected)
{
  int rc;
  struct SessionHandle *data = conn->data;
  CURLcode code = CURLE_OK;
  curl_socket_t sockfd = conn->sock[sockindex];
  long allow = DEFAULT_CONNECT_TIMEOUT;
  long has_passed;

  curlassert(sockindex >= FIRSTSOCKET && sockindex <= SECONDARYSOCKET);

  *connected = FALSE; /* a very negative world view is best */

  /* Evaluate in milliseconds how much time that has passed */
  has_passed = Curl_tvdiff(Curl_tvnow(), data->progress.t_startsingle);

  /* subtract the most strict timeout of the ones */
  if(data->set.timeout && data->set.connecttimeout) {
    if (data->set.timeout < data->set.connecttimeout)
      allow = data->set.timeout*1000;
    else
      allow = data->set.connecttimeout*1000;
  }
  else if(data->set.timeout) {
    allow = data->set.timeout*1000;
  }
  else if(data->set.connecttimeout) {
    allow = data->set.connecttimeout*1000;
  }

  if(has_passed > allow ) {
    /* time-out, bail out, go home */
    failf(data, "Connection time-out after %ld ms", has_passed);
    return CURLE_OPERATION_TIMEOUTED;
  }
  if(conn->bits.tcpconnect) {
    /* we are connected already! */
    *connected = TRUE;
    return CURLE_OK;
  }

  /* check for connect without timeout as we want to return immediately */
  rc = waitconnect(sockfd, 0);

  if(WAITCONN_CONNECTED == rc) {
    int error;
    if (verifyconnect(sockfd, &error)) {
      /* we are connected, awesome! */
      *connected = TRUE;
      return CURLE_OK;
    }
    /* nope, not connected for real */
    data->state.os_errno = error;
    infof(data, "Connection failed\n");
    if(trynextip(conn, sockindex, connected)) {
      code = CURLE_COULDNT_CONNECT;
    }
  }
  else if(WAITCONN_TIMEOUT != rc) {
    int error = 0;

    /* nope, not connected  */
    if (WAITCONN_FDSET_ERROR == rc) {
      verifyconnect(sockfd, &error);
      data->state.os_errno = error;
      infof(data, "%s\n",Curl_strerror(conn,error));
    }
    else
      infof(data, "Connection failed\n");

    if(trynextip(conn, sockindex, connected)) {
      error = Curl_ourerrno();
      data->state.os_errno = error;
      failf(data, "Failed connect to %s:%d; %s",
            conn->host.name, conn->port, Curl_strerror(conn,error));
      code = CURLE_COULDNT_CONNECT;
    }
  }
  /*
   * If the connection failed here, we should attempt to connect to the "next
   * address" for the given host.
   */

  return code;
}