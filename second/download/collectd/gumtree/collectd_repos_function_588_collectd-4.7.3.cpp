static int powerdns_get_data_dgram (list_item_t *item, /* {{{ */
    char **ret_buffer,
    size_t *ret_buffer_size)
{
  int sd;
  int status;

  char temp[4096];
  char *buffer = NULL;
  size_t buffer_size = 0;

  struct sockaddr_un sa_unix;

  sd = socket (PF_UNIX, item->socktype, 0);
  if (sd < 0)
  {
    FUNC_ERROR ("socket");
    return (-1);
  }

  memset (&sa_unix, 0, sizeof (sa_unix));
  sa_unix.sun_family = AF_UNIX;
  sstrncpy (sa_unix.sun_path,
      (local_sockpath != NULL) ? local_sockpath : PDNS_LOCAL_SOCKPATH,
      sizeof (sa_unix.sun_path));

  status = unlink (sa_unix.sun_path);
  if ((status != 0) && (errno != ENOENT))
  {
    FUNC_ERROR ("unlink");
    close (sd);
    return (-1);
  }

  do /* while (0) */
  {
    /* We need to bind to a specific path, because this is a datagram socket
     * and otherwise the daemon cannot answer. */
    status = bind (sd, (struct sockaddr *) &sa_unix, sizeof (sa_unix));
    if (status != 0)
    {
      FUNC_ERROR ("bind");
      break;
    }

    /* Make the socket writeable by the daemon.. */
    status = chmod (sa_unix.sun_path, 0666);
    if (status != 0)
    {
      FUNC_ERROR ("chmod");
      break;
    }

    struct timeval timeout;
    timeout.tv_sec=2;
    if (timeout.tv_sec < interval_g * 3 / 4)
      timeout.tv_sec = interval_g * 3 / 4;
    timeout.tv_usec=0;
    status = setsockopt (sd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof (timeout));
    if (status != 0)
    {
      FUNC_ERROR ("setsockopt");
      break;
    }

    status = connect (sd, (struct sockaddr *) &item->sockaddr,
        sizeof (item->sockaddr));
    if (status != 0)
    {
      FUNC_ERROR ("connect");
      break;
    }

    status = send (sd, item->command, strlen (item->command), 0);
    if (status < 0)
    {
      FUNC_ERROR ("send");
      break;
    }

    status = recv (sd, temp, sizeof (temp), /* flags = */ 0);
    if (status < 0)
    {
      FUNC_ERROR ("recv");
      break;
    }
    buffer_size = status + 1;
    status = 0;
  } while (0);

  close (sd);
  unlink (sa_unix.sun_path);

  if (status != 0)
    return (-1);

  assert (buffer_size > 0);
  buffer = (char *) malloc (buffer_size);
  if (buffer == NULL)
  {
    FUNC_ERROR ("malloc");
    return (-1);
  }

  memcpy (buffer, temp, buffer_size - 1);
  buffer[buffer_size - 1] = 0;

  *ret_buffer = buffer;
  *ret_buffer_size = buffer_size;

  return (0);
}