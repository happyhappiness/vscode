static int chrony_read(void) {
  /* collectd read callback: Perform data acquisition */
  int rc;
  unsigned int n_sources;

  if (g_chrony_seq_is_initialized == 0) {
    /* Seed RNG for sequence number generation */
    rc = chrony_init_seq();
    if (rc != CHRONY_RC_OK)
      return rc;

    g_chrony_seq_is_initialized = 1;
  }

  /* Get daemon stats */
  rc = chrony_request_daemon_stats();
  if (rc != CHRONY_RC_OK)
    return rc;

  /* Get number of time sources, then check every source for status */
  rc = chrony_request_sources_count(&n_sources);
  if (rc != CHRONY_RC_OK)
    return rc;

  for (unsigned int now_src = 0; now_src < n_sources; ++now_src) {
    char src_addr[IPV6_STR_MAX_SIZE] = {0};
    int is_reachable;
    rc = chrony_request_source_data(now_src, src_addr, sizeof(src_addr),
                                    &is_reachable);
    if (rc != CHRONY_RC_OK)
      return rc;

    rc = chrony_request_source_stats(now_src, src_addr, &is_reachable);
    if (rc != CHRONY_RC_OK)
      return rc;
  }
  return CHRONY_RC_OK;
}