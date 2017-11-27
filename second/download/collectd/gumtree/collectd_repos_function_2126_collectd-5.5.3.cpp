int lcc_server_set_ttl (lcc_server_t *srv, uint8_t ttl) /* {{{ */
{
  if (srv == NULL)
    return (EINVAL);

  srv->ttl = (int) ttl;

  return (0);
}