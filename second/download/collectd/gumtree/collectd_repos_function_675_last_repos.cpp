void module_register(void) {
  plugin_register_complex_config("java", cjni_config_callback);
  plugin_register_init("java", cjni_init);
  plugin_register_shutdown("java", cjni_shutdown);
}