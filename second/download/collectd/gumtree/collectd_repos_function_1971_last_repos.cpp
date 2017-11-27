void module_register(void) {
  plugin_register_init("multimeter", multimeter_init);
  plugin_register_read("multimeter", multimeter_read);
  plugin_register_shutdown("multimeter", multimeter_shutdown);
}