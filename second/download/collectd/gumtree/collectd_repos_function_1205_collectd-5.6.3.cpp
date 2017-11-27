void module_register(void) {
  plugin_register_read("entropy", entropy_read);
}