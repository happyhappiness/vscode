lcc_network_t *lcc_network_create (void) /* {{{ */
{
  lcc_network_t *net;

  net = malloc (sizeof (*net));
  if (net == NULL)
    return (NULL);
  memset (net, 0, sizeof (*net));

  net->servers = NULL;

  return (net);
}