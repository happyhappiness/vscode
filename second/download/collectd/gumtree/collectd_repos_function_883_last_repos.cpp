void module_register(void) {
  plugin_register_read("synproxy", synproxy_read);
}