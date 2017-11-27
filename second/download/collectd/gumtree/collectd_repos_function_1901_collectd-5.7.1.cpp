static int ntpd_get_name_from_address(char *buffer, size_t buffer_size,
                                      struct info_peer_summary const *peer_info,
                                      _Bool do_reverse_lookup) {
  struct sockaddr_storage sa = {0};
  socklen_t sa_len;
  int flags = 0;
  int status;

  if (peer_info->v6_flag) {
    struct sockaddr_in6 sa6 = {0};

    assert(sizeof(sa) >= sizeof(sa6));

    sa6.sin6_family = AF_INET6;
    sa6.sin6_port = htons(123);
    memcpy(&sa6.sin6_addr, &peer_info->srcadr6, sizeof(struct in6_addr));
    sa_len = sizeof(sa6);

    memcpy(&sa, &sa6, sizeof(sa6));
  } else {
    struct sockaddr_in sa4 = {0};

    assert(sizeof(sa) >= sizeof(sa4));

    sa4.sin_family = AF_INET;
    sa4.sin_port = htons(123);
    memcpy(&sa4.sin_addr, &peer_info->srcadr, sizeof(struct in_addr));
    sa_len = sizeof(sa4);

    memcpy(&sa, &sa4, sizeof(sa4));
  }

  if (!do_reverse_lookup)
    flags |= NI_NUMERICHOST;

  status = getnameinfo((struct sockaddr const *)&sa, sa_len, buffer,
                       buffer_size, NULL, 0, /* No port name */
                       flags);
  if (status != 0) {
    char errbuf[1024];
    ERROR("ntpd plugin: getnameinfo failed: %s",
          (status == EAI_SYSTEM) ? sstrerror(errno, errbuf, sizeof(errbuf))
                                 : gai_strerror(status));
    return (-1);
  }

  return (0);
}