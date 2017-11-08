static curl_socket_t
singleipconnect(struct connectdata *conn,
                Curl_addrinfo *ai,
                long timeout_ms,
                bool *connected)
{
  char addr_buf[128];
  int rc;
  int error;
  bool conected;
  struct SessionHandle *data = conn->data;
  curl_socket_t sockfd = socket(ai->ai_family, ai->ai_socktype,
                                ai->ai_protocol);
  if (sockfd == CURL_SOCKET_BAD)
    return CURL_SOCKET_BAD;

  *connected = FALSE; /* default is not connected */

  Curl_printable_address(ai, addr_buf, sizeof(addr_buf));
  infof(data, "  Trying %s... ", addr_buf);

  if(data->set.tcp_nodelay)
    tcpnodelay(conn, sockfd);

#ifdef SO_NOSIGPIPE
  nosigpipe(conn, sockfd);
#endif
  if(conn->data->set.device) {
    /* user selected to bind the outgoing socket to a specified "device"
       before doing connect */
    CURLcode res = bindlocal(conn, sockfd);
    if(res) {
      sclose(sockfd); /* close socket and bail out */
      return CURL_SOCKET_BAD;
    }
  }

  /* set socket non-blocking */
  Curl_nonblock(sockfd, TRUE);

  rc = connect(sockfd, ai->ai_addr, (socklen_t)ai->ai_addrlen);

  if(-1 == rc) {
    error = Curl_ourerrno();

    switch (error) {
    case EINPROGRESS:
    case EWOULDBLOCK:
#if defined(EAGAIN) && EAGAIN != EWOULDBLOCK
      /* On some platforms EAGAIN and EWOULDBLOCK are the
       * same value, and on others they are different, hence
       * the odd #if
       */
    case EAGAIN:
#endif
      rc = waitconnect(sockfd, timeout_ms);
      break;
    default:
      /* unknown error, fallthrough and try another address! */
      failf(data, "Failed to connect to %s: %s",
            addr_buf, Curl_strerror(conn,error));
      data->state.os_errno = error;
      break;
    }
  }

  /* The 'WAITCONN_TIMEOUT == rc' comes from the waitconnect(), and not from
     connect(). We can be sure of this since connect() cannot return 1. */
  if((WAITCONN_TIMEOUT == rc) &&
     (data->state.used_interface == Curl_if_multi)) {
    /* Timeout when running the multi interface */
    return sockfd;
  }

  conected = verifyconnect(sockfd, &error);

  if(!rc && conected) {
    /* we are connected, awesome! */
    *connected = TRUE; /* this is a true connect */
    infof(data, "connected\n");
    return sockfd;
  }
  else if(WAITCONN_TIMEOUT == rc)
    infof(data, "Timeout\n");
  else {
    data->state.os_errno = error;
    infof(data, "%s\n", Curl_strerror(conn, error));
  }

  /* connect failed or timed out */
  sclose(sockfd);

  return CURL_SOCKET_BAD;
}