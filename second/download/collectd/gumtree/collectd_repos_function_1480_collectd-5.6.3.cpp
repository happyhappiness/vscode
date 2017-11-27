void module_register(void) {
  plugin_register_init("uptime", uptime_init);
  plugin_register_read("uptime", uptime_read);
}