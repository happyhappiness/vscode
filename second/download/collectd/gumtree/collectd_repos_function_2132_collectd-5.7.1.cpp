void module_register(void) {
  plugin_register_complex_config("python", cpy_config);
  plugin_register_init("python", cpy_init);
  plugin_register_shutdown("python", cpy_shutdown);
}