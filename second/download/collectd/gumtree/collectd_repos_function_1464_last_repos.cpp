void module_register(void) {
  plugin_register_complex_config(OVS_EVENTS_PLUGIN, ovs_events_plugin_config);
  plugin_register_init(OVS_EVENTS_PLUGIN, ovs_events_plugin_init);
  plugin_register_shutdown(OVS_EVENTS_PLUGIN, ovs_events_plugin_shutdown);
}