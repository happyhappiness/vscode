static int memcached_connect_inet(memcached_t *st) {
  const char *host;
  const char *port;

  struct addrinfo *ai_list;
  int status;
  int fd = -1;

  host = (st->host != NULL) ? st->host : MEMCACHED_DEF_HOST;
  port = (st->port != NULL) ? st->port : MEMCACHED_DEF_PORT;

  struct addrinfo ai_hints = {.ai_family = AF_UNSPEC,
                              .ai_flags = AI_ADDRCONFIG,
                              .ai_socktype = SOCK_STREAM};

  status = getaddrinfo(host, port, &ai_hints, &ai_list);
  if (status != 0) {
    char errbuf[1024];
    ERROR("memcached plugin: memcached_connect_inet: "
          "getaddrinfo(%s,%s) failed: %s",
          host, port,
          (status == EAI_SYSTEM) ? sstrerror(errno, errbuf, sizeof(errbuf))
                                 : gai_strerror(status));
    return (-1);
  }

  for (struct addrinfo *ai_ptr = ai_list; ai_ptr != NULL;
       ai_ptr = ai_ptr->ai_next) {
    /* create our socket descriptor */
    fd = socket(ai_ptr->ai_family, ai_ptr->ai_socktype, ai_ptr->ai_protocol);
    if (fd < 0) {
      char errbuf[1024];
      WARNING("memcached plugin: memcached_connect_inet: "
              "socket(2) failed: %s",
              sstrerror(errno, errbuf, sizeof(errbuf)));
      continue;
    }

    /* connect to the memcached daemon */
    status = (int)connect(fd, ai_ptr->ai_addr, ai_ptr->ai_addrlen);
    if (status != 0) {
      shutdown(fd, SHUT_RDWR);
      close(fd);
      fd = -1;
      continue;
    }

    /* A socket could be opened and connecting succeeded. We're done. */
    break;
  }

  freeaddrinfo(ai_list);
  return (fd);
}