static void dpdk_stats_default_config(void) {
  dpdk_stats_ctx_t *ec = DPDK_STATS_CTX_GET(g_hc);

  ec->config.interval = plugin_get_interval();
  for (int i = 0; i < RTE_MAX_ETHPORTS; i++) {
    ec->config.port_name[i][0] = 0;
  }
  /* Enable all ports by default */
  ec->config.enabled_port_mask = ~0;
}