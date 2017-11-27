static int mb_config_set_host_address(mb_host_t *host, /* {{{ */
                                      const char *address) {
  struct addrinfo *ai_list;
  int status;

  if ((host == NULL) || (address == NULL))
    return EINVAL;

  struct addrinfo ai_hints = {
      /* XXX: libmodbus can only handle IPv4 addresses. */
      .ai_family = AF_INET,
      .ai_flags = AI_ADDRCONFIG};

  status = getaddrinfo(address, /* service = */ NULL, &ai_hints, &ai_list);
  if (status != 0) {
    char errbuf[1024];
    ERROR("Modbus plugin: getaddrinfo failed: %s",
          (status == EAI_SYSTEM) ? sstrerror(errno, errbuf, sizeof(errbuf))
                                 : gai_strerror(status));
    return status;
  }

  for (struct addrinfo *ai_ptr = ai_list; ai_ptr != NULL;
       ai_ptr = ai_ptr->ai_next) {
    status = getnameinfo(ai_ptr->ai_addr, ai_ptr->ai_addrlen, host->node,
                         sizeof(host->node),
                         /* service = */ NULL, /* length = */ 0,
                         /* flags = */ NI_NUMERICHOST);
    if (status == 0)
      break;
  } /* for (ai_ptr) */

  freeaddrinfo(ai_list);

  if (status != 0)
    ERROR("Modbus plugin: Unable to translate node name: \"%s\"", address);
  else /* if (status == 0) */
  {
    DEBUG("Modbus plugin: mb_config_set_host_address: %s -> %s", address,
          host->node);
  }

  return status;
}