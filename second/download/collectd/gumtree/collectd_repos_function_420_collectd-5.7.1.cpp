void module_register(void) {
  plugin_register_complex_config("apcups", apcups_config);
  plugin_register_read("apcups", apcups_read);
  plugin_register_shutdown("apcups", apcups_shutdown);
}