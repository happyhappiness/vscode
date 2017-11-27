static int powerdns_get_data_stream (list_item_t *item, /* {{{ */
    char **ret_buffer,
    size_t *ret_buffer_size)
{
  int sd;
  int status;

  char temp[4096];
  char *buffer = NULL;
  size_t buffer_size = 0;

  sd = socket (PF_UNIX, item->socktype, 0);
  if (sd < 0)
  {
    FUNC_ERROR ("socket");
    return (-1);
  }

  struct timeval timeout;
  timeout.tv_sec=5;
  timeout.tv_usec=0;
  status = setsockopt (sd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof (timeout));
  if (status != 0)
  {
    FUNC_ERROR ("setsockopt");
    close (sd);
    return (-1);
  }

  status = connect (sd, (struct sockaddr *) &item->sockaddr,
      sizeof (item->sockaddr));
  if (status != 0)
  {
    FUNC_ERROR ("connect");
    close (sd);
    return (-1);
  }

  /* strlen + 1, because we need to send the terminating NULL byte, too. */
  status = send (sd, item->command, strlen (item->command) + 1,
      /* flags = */ 0);
  if (status < 0)
  {
    FUNC_ERROR ("send");
    close (sd);
    return (-1);
  }

  while (42)
  {
    char *buffer_new;

    status = recv (sd, temp, sizeof (temp), /* flags = */ 0);
    if (status < 0)
    {
      FUNC_ERROR ("recv");
      break;
    }
    else if (status == 0)
      break;

    buffer_new = realloc (buffer, buffer_size + status + 1);
    if (buffer_new == NULL)
    {
      FUNC_ERROR ("realloc");
      status = -1;
      break;
    }
    buffer = buffer_new;

    memcpy (buffer + buffer_size, temp, status);
    buffer_size += status;
    buffer[buffer_size] = 0;
  } /* while (42) */
  close (sd);

  if (status < 0)
  {
    sfree (buffer);
  }
  else
  {
    assert (status == 0);
    *ret_buffer = buffer;
    *ret_buffer_size = buffer_size;
  }

  return (status);
}