void module_register(void) {
  plugin_register_complex_config("write_log", wl_config);
  /* If config is supplied, the global wl_format will be set. */
  plugin_register_write("write_log", wl_write, NULL);
}