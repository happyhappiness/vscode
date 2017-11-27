static host_config_t *cna_alloc_host(void) /* {{{ */
{
  host_config_t *host;

  host = calloc(1, sizeof(*host));
  if (host == NULL)
    return (NULL);

  host->name = NULL;
  host->protocol = NA_SERVER_TRANSPORT_HTTPS;
  host->host = NULL;
  host->username = NULL;
  host->password = NULL;
  host->vfiler = NULL;
  host->srv = NULL;
  host->cfg_wafl = NULL;
  host->cfg_disk = NULL;
  host->cfg_volume_perf = NULL;
  host->cfg_volume_usage = NULL;
  host->cfg_quota = NULL;
  host->cfg_snapvault = NULL;
  host->cfg_system = NULL;

  return (host);
}