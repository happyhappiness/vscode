int lcc_server_destroy(lcc_network_t *net, lcc_server_t *srv) /* {{{ */
{
  if ((net == NULL) || (srv == NULL))
    return EINVAL;

  if (net->servers == srv) {
    net->servers = srv->next;
    srv->next = NULL;
  } else {
    lcc_server_t *prev = net->servers;

    while ((prev != NULL) && (prev->next != srv))
      prev = prev->next;

    if (prev == NULL)
      return ENOENT;

    prev->next = srv->next;
    srv->next = NULL;
  }

  int_server_destroy(srv);

  return 0;
}