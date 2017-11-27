static int ntpd_connect(void) {
  const char *host;
  const char *port;

  struct addrinfo *ai_list;
  int status;

  if (sock_descr >= 0)
    return sock_descr;

  DEBUG("Opening a new socket");

  host = ntpd_host;
  if (host == NULL)
    host = NTPD_DEFAULT_HOST;

  port = ntpd_port;
  if (strlen(port) == 0)
    port = NTPD_DEFAULT_PORT;

  struct addrinfo ai_hints = {.ai_family = AF_UNSPEC,
                              .ai_flags = AI_ADDRCONFIG,
                              .ai_protocol = IPPROTO_UDP,
                              .ai_socktype = SOCK_DGRAM};

  if ((status = getaddrinfo(host, port, &ai_hints, &ai_list)) != 0) {
    char errbuf[1024];
    ERROR("ntpd plugin: getaddrinfo (%s, %s): %s", host, port,
          (status == EAI_SYSTEM) ? sstrerror(errno, errbuf, sizeof(errbuf))
                                 : gai_strerror(status));
    return -1;
  }

  for (struct addrinfo *ai_ptr = ai_list; ai_ptr != NULL;
       ai_ptr = ai_ptr->ai_next) {
    /* create our socket descriptor */
    if ((sock_descr = socket(ai_ptr->ai_family, ai_ptr->ai_socktype,
                             ai_ptr->ai_protocol)) < 0)
      continue;

    /* connect to the ntpd */
    if (connect(sock_descr, ai_ptr->ai_addr, ai_ptr->ai_addrlen)) {
      close(sock_descr);
      sock_descr = -1;
      continue;
    }

    break;
  }

  freeaddrinfo(ai_list);

  if (sock_descr < 0) {
    ERROR("ntpd plugin: Unable to connect to server.");
  }

  return sock_descr;
}