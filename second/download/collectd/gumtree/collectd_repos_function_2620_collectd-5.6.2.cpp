int plugin_unregister_write(const char *name) {
  return (plugin_unregister(list_write, name));
}