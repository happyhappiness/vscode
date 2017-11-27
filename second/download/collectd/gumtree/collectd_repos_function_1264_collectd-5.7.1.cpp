void module_register(void) {
  plugin_register_complex_config(g_plugin_name, hp_config);
  plugin_register_read(g_plugin_name, huge_read);
}