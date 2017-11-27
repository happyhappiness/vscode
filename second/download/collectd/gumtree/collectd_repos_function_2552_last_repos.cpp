lcc_network_t *lcc_network_create(void) /* {{{ */
{
  lcc_network_t *net;

  net = calloc(1, sizeof(*net));
  if (net == NULL)
    return NULL;

  net->servers = NULL;

  return net;
}