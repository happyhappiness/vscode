void module_register(void) {
  plugin_register_complex_config("lua", lua_config);
  plugin_register_shutdown("lua", lua_shutdown);
}