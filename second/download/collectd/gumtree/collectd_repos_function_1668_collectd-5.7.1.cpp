static int wrr_disconnect(struct riemann_host *host) /* {{{ */
{
  if (!host->client)
    return (0);

  riemann_client_free(host->client);
  host->client = NULL;

  return (0);
}