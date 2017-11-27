void module_register(void) {
  plugin_register_complex_config(plugin_name, ovs_stats_plugin_config);
  plugin_register_init(plugin_name, ovs_stats_plugin_init);
  plugin_register_complex_read(NULL, plugin_name, ovs_stats_plugin_read, 0,
                               NULL);
  plugin_register_shutdown(plugin_name, ovs_stats_plugin_shutdown);
}