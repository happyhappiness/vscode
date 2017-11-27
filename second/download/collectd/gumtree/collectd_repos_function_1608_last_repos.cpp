static char *hddtemp_query_daemon(void) {
  int fd;
  ssize_t status;

  char *buffer;
  int buffer_size;
  int buffer_fill;
  char *new_buffer;

  const char *host;
  const char *port;

  struct addrinfo *ai_list;
  int ai_return;

  host = hddtemp_host;
  if (host == NULL)
    host = HDDTEMP_DEF_HOST;

  port = hddtemp_port;
  if (strlen(port) == 0)
    port = HDDTEMP_DEF_PORT;

  struct addrinfo ai_hints = {.ai_flags = AI_ADDRCONFIG,
                              .ai_family = AF_UNSPEC,
                              .ai_protocol = IPPROTO_TCP,
                              .ai_socktype = SOCK_STREAM};

  if ((ai_return = getaddrinfo(host, port, &ai_hints, &ai_list)) != 0) {
    char errbuf[1024];
    ERROR("hddtemp plugin: getaddrinfo (%s, %s): %s", host, port,
          (ai_return == EAI_SYSTEM) ? sstrerror(errno, errbuf, sizeof(errbuf))
                                    : gai_strerror(ai_return));
    return NULL;
  }

  fd = -1;
  for (struct addrinfo *ai_ptr = ai_list; ai_ptr != NULL;
       ai_ptr = ai_ptr->ai_next) {
    /* create our socket descriptor */
    fd = socket(ai_ptr->ai_family, ai_ptr->ai_socktype, ai_ptr->ai_protocol);
    if (fd < 0) {
      char errbuf[1024];
      ERROR("hddtemp plugin: socket: %s",
            sstrerror(errno, errbuf, sizeof(errbuf)));
      continue;
    }

    /* connect to the hddtemp daemon */
    if (connect(fd, (struct sockaddr *)ai_ptr->ai_addr, ai_ptr->ai_addrlen)) {
      char errbuf[1024];
      INFO("hddtemp plugin: connect (%s, %s) failed: %s", host, port,
           sstrerror(errno, errbuf, sizeof(errbuf)));
      close(fd);
      fd = -1;
      continue;
    }

    /* A socket could be opened and connecting succeeded. We're
     * done. */
    break;
  }

  freeaddrinfo(ai_list);

  if (fd < 0) {
    ERROR("hddtemp plugin: Could not connect to daemon.");
    return NULL;
  }

  /* receive data from the hddtemp daemon */
  buffer = NULL;
  buffer_size = 0;
  buffer_fill = 0;
  while (1) {
    if ((buffer_size == 0) || (buffer_fill >= buffer_size - 1)) {
      if (buffer_size == 0)
        buffer_size = 1024;
      else
        buffer_size *= 2;
      if (buffer_size > HDDTEMP_MAX_RECV_BUF) {
        WARNING("hddtemp plugin: Message from hddtemp has been "
                "truncated.");
        break;
      }
      new_buffer = realloc(buffer, buffer_size);
      if (new_buffer == NULL) {
        close(fd);
        free(buffer);
        ERROR("hddtemp plugin: Allocation failed.");
        return NULL;
      }
      buffer = new_buffer;
    }
    status = read(fd, buffer + buffer_fill, buffer_size - buffer_fill - 1);
    if (status == 0) {
      break;
    } else if (status == -1) {
      char errbuf[1024];

      if ((errno == EAGAIN) || (errno == EINTR))
        continue;

      ERROR("hddtemp plugin: Error reading from socket: %s",
            sstrerror(errno, errbuf, sizeof(errbuf)));
      close(fd);
      free(buffer);
      return NULL;
    }
    buffer_fill += status;
  }

  if (buffer_fill == 0) {
    WARNING("hddtemp plugin: Peer has unexpectedly shut down "
            "the socket. Buffer: `%s'",
            buffer);
    close(fd);
    free(buffer);
    return NULL;
  }

  assert(buffer_fill < buffer_size);
  buffer[buffer_fill] = '\0';
  close(fd);
  return buffer;
}