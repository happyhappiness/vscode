static int server_multicast_join(lcc_listener_t *srv,
                                 struct sockaddr_storage *group, int loop_back,
                                 int ttl) {
  if (group->ss_family == AF_INET) {
    struct sockaddr_in *sa = (struct sockaddr_in *)group;

    int status = setsockopt(srv->conn, IPPROTO_IP, IP_MULTICAST_LOOP,
                            &loop_back, sizeof(loop_back));
    if (status == -1) {
      DEBUG("setsockopt(IP_MULTICAST_LOOP, %d) = %d\n", loop_back, errno);
      return errno;
    }

    status =
        setsockopt(srv->conn, IPPROTO_IP, IP_MULTICAST_TTL, &ttl, sizeof(ttl));
    if (status == -1)
      return errno;

#if HAVE_STRUCT_IP_MREQN_IMR_IFINDEX
    struct ip_mreqn mreq = {
        .imr_address.s_addr = INADDR_ANY,
        .imr_multiaddr.s_addr = sa->sin_addr.s_addr,
        .imr_ifindex = if_nametoindex(srv->interface),
    };
#else
    struct ip_mreq mreq = {
        .imr_multiaddr.s_addr = sa->sin_addr.s_addr,
    };
#endif
    status = setsockopt(srv->conn, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq,
                        sizeof(mreq));
    if (status == -1)
      return errno;
  } else if (group->ss_family == AF_INET6) {
    struct sockaddr_in6 *sa = (struct sockaddr_in6 *)group;

    int status = setsockopt(srv->conn, IPPROTO_IPV6, IPV6_MULTICAST_LOOP,
                            &loop_back, sizeof(loop_back));
    if (status == -1)
      return errno;

    status = setsockopt(srv->conn, IPPROTO_IPV6, IPV6_MULTICAST_HOPS, &ttl,
                        sizeof(ttl));
    if (status == -1)
      return errno;

    struct ipv6_mreq mreq6 = {
        .ipv6mr_interface = if_nametoindex(srv->interface),
    };
    memmove(&mreq6.ipv6mr_multiaddr, &sa->sin6_addr, sizeof(struct in6_addr));

    status = setsockopt(srv->conn, IPPROTO_IPV6, IPV6_JOIN_GROUP, &mreq6,
                        sizeof(mreq6));
    if (status == -1)
      return errno;
  } else {
    return EINVAL;
  }

  return 0;
}