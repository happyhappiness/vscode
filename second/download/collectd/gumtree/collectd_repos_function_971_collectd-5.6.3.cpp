static int pplugin_unregister_data_set(char *name) {
  if (NULL == name)
    return 0;
  return plugin_unregister_data_set(name);
}