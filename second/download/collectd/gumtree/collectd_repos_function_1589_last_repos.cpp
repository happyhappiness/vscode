void module_register(void) {
  plugin_register_read("uptime", uptime_read);
}