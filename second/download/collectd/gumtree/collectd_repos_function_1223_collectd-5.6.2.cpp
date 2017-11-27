static int connect_client(const char *p_hostname, const char *p_service,
                          int p_family, int p_socktype) {
  struct addrinfo *res, *ressave;
  int n, sockfd;

  struct addrinfo ai_hints = {.ai_family = p_family, .ai_socktype = p_socktype};

  n = getaddrinfo(p_hostname, p_service, &ai_hints, &res);

  if (n < 0) {
    ERROR(PLUGIN_NAME ": getaddrinfo error:: [%s]", gai_strerror(n));
    return -1;
  }

  ressave = res;

  sockfd = -1;
  while (res) {
    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    if (!(sockfd < 0)) {
      if (connect(sockfd, res->ai_addr, res->ai_addrlen) == 0) {
        /* Success */
        break;
      }

      close(sockfd);
      sockfd = -1;
    }
    res = res->ai_next;
  }

  freeaddrinfo(ressave);
  return sockfd;
}