static curl_socket_t
singleipconnect(struct connectdata *conn,
                const Curl_addrinfo *ai,
                long timeout_ms,
                bool *connected)
{
  char addr_buf[128];
  int rc;
  int error;
  bool isconnected;
  struct SessionHandle *data = conn->data;
  curl_socket_t sockfd;
  CURLcode res;
  /*
   * Curl_sockaddr_storage, which is basically sockaddr_storage has a space
   * for a largest possible struct sockaddr only. We should add some space for
   * the other fields we are using. Hence the addr_storage size math.
   */
  char addr_storage[sizeof(struct curl_sockaddr)-
                    sizeof(struct sockaddr)+
                    sizeof(struct Curl_sockaddr_storage)];
  struct curl_sockaddr *addr=(struct curl_sockaddr*)&addr_storage;
  const void *iptoprint;

  addr->family=ai->ai_family;
  addr->socktype=conn->socktype;
  addr->protocol=ai->ai_protocol;
  addr->addrlen =
    (ai->ai_addrlen < (socklen_t)sizeof(struct Curl_sockaddr_storage)) ?
     (unsigned int)ai->ai_addrlen : sizeof(struct Curl_sockaddr_storage);
  memcpy(&addr->addr, ai->ai_addr, addr->addrlen);

  /* If set, use opensocket callback to get the socket */
  if(data->set.fopensocket)
    sockfd = data->set.fopensocket(data->set.opensocket_client,
                                   CURLSOCKTYPE_IPCXN, addr);
  else
    sockfd = socket(addr->family, addr->socktype, addr->protocol);
  if(sockfd == CURL_SOCKET_BAD)
    return CURL_SOCKET_BAD;

  *connected = FALSE; /* default is not connected */

  /* FIXME: do we have Curl_printable_address-like with struct sockaddr* as
     argument? */
  iptoprint = &((const struct sockaddr_in*)(&addr->addr))->sin_addr;
#ifdef ENABLE_IPV6
  if(addr->family==AF_INET6)
    iptoprint= &((const struct sockaddr_in6*)(&addr->addr))->sin6_addr;
#endif
  Curl_inet_ntop(addr->family, iptoprint, addr_buf, sizeof(addr_buf));
  infof(data, "  Trying %s... ", addr_buf);

  if(data->set.tcp_nodelay)
    tcpnodelay(conn, sockfd);

  nosigpipe(conn, sockfd);

  if(data->set.fsockopt) {
    /* activate callback for setting socket options */
    error = data->set.fsockopt(data->set.sockopt_client,
                               sockfd,
                               CURLSOCKTYPE_IPCXN);
    if(error) {
      sclose(sockfd); /* close the socket and bail out */
      return CURL_SOCKET_BAD;
    }
  }

  /* possibly bind the local end to an IP, interface or port */
  res = bindlocal(conn, sockfd);
  if(res) {
    sclose(sockfd); /* close socket and bail out */
    return CURL_SOCKET_BAD;
  }

  /* set socket non-blocking */
  Curl_nonblock(sockfd, TRUE);

  /* Connect TCP sockets, bind UDP */
  if(conn->socktype == SOCK_STREAM)
    rc = connect(sockfd, &addr->addr, addr->addrlen);
  else
    rc = 0;

  if(-1 == rc) {
    error = SOCKERRNO;

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

  isconnected = verifyconnect(sockfd, &error);

  if(!rc && isconnected) {
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