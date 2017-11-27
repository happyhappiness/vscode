void module_register(void) {
  plugin_register_complex_config("modbus", mb_config);
  plugin_register_shutdown("modbus", mb_shutdown);
}