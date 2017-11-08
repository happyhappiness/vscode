static curl_socket_t sockdaemon(curl_socket_t sock,
                                unsigned short *port)
{
  /* passive daemon style */
  struct sockaddr_in me;
#ifdef ENABLE_IPV6
  struct sockaddr_in6 me6;
#endif /* ENABLE_IPV6 */
  int flag = 1;
  int rc;

  if (setsockopt
      (sock, SOL_SOCKET, SO_REUSEADDR, (const void *) &flag,
       sizeof(int)) < 0) {
    perror("setsockopt(SO_REUSEADDR)");
  }

#ifdef ENABLE_IPV6
  if(!use_ipv6) {
#endif
    me.sin_family = AF_INET;
    me.sin_addr.s_addr = INADDR_ANY;
    me.sin_port = htons(*port);
    rc = bind(sock, (struct sockaddr *) &me, sizeof(me));
#ifdef ENABLE_IPV6
  }
  else {
    memset(&me6, 0, sizeof(struct sockaddr_in6));
    me6.sin6_family = AF_INET6;
    me6.sin6_addr = in6addr_any;
    me6.sin6_port = htons(*port);
    rc = bind(sock, (struct sockaddr *) &me6, sizeof(me6));
  }
#endif /* ENABLE_IPV6 */
  if(rc < 0) {
    perror("binding stream socket");
    logmsg("Error binding socket");
    return CURL_SOCKET_BAD;
  }

  if(!*port) {
    /* The system picked a port number, now figure out which port we actually
       got */
    /* we succeeded to bind */
    struct sockaddr_in add;
    socklen_t socksize = sizeof(add);

    if(getsockname(sock, (struct sockaddr *) &add,
                   &socksize)<0) {
      fprintf(stderr, "getsockname() failed");
      return CURL_SOCKET_BAD;
    }
    *port = ntohs(add.sin_port);
  }

  /* start accepting connections */
  listen(sock, 4);

  return sock;
}