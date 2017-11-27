static const char *plugin_get_dir(void) {
  if (plugindir == NULL)
    return (PLUGINDIR);
  else
    return (plugindir);
}