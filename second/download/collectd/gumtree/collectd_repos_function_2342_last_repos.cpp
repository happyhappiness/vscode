static int wt_callback_init(struct wt_callback *cb) {
  int status;
  cdtime_t now;

  const char *node = cb->node ? cb->node : WT_DEFAULT_NODE;
  const char *service = cb->service ? cb->service : WT_DEFAULT_SERVICE;

  if (cb->sock_fd > 0)
    return 0;

  now = cdtime();
  if (cb->ai) {
    /* When we are here, we still have the IP in cache.
     * If we have remaining attempts without calling the DNS, we update the
     * last_update date so we keep the info until next time.
     * If there is no more attempts, we need to flush the cache.
     */

    if ((cb->ai_last_update + resolve_interval + cb->next_random_ttl) < now) {
      cb->next_random_ttl = new_random_ttl();
      if (cb->connect_dns_failed_attempts_remaining > 0) {
        /* Warning : this is run under send_lock mutex.
         * This is why we do not use another mutex here.
         * */
        cb->ai_last_update = now;
        cb->connect_dns_failed_attempts_remaining--;
      } else {
        freeaddrinfo(cb->ai);
        cb->ai = NULL;
      }
    }
  }

  if (cb->ai == NULL) {
    if ((cb->ai_last_update + resolve_interval + cb->next_random_ttl) >= now) {
      DEBUG("write_tsdb plugin: too many getaddrinfo(%s, %s) failures", node,
            service);
      return -1;
    }
    cb->ai_last_update = now;
    cb->next_random_ttl = new_random_ttl();

    struct addrinfo ai_hints = {
        .ai_family = AF_UNSPEC,
        .ai_flags = AI_ADDRCONFIG,
        .ai_socktype = SOCK_STREAM,
    };

    status = getaddrinfo(node, service, &ai_hints, &cb->ai);
    if (status != 0) {
      if (cb->ai) {
        freeaddrinfo(cb->ai);
        cb->ai = NULL;
      }
      if (cb->connect_failed_log_enabled) {
        ERROR("write_tsdb plugin: getaddrinfo(%s, %s) failed: %s", node,
              service, gai_strerror(status));
        cb->connect_failed_log_enabled = 0;
      }
      return -1;
    }
  }

  assert(cb->ai != NULL);
  for (struct addrinfo *ai = cb->ai; ai != NULL; ai = ai->ai_next) {
    cb->sock_fd = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
    if (cb->sock_fd < 0)
      continue;

    set_sock_opts(cb->sock_fd);

    status = connect(cb->sock_fd, ai->ai_addr, ai->ai_addrlen);
    if (status != 0) {
      close(cb->sock_fd);
      cb->sock_fd = -1;
      continue;
    }

    break;
  }

  if (cb->sock_fd < 0) {
    char errbuf[1024];
    ERROR("write_tsdb plugin: Connecting to %s:%s failed. "
          "The last error was: %s",
          node, service, sstrerror(errno, errbuf, sizeof(errbuf)));
    return -1;
  }

  if (0 == cb->connect_failed_log_enabled) {
    WARNING("write_tsdb plugin: Connecting to %s:%s succeeded.", node, service);
    cb->connect_failed_log_enabled = 1;
  }
  cb->connect_dns_failed_attempts_remaining = 1;

  wt_reset_buffer(cb);

  return 0;
}