static int cna_read_internal(host_config_t *host) { /* {{{ */
  int status;

  status = cna_query_wafl(host);
  if (status != 0)
    return status;

  status = cna_query_disk(host);
  if (status != 0)
    return status;

  status = cna_query_volume_perf(host);
  if (status != 0)
    return status;

  status = cna_query_volume_usage(host);
  if (status != 0)
    return status;

  status = cna_query_quota(host);
  if (status != 0)
    return status;

  status = cna_query_snapvault(host);
  if (status != 0)
    return status;

  status = cna_query_system(host);
  if (status != 0)
    return status;

  return 0;
}