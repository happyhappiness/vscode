int parse_identifier(char *str, char **ret_host, char **ret_plugin,
                     char **ret_plugin_instance, char **ret_type,
                     char **ret_type_instance, char *default_host) {
  char *hostname = NULL;
  char *plugin = NULL;
  char *plugin_instance = NULL;
  char *type = NULL;
  char *type_instance = NULL;

  hostname = str;
  if (hostname == NULL)
    return -1;

  plugin = strchr(hostname, '/');
  if (plugin == NULL)
    return -1;
  *plugin = '\0';
  plugin++;

  type = strchr(plugin, '/');
  if (type == NULL) {
    if (default_host == NULL)
      return -1;
    /* else: no host specified; use default */
    type = plugin;
    plugin = hostname;
    hostname = default_host;
  } else {
    *type = '\0';
    type++;
  }

  plugin_instance = strchr(plugin, '-');
  if (plugin_instance != NULL) {
    *plugin_instance = '\0';
    plugin_instance++;
  }

  type_instance = strchr(type, '-');
  if (type_instance != NULL) {
    *type_instance = '\0';
    type_instance++;
  }

  *ret_host = hostname;
  *ret_plugin = plugin;
  *ret_plugin_instance = plugin_instance;
  *ret_type = type;
  *ret_type_instance = type_instance;
  return 0;
}