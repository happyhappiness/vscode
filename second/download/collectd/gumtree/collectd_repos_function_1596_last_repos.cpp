void module_register(void) {
  plugin_register_init("apple_sensors", as_init);
  plugin_register_read("apple_sensors", as_read);
}