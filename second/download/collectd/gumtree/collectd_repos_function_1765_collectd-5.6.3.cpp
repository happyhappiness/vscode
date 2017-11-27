static FILE *olsrd_connect(void) /* {{{ */
{
  struct addrinfo *ai_list;
  int ai_return;

  FILE *fh;

  struct addrinfo ai_hints = {.ai_family = AF_UNSPEC,
                              .ai_flags = AI_ADDRCONFIG,
                              .ai_protocol = IPPROTO_TCP,
                              .ai_socktype = SOCK_STREAM};

  ai_return =
      getaddrinfo(olsrd_get_node(), olsrd_get_service(), &ai_hints, &ai_list);
  if (ai_return != 0) {
    ERROR("olsrd plugin: getaddrinfo (%s, %s) failed: %s", olsrd_get_node(),
          olsrd_get_service(), gai_strerror(ai_return));
    return (NULL);
  }

  fh = NULL;
  for (struct addrinfo *ai_ptr = ai_list; ai_ptr != NULL;
       ai_ptr = ai_ptr->ai_next) {
    int fd;
    int status;
    char errbuf[1024];

    fd = socket(ai_ptr->ai_family, ai_ptr->ai_socktype, ai_ptr->ai_protocol);
    if (fd < 0) {
      ERROR("olsrd plugin: socket failed: %s",
            sstrerror(errno, errbuf, sizeof(errbuf)));
      continue;
    }

    status = connect(fd, ai_ptr->ai_addr, ai_ptr->ai_addrlen);
    if (status != 0) {
      ERROR("olsrd plugin: connect failed: %s",
            sstrerror(errno, errbuf, sizeof(errbuf)));
      close(fd);
      continue;
    }

    fh = fdopen(fd, "r+");
    if (fh == NULL) {
      ERROR("olsrd plugin: fdopen failed.");
      close(fd);
      continue;
    }

    break;
  } /* for (ai_ptr) */

  freeaddrinfo(ai_list);

  return (fh);
}