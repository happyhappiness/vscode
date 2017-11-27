static int server_close_socket(lcc_server_t *srv) /* {{{ */
{
  if (srv == NULL)
    return (EINVAL);

  if (srv->fd < 0)
    return (0);

  close(srv->fd);
  srv->fd = -1;
  free(srv->sa);
  srv->sa = NULL;
  srv->sa_len = 0;

  return (0);
}