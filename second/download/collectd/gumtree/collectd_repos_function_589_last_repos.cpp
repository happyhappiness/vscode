void module_register(void) {
  plugin_register_init(DPDK_EVENTS_PLUGIN, dpdk_events_init);
  plugin_register_complex_config(DPDK_EVENTS_PLUGIN, dpdk_events_config);
  plugin_register_complex_read(NULL, DPDK_EVENTS_PLUGIN, dpdk_events_read, 0,
                               NULL);
  plugin_register_shutdown(DPDK_EVENTS_PLUGIN, dpdk_events_shutdown);
}