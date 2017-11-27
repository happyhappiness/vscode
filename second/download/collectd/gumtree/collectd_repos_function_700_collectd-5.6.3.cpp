void module_register(void) {
  plugin_register_complex_config("processes", ps_config);
  plugin_register_init("processes", ps_init);
  plugin_register_read("processes", ps_read);
}