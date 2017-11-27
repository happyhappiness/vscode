static int lcc_open_socket (lcc_connection_t *c, const char *addr) /* {{{ */
{
  int status = 0;

  if (addr == NULL)
    return (-1);

  assert (c != NULL);
  assert (c->fh == NULL);
  assert (addr != NULL);

  if (strncmp ("unix:", addr, strlen ("unix:")) == 0)
    status = lcc_open_unixsocket (c, addr + strlen ("unix:"));
  else if (addr[0] == '/')
    status = lcc_open_unixsocket (c, addr);
  else
    status = lcc_open_netsocket (c, addr);

  return (status);
}