void module_register(void) {
  plugin_register_read("fscache", fscache_read);
}