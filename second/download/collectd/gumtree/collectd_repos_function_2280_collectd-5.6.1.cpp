int lcc_network_values_send (lcc_network_t *net, /* {{{ */
    const lcc_value_list_t *vl)
{
  if ((net == NULL) || (vl == NULL))
    return (EINVAL);

  for (lcc_server_t *srv = net->servers; srv != NULL; srv = srv->next)
    server_value_add (srv, vl);

  return (0);
}