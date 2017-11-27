static pinba_socket_t *pinba_socket_open(const char *node, /* {{{ */
                                         const char *service) {
  pinba_socket_t *s;
  struct addrinfo *ai_list;
  int status;

  if (node == NULL)
    node = PINBA_DEFAULT_NODE;

  if (service == NULL)
    service = PINBA_DEFAULT_SERVICE;

  struct addrinfo ai_hints = {.ai_family = AF_UNSPEC,
                              .ai_flags = AI_PASSIVE,
                              .ai_socktype = SOCK_DGRAM};

  status = getaddrinfo(node, service, &ai_hints, &ai_list);
  if (status != 0) {
    ERROR("pinba plugin: getaddrinfo(3) failed: %s", gai_strerror(status));
    return (NULL);
  }
  assert(ai_list != NULL);

  s = calloc(1, sizeof(*s));
  if (s == NULL) {
    freeaddrinfo(ai_list);
    ERROR("pinba plugin: calloc failed.");
    return (NULL);
  }

  for (struct addrinfo *ai_ptr = ai_list; ai_ptr != NULL;
       ai_ptr = ai_ptr->ai_next) {
    status = pb_add_socket(s, ai_ptr);
    if (status != 0)
      break;
  } /* for (ai_list) */

  freeaddrinfo(ai_list);

  if (s->fd_num < 1) {
    WARNING("pinba plugin: Unable to open socket for address %s.", node);
    sfree(s);
    s = NULL;
  }

  return (s);
}