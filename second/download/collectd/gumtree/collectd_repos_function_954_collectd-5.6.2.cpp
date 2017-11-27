static int zookeeper_connect(void) {
  int sk = -1;
  int status;
  struct addrinfo *ai_list;
  const char *host;
  const char *port;

  host = (zk_host != NULL) ? zk_host : ZOOKEEPER_DEF_HOST;
  port = (zk_port != NULL) ? zk_port : ZOOKEEPER_DEF_PORT;

  struct addrinfo ai_hints = {.ai_family = AF_UNSPEC,
                              .ai_socktype = SOCK_STREAM};

  status = getaddrinfo(host, port, &ai_hints, &ai_list);
  if (status != 0) {
    char errbuf[1024];
    INFO("getaddrinfo failed: %s",
         (status == EAI_SYSTEM) ? sstrerror(errno, errbuf, sizeof(errbuf))
                                : gai_strerror(status));
    return (-1);
  }

  for (struct addrinfo *ai = ai_list; ai != NULL; ai = ai->ai_next) {
    sk = socket(ai->ai_family, SOCK_STREAM, 0);
    if (sk < 0) {
      char errbuf[1024];
      WARNING("zookeeper: socket(2) failed: %s",
              sstrerror(errno, errbuf, sizeof(errbuf)));
      continue;
    }
    status = (int)connect(sk, ai->ai_addr, ai->ai_addrlen);
    if (status != 0) {
      char errbuf[1024];
      close(sk);
      sk = -1;
      WARNING("zookeeper: connect(2) failed: %s",
              sstrerror(errno, errbuf, sizeof(errbuf)));
      continue;
    }

    /* connected */
    break;
  }

  freeaddrinfo(ai_list);
  return (sk);
}