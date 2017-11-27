void module_register(void) {
  plugin_register_complex_config("powerdns", powerdns_config);
  plugin_register_read("powerdns", powerdns_read);
  plugin_register_shutdown("powerdns", powerdns_shutdown);
}