static int statsd_network_init(struct pollfd **ret_fds, /* {{{ */
                               size_t *ret_fds_num) {
  struct pollfd *fds = NULL;
  size_t fds_num = 0;

  struct addrinfo *ai_list;
  int status;

  char const *node = (conf_node != NULL) ? conf_node : STATSD_DEFAULT_NODE;
  char const *service =
      (conf_service != NULL) ? conf_service : STATSD_DEFAULT_SERVICE;

  struct addrinfo ai_hints = {.ai_family = AF_UNSPEC,
                              .ai_flags = AI_PASSIVE | AI_ADDRCONFIG,
                              .ai_socktype = SOCK_DGRAM};

  status = getaddrinfo(node, service, &ai_hints, &ai_list);
  if (status != 0) {
    ERROR("statsd plugin: getaddrinfo (\"%s\", \"%s\") failed: %s", node,
          service, gai_strerror(status));
    return status;
  }

  for (struct addrinfo *ai_ptr = ai_list; ai_ptr != NULL;
       ai_ptr = ai_ptr->ai_next) {
    int fd;
    struct pollfd *tmp;

    char dbg_node[NI_MAXHOST];
    char dbg_service[NI_MAXSERV];

    fd = socket(ai_ptr->ai_family, ai_ptr->ai_socktype, ai_ptr->ai_protocol);
    if (fd < 0) {
      char errbuf[1024];
      ERROR("statsd plugin: socket(2) failed: %s",
            sstrerror(errno, errbuf, sizeof(errbuf)));
      continue;
    }

    getnameinfo(ai_ptr->ai_addr, ai_ptr->ai_addrlen, dbg_node, sizeof(dbg_node),
                dbg_service, sizeof(dbg_service),
                NI_DGRAM | NI_NUMERICHOST | NI_NUMERICSERV);
    DEBUG("statsd plugin: Trying to bind to [%s]:%s ...", dbg_node,
          dbg_service);

    status = bind(fd, ai_ptr->ai_addr, ai_ptr->ai_addrlen);
    if (status != 0) {
      char errbuf[1024];
      ERROR("statsd plugin: bind(2) failed: %s",
            sstrerror(errno, errbuf, sizeof(errbuf)));
      close(fd);
      continue;
    }

    tmp = realloc(fds, sizeof(*fds) * (fds_num + 1));
    if (tmp == NULL) {
      ERROR("statsd plugin: realloc failed.");
      close(fd);
      continue;
    }
    fds = tmp;
    tmp = fds + fds_num;
    fds_num++;

    memset(tmp, 0, sizeof(*tmp));
    tmp->fd = fd;
    tmp->events = POLLIN | POLLPRI;
  }

  freeaddrinfo(ai_list);

  if (fds_num == 0) {
    ERROR("statsd plugin: Unable to create listening socket for [%s]:%s.",
          (node != NULL) ? node : "::", service);
    return ENOENT;
  }

  *ret_fds = fds;
  *ret_fds_num = fds_num;
  return 0;
}