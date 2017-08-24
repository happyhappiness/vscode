((flags & UV_UDP_IPV6ONLY) && addr->sa_family != AF_INET6) {
    /* UV_UDP_IPV6ONLY is supported only for IPV6 sockets */
    return ERROR_INVALID_PARAMETER;
  }