static int lcc_open_netsocket (lcc_connection_t *c, /* {{{ */
    const char *addr_orig)
{
  struct addrinfo *ai_res;
  char addr_copy[NI_MAXHOST];
  char *addr;
  char *port;
  int fd;
  int status;

  assert (c != NULL);
  assert (c->fh == NULL);
  assert (addr_orig != NULL);

  strncpy(addr_copy, addr_orig, sizeof(addr_copy));
  addr_copy[sizeof(addr_copy) - 1] = '\0';
  addr = addr_copy;

  port = NULL;
  if (*addr == '[') /* IPv6+port format */
  {
    /* `addr' is something like "[2001:780:104:2:211:24ff:feab:26f8]:12345" */
    addr++;

    port = strchr (addr, ']');
    if (port == NULL)
    {
      LCC_SET_ERRSTR (c, "malformed address: %s", addr_orig);
      return (-1);
    }
    *port = 0;
    port++;

    if (*port == ':')
      port++;
    else if (*port == 0)
      port = NULL;
    else
    {
      LCC_SET_ERRSTR (c, "garbage after address: %s", port);
      return (-1);
    }
  } /* if (*addr = ']') */
  else if (strchr (addr, '.') != NULL) /* Hostname or IPv4 */
  {
    port = strrchr (addr, ':');
    if (port != NULL)
    {
      *port = 0;
      port++;
    }
  }

  struct addrinfo ai_hints = {
    .ai_family = AF_UNSPEC,
    .ai_flags = AI_ADDRCONFIG,
    .ai_socktype = SOCK_STREAM
  };

  status = getaddrinfo (addr,
                        port == NULL ? LCC_DEFAULT_PORT : port,
                        &ai_hints, &ai_res);
  if (status != 0)
  {
    LCC_SET_ERRSTR (c, "getaddrinfo: %s", gai_strerror (status));
    return (-1);
  }

  for (struct addrinfo *ai_ptr = ai_res; ai_ptr != NULL; ai_ptr = ai_ptr->ai_next)
  {
    fd = socket (ai_ptr->ai_family, ai_ptr->ai_socktype, ai_ptr->ai_protocol);
    if (fd < 0)
    {
      status = errno;
      continue;
    }

    status = connect (fd, ai_ptr->ai_addr, ai_ptr->ai_addrlen);
    if (status != 0)
    {
      status = errno;
      close (fd);
      continue;
    }

    c->fh = fdopen (fd, "r+");
    if (c->fh == NULL)
    {
      status = errno;
      close (fd);
      continue;
    }

    assert (status == 0);
    break;
  } /* for (ai_ptr) */

  if (status != 0)
  {
    lcc_set_errno (c, status);
    freeaddrinfo (ai_res);
    return (-1);
  }

  freeaddrinfo (ai_res);
  return (0);
}