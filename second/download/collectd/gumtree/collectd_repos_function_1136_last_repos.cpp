static int cna_query_wafl(host_config_t *host) /* {{{ */
{
  na_elem_t *data;
  int status;
  cdtime_t now;

  if (host == NULL)
    return EINVAL;

  /* If WAFL was not configured, return without doing anything. */
  if (host->cfg_wafl == NULL)
    return 0;

  now = cdtime();
  if ((host->cfg_wafl->interval.interval + host->cfg_wafl->interval.last_read) >
      now)
    return 0;

  status = cna_setup_wafl(host->cfg_wafl);
  if (status != 0)
    return status;
  assert(host->cfg_wafl->query != NULL);

  data = na_server_invoke_elem(host->srv, host->cfg_wafl->query);
  if (na_results_status(data) != NA_OK) {
    ERROR("netapp plugin: cna_query_wafl: na_server_invoke_elem failed for "
          "host %s: %s",
          host->name, na_results_reason(data));
    na_elem_free(data);
    return -1;
  }

  status = cna_handle_wafl_data(host->name, host->cfg_wafl, data,
                                host->cfg_wafl->interval.interval);

  if (status == 0)
    host->cfg_wafl->interval.last_read = now;

  na_elem_free(data);
  return status;
}