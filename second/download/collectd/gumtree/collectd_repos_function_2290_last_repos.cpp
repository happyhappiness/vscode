void module_register(void) {
  plugin_register_complex_config("tail", ctail_config);
  plugin_register_init("tail", ctail_init);
  plugin_register_shutdown("tail", ctail_shutdown);
}