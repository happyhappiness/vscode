static threshold_t *threshold_get (const char *hostname,
    const char *plugin, const char *plugin_instance,
    const char *type, const char *type_instance)
{
  char name[6 * DATA_MAX_NAME_LEN];
  threshold_t *th = NULL;

  format_name (name, sizeof (name),
      (hostname == NULL) ? "" : hostname,
      (plugin == NULL) ? "" : plugin, plugin_instance,
      (type == NULL) ? "" : type, type_instance);
  name[sizeof (name) - 1] = '\0';

  if (c_avl_get (threshold_tree, name, (void *) &th) == 0)
    return (th);
  else
    return (NULL);
}