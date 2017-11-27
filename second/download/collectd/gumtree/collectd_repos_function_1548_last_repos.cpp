static int prom_open_socket(int addrfamily) {
  /* {{{ */
  char service[NI_MAXSERV];
  snprintf(service, sizeof(service), "%hu", httpd_port);

  struct addrinfo *res;
  int status = getaddrinfo(NULL, service,
                           &(struct addrinfo){
                               .ai_flags = AI_PASSIVE | AI_ADDRCONFIG,
                               .ai_family = addrfamily,
                               .ai_socktype = SOCK_STREAM,
                           },
                           &res);
  if (status != 0) {
    return -1;
  }

  int fd = -1;
  for (struct addrinfo *ai = res; ai != NULL; ai = ai->ai_next) {
    fd = socket(ai->ai_family, ai->ai_socktype | SOCK_CLOEXEC, 0);
    if (fd == -1)
      continue;

    if (bind(fd, ai->ai_addr, ai->ai_addrlen) != 0) {
      close(fd);
      fd = -1;
      continue;
    }

    if (listen(fd, /* backlog = */ 16) != 0) {
      close(fd);
      fd = -1;
      continue;
    }

    break;
  }

  freeaddrinfo(res);

  return fd;
}