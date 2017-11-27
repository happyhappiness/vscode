static void dpdk_events_default_config(void) {
  dpdk_events_ctx_t *ec = DPDK_EVENTS_CTX_GET(g_hc);

  ec->config.interval = plugin_get_interval();

  /* In configless mode when no <Plugin/> section is defined in config file
   * both link_status and keep_alive should be enabled */

  /* Link Status */
  ec->config.link_status.enabled = 1;
  ec->config.link_status.enabled_port_mask = ~0;
  ec->config.link_status.send_updated = 1;
  ec->config.link_status.notify = 0;

  for (int i = 0; i < RTE_MAX_ETHPORTS; i++) {
    ec->config.link_status.port_name[i][0] = 0;
  }

  /* Keep Alive */
  ec->config.keep_alive.enabled = 1;
  ec->config.keep_alive.send_updated = 1;
  ec->config.keep_alive.notify = 0;
  /* by default enable 128 cores */
  memset(&ec->config.keep_alive.lcore_mask, 1,
         sizeof(ec->config.keep_alive.lcore_mask));
  memset(&ec->config.keep_alive.shm_name, 0,
         sizeof(ec->config.keep_alive.shm_name));
  ec->config.keep_alive.shm = MAP_FAILED;
  ec->config.keep_alive.fd = -1;
}