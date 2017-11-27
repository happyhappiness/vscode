void module_register(void) {
  plugin_register_read("contextswitch", cs_read);
}