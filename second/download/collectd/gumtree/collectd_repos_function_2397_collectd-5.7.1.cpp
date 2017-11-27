static int server_open_socket(lcc_server_t *srv) /* {{{ */
{
  struct addrinfo *ai_list;
  int status;

  if (srv == NULL)
    return (EINVAL);

  if (srv->fd >= 0)
    server_close_socket(srv);

  struct addrinfo ai_hints = {.ai_family = AF_UNSPEC,
                              .ai_flags = AI_ADDRCONFIG,
                              .ai_socktype = SOCK_DGRAM};

  status = getaddrinfo(srv->node, srv->service, &ai_hints, &ai_list);
  if (status != 0)
    return (status);
  assert(ai_list != NULL);

  for (struct addrinfo *ai_ptr = ai_list; ai_ptr != NULL;
       ai_ptr = ai_ptr->ai_next) {
    srv->fd =
        socket(ai_ptr->ai_family, ai_ptr->ai_socktype, ai_ptr->ai_protocol);
    if (srv->fd < 0)
      continue;

    if (ai_ptr->ai_family == AF_INET) {
      struct sockaddr_in *addr = (struct sockaddr_in *)ai_ptr->ai_addr;
      int optname;

      if (IN_MULTICAST(ntohl(addr->sin_addr.s_addr)))
        optname = IP_MULTICAST_TTL;
      else
        optname = IP_TTL;

      status =
          setsockopt(srv->fd, IPPROTO_IP, optname, &srv->ttl, sizeof(srv->ttl));
    } else if (ai_ptr->ai_family == AF_INET6) {
      /* Useful example:
       * http://gsyc.escet.urjc.es/~eva/IPv6-web/examples/mcast.html */
      struct sockaddr_in6 *addr = (struct sockaddr_in6 *)ai_ptr->ai_addr;
      int optname;

      if (IN6_IS_ADDR_MULTICAST(&addr->sin6_addr))
        optname = IPV6_MULTICAST_HOPS;
      else
        optname = IPV6_UNICAST_HOPS;

      status = setsockopt(srv->fd, IPPROTO_IPV6, optname, &srv->ttl,
                          sizeof(srv->ttl));
    }
    if (status != 0) {
      /* setsockopt failed. */
      close(srv->fd);
      srv->fd = -1;
      continue;
    }

    srv->sa = malloc(ai_ptr->ai_addrlen);
    if (srv->sa == NULL) {
      close(srv->fd);
      srv->fd = -1;
      continue;
    }

    memcpy(srv->sa, ai_ptr->ai_addr, ai_ptr->ai_addrlen);
    srv->sa_len = ai_ptr->ai_addrlen;
    break;
  }

  freeaddrinfo(ai_list);

  if (srv->fd < 0)
    return (-1);
  return (0);
}