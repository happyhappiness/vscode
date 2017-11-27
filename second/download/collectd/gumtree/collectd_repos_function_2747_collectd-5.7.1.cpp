int plugin_unregister_log(const char *name) {
  return (plugin_unregister(list_log, name));
}