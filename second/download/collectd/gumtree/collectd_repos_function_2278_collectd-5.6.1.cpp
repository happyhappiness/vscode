int lcc_server_set_interface (lcc_server_t *srv, char const *interface) /* {{{ */
{
  unsigned int if_index;
  int status;

  if ((srv == NULL) || (interface == NULL))
    return (EINVAL);

  if_index = if_nametoindex (interface);
  if (if_index == 0)
    return (ENOENT);

  /* IPv4 multicast */
  if (srv->sa->sa_family == AF_INET)
  {
    struct sockaddr_in *addr = (struct sockaddr_in *) srv->sa;

    if (IN_MULTICAST (ntohl (addr->sin_addr.s_addr)))
    {
#if HAVE_STRUCT_IP_MREQN_IMR_IFINDEX
      /* If possible, use the "ip_mreqn" structure which has
       * an "interface index" member. Using the interface
       * index is preferred here, because of its similarity
       * to the way IPv6 handles this. Unfortunately, it
       * appears not to be portable. */
      struct ip_mreqn mreq = {
        .imr_multiaddr.s_addr = addr->sin_addr.s_addr,
        .imr_address.s_addr = ntohl (INADDR_ANY),
        .imr_ifindex = (int) if_index
      };
#else
      struct ip_mreq mreq = {
        .imr_multiaddr.s_addr = addr->sin_addr.s_addr,
        .imr_interface.s_addr = ntohl (INADDR_ANY)
      };
#endif

      status = setsockopt (srv->fd, IPPROTO_IP, IP_MULTICAST_IF,
          &mreq, sizeof (mreq));
      if (status != 0)
        return (status);

      return (0);
    }
  }

  /* IPv6 multicast */
  if (srv->sa->sa_family == AF_INET6)
  {
    struct sockaddr_in6 *addr = (struct sockaddr_in6 *) srv->sa;

    if (IN6_IS_ADDR_MULTICAST (&addr->sin6_addr))
    {
      status = setsockopt (srv->fd, IPPROTO_IPV6, IPV6_MULTICAST_IF,
          &if_index, sizeof (if_index));
      if (status != 0)
        return (status);

      return (0);
    }
  }

  /* else: Not a multicast interface. */
#if defined(SO_BINDTODEVICE)
  status = setsockopt (srv->fd, SOL_SOCKET, SO_BINDTODEVICE, interface,
      (socklen_t) (strlen (interface) + 1));
  if (status != 0)
    return (-1);
#endif

  return (0);
}