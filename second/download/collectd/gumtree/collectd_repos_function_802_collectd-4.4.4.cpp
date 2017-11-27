int ut_check_interesting (const char *name)
{
  char *name_copy = NULL;
  char *host = NULL;
  char *plugin = NULL;
  char *plugin_instance = NULL;
  char *type = NULL;
  char *type_instance = NULL;
  int status;
  data_set_t ds;
  value_list_t vl;
  threshold_t *th;

  /* If there is no tree nothing is interesting. */
  if (threshold_tree == NULL)
    return (0);

  name_copy = strdup (name);
  if (name_copy == NULL)
  {
    ERROR ("ut_check_interesting: strdup failed.");
    return (-1);
  }

  status = parse_identifier (name_copy, &host,
      &plugin, &plugin_instance, &type, &type_instance);
  if (status != 0)
  {
    ERROR ("ut_check_interesting: parse_identifier failed.");
    sfree (name_copy);
    return (-1);
  }

  memset (&ds, '\0', sizeof (ds));
  memset (&vl, '\0', sizeof (vl));

  strncpy (vl.host, host, sizeof (vl.host));
  vl.host[sizeof (vl.host) - 1] = '\0';
  strncpy (vl.plugin, plugin, sizeof (vl.plugin));
  vl.plugin[sizeof (vl.plugin) - 1] = '\0';
  if (plugin_instance != NULL)
  {
    strncpy (vl.plugin_instance, plugin_instance, sizeof (vl.plugin_instance));
    vl.plugin_instance[sizeof (vl.plugin_instance) - 1] = '\0';
  }
  strncpy (ds.type, type, sizeof (ds.type));
  ds.type[sizeof (ds.type) - 1] = '\0';
  if (type_instance != NULL)
  {
    strncpy (vl.type_instance, type_instance, sizeof (vl.type_instance));
    vl.type_instance[sizeof (vl.type_instance) - 1] = '\0';
  }

  sfree (name_copy);
  host = plugin = plugin_instance = type = type_instance = NULL;

  th = threshold_search (&ds, &vl);
  if (th == NULL)
    return (0);
  if ((th->flags & UT_FLAG_PERSIST) == 0)
    return (1);
  return (2);
}