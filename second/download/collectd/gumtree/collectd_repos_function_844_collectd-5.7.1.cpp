void module_register(void) {
  plugin_register_complex_config("filecount", fc_config);
  plugin_register_init("filecount", fc_init);
  plugin_register_read("filecount", fc_read);
}