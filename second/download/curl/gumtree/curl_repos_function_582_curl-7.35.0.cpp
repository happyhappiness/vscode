static curl_socket_t connect_to(const char *ipaddr, unsigned short port)
{
  srvr_sockaddr_union_t serveraddr;
  curl_socket_t serverfd;
  int error;
  int rc;
  const char *op_br = "";
  const char *cl_br = "";
#ifdef TCP_NODELAY
  curl_socklen_t flag;
#endif

#ifdef ENABLE_IPV6
  if(use_ipv6) {
    op_br = "[";
    cl_br = "]";
  }
#endif

  if(!ipaddr)
    return CURL_SOCKET_BAD;

  logmsg("about to connect to %s%s%s:%hu",
         op_br, ipaddr, cl_br, port);

#ifdef ENABLE_IPV6
  if(!use_ipv6)
#endif
    serverfd = socket(AF_INET, SOCK_STREAM, 0);
#ifdef ENABLE_IPV6
  else
    serverfd = socket(AF_INET6, SOCK_STREAM, 0);
#endif
  if(CURL_SOCKET_BAD == serverfd) {
    error = SOCKERRNO;
    logmsg("Error creating socket for server conection: (%d) %s",
           error, strerror(error));
    return CURL_SOCKET_BAD;
  }

#ifdef TCP_NODELAY
  /* Disable the Nagle algorithm */
  flag = 1;
  if(0 != setsockopt(serverfd, IPPROTO_TCP, TCP_NODELAY,
                     (void *)&flag, sizeof(flag)))
    logmsg("====> TCP_NODELAY for server conection failed");
  else
    logmsg("TCP_NODELAY set for server conection");
#endif

#ifdef ENABLE_IPV6
  if(!use_ipv6) {
#endif
    memset(&serveraddr.sa4, 0, sizeof(serveraddr.sa4));
    serveraddr.sa4.sin_family = AF_INET;
    serveraddr.sa4.sin_port = htons(port);
    if(Curl_inet_pton(AF_INET, ipaddr, &serveraddr.sa4.sin_addr) < 1) {
      logmsg("Error inet_pton failed AF_INET conversion of '%s'", ipaddr);
      sclose(serverfd);
      return CURL_SOCKET_BAD;
    }

    rc = connect(serverfd, &serveraddr.sa, sizeof(serveraddr.sa4));
#ifdef ENABLE_IPV6
  }
  else {
    memset(&serveraddr.sa6, 0, sizeof(serveraddr.sa6));
    serveraddr.sa6.sin6_family = AF_INET6;
    serveraddr.sa6.sin6_port = htons(port);
    if(Curl_inet_pton(AF_INET6, ipaddr, &serveraddr.sa6.sin6_addr) < 1) {
      logmsg("Error inet_pton failed AF_INET6 conversion of '%s'", ipaddr);
      sclose(serverfd);
      return CURL_SOCKET_BAD;
    }

    rc = connect(serverfd, &serveraddr.sa, sizeof(serveraddr.sa6));
  }
#endif /* ENABLE_IPV6 */

  if(got_exit_signal) {
    sclose(serverfd);
    return CURL_SOCKET_BAD;
  }

  if(rc) {
    error = SOCKERRNO;
    logmsg("Error connecting to server port %hu: (%d) %s",
           port, error, strerror(error));
    sclose(serverfd);
    return CURL_SOCKET_BAD;
  }

  logmsg("connected fine to %s%s%s:%hu, now tunnel",
         op_br, ipaddr, cl_br, port);

  return serverfd;
}