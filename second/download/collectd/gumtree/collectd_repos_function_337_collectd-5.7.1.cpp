void module_register(void) {
  plugin_register_init(RDT_PLUGIN, rdt_init);
  plugin_register_complex_config(RDT_PLUGIN, rdt_config);
  plugin_register_complex_read(NULL, RDT_PLUGIN, rdt_read, 0, NULL);
  plugin_register_shutdown(RDT_PLUGIN, rdt_shutdown);
}