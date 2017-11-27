int lcc_connect (const char *address, lcc_connection_t **ret_con) /* {{{ */
{
  lcc_connection_t *c;
  int status;

  if (address == NULL)
    return (-1);

  if (ret_con == NULL)
    return (-1);

  c = (lcc_connection_t *) malloc (sizeof (*c));
  if (c == NULL)
    return (-1);
  memset (c, 0, sizeof (*c));

  status = lcc_open_socket (c, address);
  if (status != 0)
  {
    lcc_disconnect (c);
    return (status);
  }

  *ret_con = c;
  return (0);
}