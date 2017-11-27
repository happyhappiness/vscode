static int cna_query_volume_usage(host_config_t *host) /* {{{ */
{
  na_elem_t *data;
  int status;
  cdtime_t now;

  if (host == NULL)
    return EINVAL;

  /* If the user did not configure volume_usage statistics, return without
   * doing anything. */
  if (host->cfg_volume_usage == NULL)
    return 0;

  now = cdtime();
  if ((host->cfg_volume_usage->interval.interval +
       host->cfg_volume_usage->interval.last_read) > now)
    return 0;

  status = cna_setup_volume_usage(host->cfg_volume_usage);
  if (status != 0)
    return status;
  assert(host->cfg_volume_usage->query != NULL);

  data = na_server_invoke_elem(host->srv, host->cfg_volume_usage->query);
  if (na_results_status(data) != NA_OK) {
    ERROR("netapp plugin: cna_query_volume_usage: na_server_invoke_elem failed "
          "for host %s: %s",
          host->name, na_results_reason(data));
    na_elem_free(data);
    return -1;
  }

  status = cna_handle_volume_usage_data(host, host->cfg_volume_usage, data);

  if (status == 0)
    host->cfg_volume_usage->interval.last_read = now;

  na_elem_free(data);
  return status;
}