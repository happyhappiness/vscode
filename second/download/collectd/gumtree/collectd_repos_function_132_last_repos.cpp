void module_register(void) {
  plugin_register_init(DPDK_STATS_PLUGIN, dpdk_stats_init);
  plugin_register_complex_config(DPDK_STATS_PLUGIN, dpdk_stats_config);
  plugin_register_complex_read(NULL, DPDK_STATS_PLUGIN, dpdk_stats_read, 0,
                               NULL);
  plugin_register_shutdown(DPDK_STATS_PLUGIN, dpdk_stats_shutdown);
}