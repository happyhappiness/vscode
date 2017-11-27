static int wt_callback_init(struct wt_callback *cb) {
  struct addrinfo *ai_list;
  int status;

  const char *node = cb->node ? cb->node : WT_DEFAULT_NODE;
  const char *service = cb->service ? cb->service : WT_DEFAULT_SERVICE;

  if (cb->sock_fd > 0)
    return 0;

  struct addrinfo ai_hints = {.ai_family = AF_UNSPEC,
                              .ai_flags = AI_ADDRCONFIG,
                              .ai_socktype = SOCK_STREAM};

  status = getaddrinfo(node, service, &ai_hints, &ai_list);
  if (status != 0) {
    ERROR("write_tsdb plugin: getaddrinfo (%s, %s) failed: %s", node, service,
          gai_strerror(status));
    return -1;
  }

  assert(ai_list != NULL);
  for (struct addrinfo *ai_ptr = ai_list; ai_ptr != NULL;
       ai_ptr = ai_ptr->ai_next) {
    cb->sock_fd =
        socket(ai_ptr->ai_family, ai_ptr->ai_socktype, ai_ptr->ai_protocol);
    if (cb->sock_fd < 0)
      continue;

    set_sock_opts(cb->sock_fd);

    status = connect(cb->sock_fd, ai_ptr->ai_addr, ai_ptr->ai_addrlen);
    if (status != 0) {
      close(cb->sock_fd);
      cb->sock_fd = -1;
      continue;
    }

    break;
  }

  freeaddrinfo(ai_list);

  if (cb->sock_fd < 0) {
    char errbuf[1024];
    ERROR("write_tsdb plugin: Connecting to %s:%s failed. "
          "The last error was: %s",
          node, service, sstrerror(errno, errbuf, sizeof(errbuf)));
    return -1;
  }

  wt_reset_buffer(cb);

  return 0;
}