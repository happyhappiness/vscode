void module_register(void) {
  plugin_register_complex_config("battery", battery_config);
  plugin_register_read("battery", battery_read);
}