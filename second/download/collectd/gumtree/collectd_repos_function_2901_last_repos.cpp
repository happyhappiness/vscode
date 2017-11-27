int plugin_unregister_missing(const char *name) {
  return plugin_unregister(list_missing, name);
}