void module_register(void) {
  plugin_register_complex_config("apache", config);
  plugin_register_init("apache", apache_init);
}