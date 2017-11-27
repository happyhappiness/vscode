void module_register(void) {
  plugin_register_complex_config(MCELOG_PLUGIN, mcelog_config);
  plugin_register_init(MCELOG_PLUGIN, mcelog_init);
  plugin_register_complex_read(NULL, MCELOG_PLUGIN, mcelog_read, 0, NULL);
  plugin_register_shutdown(MCELOG_PLUGIN, mcelog_shutdown);
}