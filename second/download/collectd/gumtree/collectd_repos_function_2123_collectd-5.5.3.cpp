void lcc_network_destroy (lcc_network_t *net) /* {{{ */
{
  if (net == NULL)
    return;
  int_server_destroy (net->servers);
  free (net);
}