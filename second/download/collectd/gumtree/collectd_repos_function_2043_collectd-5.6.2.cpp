void module_register(void) {
  plugin_register_read("cpusleep", cpusleep_read);
}