static int cna_query_disk(host_config_t *host) /* {{{ */
{
  na_elem_t *data;
  int status;
  cdtime_t now;

  if (host == NULL)
    return (EINVAL);

  /* If the user did not configure disk statistics, return without doing
   * anything. */
  if (host->cfg_disk == NULL)
    return (0);

  now = cdtime();
  if ((host->cfg_disk->interval.interval + host->cfg_disk->interval.last_read) >
      now)
    return (0);

  status = cna_setup_disk(host->cfg_disk);
  if (status != 0)
    return (status);
  assert(host->cfg_disk->query != NULL);

  data = na_server_invoke_elem(host->srv, host->cfg_disk->query);
  if (na_results_status(data) != NA_OK) {
    ERROR("netapp plugin: cna_query_disk: na_server_invoke_elem failed for "
          "host %s: %s",
          host->name, na_results_reason(data));
    na_elem_free(data);
    return (-1);
  }

  status = cna_handle_disk_data(host->name, host->cfg_disk, data,
                                host->cfg_disk->interval.interval);

  if (status == 0)
    host->cfg_disk->interval.last_read = now;

  na_elem_free(data);
  return (status);
}