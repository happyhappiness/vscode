static CURLcode singleipconnect(struct connectdata *conn,
                                const Curl_addrinfo *ai,
                                curl_socket_t *sockp)
{
  struct Curl_sockaddr_ex addr;
  int rc = -1;
  int error = 0;
  bool isconnected = FALSE;
  struct Curl_easy *data = conn->data;
  curl_socket_t sockfd;
  CURLcode result;
  char ipaddress[MAX_IPADR_LEN];
  long port;
  bool is_tcp;

  *sockp = CURL_SOCKET_BAD;

  result = Curl_socket(conn, ai, &addr, &sockfd);
  if(result)
    /* Failed to create the socket, but still return OK since we signal the
       lack of socket as well. This allows the parent function to keep looping
       over alternative addresses/socket families etc. */
    return CURLE_OK;

  /* store remote address and port used in this connection attempt */
  if(!getaddressinfo((struct sockaddr*)&addr.sa_addr,
                     ipaddress, &port)) {
    /* malformed address or bug in inet_ntop, try next address */
    failf(data, "sa_addr inet_ntop() failed with errno %d: %s",
          errno, Curl_strerror(conn, errno));
    Curl_closesocket(conn, sockfd);
    return CURLE_OK;
  }
  infof(data, "  Trying %s...\n", ipaddress);

#ifdef ENABLE_IPV6
  is_tcp = (addr.family == AF_INET || addr.family == AF_INET6) &&
    addr.socktype == SOCK_STREAM;
#else
  is_tcp = (addr.family == AF_INET) && addr.socktype == SOCK_STREAM;
#endif
  if(is_tcp && data->set.tcp_nodelay)
    Curl_tcpnodelay(conn, sockfd);

  nosigpipe(conn, sockfd);

  Curl_sndbufset(sockfd);

  if(is_tcp && data->set.tcp_keepalive)
    tcpkeepalive(data, sockfd);

  if(data->set.fsockopt) {
    /* activate callback for setting socket options */
    error = data->set.fsockopt(data->set.sockopt_client,
                               sockfd,
                               CURLSOCKTYPE_IPCXN);

    if(error == CURL_SOCKOPT_ALREADY_CONNECTED)
      isconnected = TRUE;
    else if(error) {
      Curl_closesocket(conn, sockfd); /* close the socket and bail out */
      return CURLE_ABORTED_BY_CALLBACK;
    }
  }

  /* possibly bind the local end to an IP, interface or port */
  if(addr.family == AF_INET
#ifdef ENABLE_IPV6
     || addr.family == AF_INET6
#endif
    ) {
    result = bindlocal(conn, sockfd, addr.family,
                       Curl_ipv6_scope((struct sockaddr*)&addr.sa_addr));
    if(result) {
      Curl_closesocket(conn, sockfd); /* close socket and bail out */
      if(result == CURLE_UNSUPPORTED_PROTOCOL) {
        /* The address family is not supported on this interface.
           We can continue trying addresses */
        return CURLE_COULDNT_CONNECT;
      }
      return result;
    }
  }

  /* set socket non-blocking */
  (void)curlx_nonblock(sockfd, TRUE);

  conn->connecttime = Curl_tvnow();
  if(conn->num_addr > 1)
    Curl_expire(data, conn->timeoutms_per_addr, EXPIRE_DNS_PER_NAME);

  /* Connect TCP sockets, bind UDP */
  if(!isconnected && (conn->socktype == SOCK_STREAM)) {
    if(conn->bits.tcp_fastopen) {
#if defined(CONNECT_DATA_IDEMPOTENT) /* OS X */
#ifdef HAVE_BUILTIN_AVAILABLE
      if(__builtin_available(macOS 10.11, iOS 9.0, tvOS 9.0, watchOS 2.0, *)) {
#endif /* HAVE_BUILTIN_AVAILABLE */
        sa_endpoints_t endpoints;
        endpoints.sae_srcif = 0;
        endpoints.sae_srcaddr = NULL;
        endpoints.sae_srcaddrlen = 0;
        endpoints.sae_dstaddr = &addr.sa_addr;
        endpoints.sae_dstaddrlen = addr.addrlen;

        rc = connectx(sockfd, &endpoints, SAE_ASSOCID_ANY,
                      CONNECT_RESUME_ON_READ_WRITE | CONNECT_DATA_IDEMPOTENT,
                      NULL, 0, NULL, NULL);
#ifdef HAVE_BUILTIN_AVAILABLE
      }
      else {
        rc = connect(sockfd, &addr.sa_addr, addr.addrlen);
      }
#endif /* HAVE_BUILTIN_AVAILABLE */
#elif defined(MSG_FASTOPEN) /* Linux */
      if(conn->given->flags & PROTOPT_SSL)
        rc = connect(sockfd, &addr.sa_addr, addr.addrlen);
      else
        rc = 0; /* Do nothing */
#endif
    }
    else {
      rc = connect(sockfd, &addr.sa_addr, addr.addrlen);
    }

    if(-1 == rc)
      error = SOCKERRNO;
  }
  else {
    *sockp = sockfd;
    return CURLE_OK;
  }

#ifdef ENABLE_IPV6
  conn->bits.ipv6 = (addr.family == AF_INET6)?TRUE:FALSE;
#endif

  if(-1 == rc) {
    switch(error) {
    case EINPROGRESS:
    case EWOULDBLOCK:
#if defined(EAGAIN)
#if (EAGAIN) != (EWOULDBLOCK)
      /* On some platforms EAGAIN and EWOULDBLOCK are the
       * same value, and on others they are different, hence
       * the odd #if
       */
    case EAGAIN:
#endif
#endif
      result = CURLE_OK;
      break;

    default:
      /* unknown error, fallthrough and try another address! */
      infof(data, "Immediate connect fail for %s: %s\n",
            ipaddress, Curl_strerror(conn, error));
      data->state.os_errno = error;

      /* connect failed */
      Curl_closesocket(conn, sockfd);
      result = CURLE_COULDNT_CONNECT;
    }
  }

  if(!result)
    *sockp = sockfd;

  return result;
}