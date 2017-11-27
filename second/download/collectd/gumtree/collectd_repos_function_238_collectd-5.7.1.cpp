static int dpdk_re_init_shm() {
  dpdk_config_t temp_config;
  memcpy(&temp_config, g_configuration, sizeof(dpdk_config_t));
  DEBUG("dpdkstat: %s: ports %" PRIu32 ", xstats %" PRIu32, __func__,
        temp_config.num_ports, temp_config.num_xstats);

  size_t shm_xstats_size =
      sizeof(dpdk_config_t) +
      (DPDK_STATS_CTX_GET_XSTAT_SIZE * g_configuration->num_xstats);
  DEBUG("=== SHM new size for %" PRIu32 " xstats", g_configuration->num_xstats);

  int err = dpdk_shm_cleanup();
  if (err) {
    ERROR("dpdkstat: Error in shm_cleanup in %s", __func__);
    return err;
  }
  err = dpdk_shm_init(shm_xstats_size);
  if (err) {
    WARNING("dpdkstat: Error in shm_init in %s", __func__);
    return err;
  }
  /* If the XML config() function has been run, don't re-initialize defaults */
  if (!g_configured)
    dpdk_config_init_default();

  memcpy(g_configuration, &temp_config, sizeof(dpdk_config_t));
  g_configuration->collectd_reinit_shm = 0;
  g_configuration->raw_data = (char *)(g_configuration + 1);
  DPDK_STATS_CTX_INIT(g_configuration);
  return 0;
}