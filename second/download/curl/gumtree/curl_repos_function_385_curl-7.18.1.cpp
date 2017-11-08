CURLcode Curl_is_connected(struct connectdata *conn,
                           int sockindex,
                           bool *connected)
{
  int rc;
  struct SessionHandle *data = conn->data;
  CURLcode code = CURLE_OK;
  curl_socket_t sockfd = conn->sock[sockindex];
  long allow = DEFAULT_CONNECT_TIMEOUT;

  DEBUGASSERT(sockindex >= FIRSTSOCKET && sockindex <= SECONDARYSOCKET);

  *connected = FALSE; /* a very negative world view is best */

  if(conn->bits.tcpconnect) {
    /* we are connected already! */
    long allow_total = 0;

    /* subtract the most strict timeout of the ones */
    if(data->set.timeout)
      allow_total = data->set.timeout;

    Curl_expire(data, allow_total);
    *connected = TRUE;
    return CURLE_OK;
  }

  /* figure out how long time we have left to connect */
  allow = Curl_timeleft(conn, NULL, TRUE);

  if(allow < 0) {
    /* time-out, bail out, go home */
    failf(data, "Connection time-out");
    return CURLE_OPERATION_TIMEDOUT;
  }

  Curl_expire(data, allow);

  /* check for connect without timeout as we want to return immediately */
  rc = waitconnect(sockfd, 0);

  if(WAITCONN_CONNECTED == rc) {
    int error;
    if(verifyconnect(sockfd, &error)) {
      /* we are connected, awesome! */
      *connected = TRUE;
      return CURLE_OK;
    }
    /* nope, not connected for real */
    data->state.os_errno = error;
    infof(data, "Connection failed\n");
    if(trynextip(conn, sockindex, connected)) {
      failf(data, "Failed connect to %s:%d; %s",
            conn->host.name, conn->port, Curl_strerror(conn, error));
      code = CURLE_COULDNT_CONNECT;
    }
  }
  else if(WAITCONN_TIMEOUT != rc) {
    int error = 0;

    /* nope, not connected  */
    if(WAITCONN_FDSET_ERROR == rc) {
      (void)verifyconnect(sockfd, &error);
      data->state.os_errno = error;
      infof(data, "%s\n",Curl_strerror(conn,error));
    }
    else
      infof(data, "Connection failed\n");

    if(trynextip(conn, sockindex, connected)) {
      error = SOCKERRNO;
      data->state.os_errno = error;
      failf(data, "Failed connect to %s:%d; %s",
            conn->host.name, conn->port, Curl_strerror(conn, error));
      code = CURLE_COULDNT_CONNECT;
    }
  }
  /*
   * If the connection failed here, we should attempt to connect to the "next
   * address" for the given host.
   */

  return code;
}