static int mb_config_set_host_address (mb_host_t *host, /* {{{ */
    const char *address)
{
  struct addrinfo *ai_list;
  struct addrinfo *ai_ptr;
  struct addrinfo  ai_hints;
  int status;

  if ((host == NULL) || (address == NULL))
    return (EINVAL);

  memset (&ai_hints, 0, sizeof (ai_hints));
#if AI_ADDRCONFIG
  ai_hints.ai_flags |= AI_ADDRCONFIG;
#endif
  /* XXX: libmodbus can only handle IPv4 addresses. */
  ai_hints.ai_family = AF_INET;
  ai_hints.ai_addr = NULL;
  ai_hints.ai_canonname = NULL;
  ai_hints.ai_next = NULL;

  ai_list = NULL;
  status = getaddrinfo (address, /* service = */ NULL,
      &ai_hints, &ai_list);
  if (status != 0)
  {
    char errbuf[1024];
    ERROR ("Modbus plugin: getaddrinfo failed: %s",
        (status == EAI_SYSTEM)
        ? sstrerror (errno, errbuf, sizeof (errbuf))
        : gai_strerror (status));
    return (status);
  }

  for (ai_ptr = ai_list; ai_ptr != NULL; ai_ptr = ai_ptr->ai_next)
  {
    status = getnameinfo (ai_ptr->ai_addr, ai_ptr->ai_addrlen,
        host->node, sizeof (host->node),
        /* service = */ NULL, /* length = */ 0,
        /* flags = */ NI_NUMERICHOST);
    if (status == 0)
      break;
  } /* for (ai_ptr) */

  freeaddrinfo (ai_list);

  if (status != 0)
    ERROR ("Modbus plugin: Unable to translate node name: \"%s\"", address);
  else /* if (status == 0) */
  {
    DEBUG ("Modbus plugin: mb_config_set_host_address: %s -> %s",
        address, host->node);
  }

  return (status);
}