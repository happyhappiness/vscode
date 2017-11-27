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

  sstrncpy (vl.host, host, sizeof (vl.host));
  sstrncpy (vl.plugin, plugin, sizeof (vl.plugin));
  if (plugin_instance != NULL)
    sstrncpy (vl.plugin_instance, plugin_instance, sizeof (vl.plugin_instance));
  sstrncpy (ds.type, type, sizeof (ds.type));
  sstrncpy (vl.type, type, sizeof (vl.type));
  if (type_instance != NULL)
    sstrncpy (vl.type_instance, type_instance, sizeof (vl.type_instance));

  sfree (name_copy);
  host = plugin = plugin_instance = type = type_instance = NULL;

  th = threshold_search (&vl);
  if (th == NULL)
    return (0);
  if ((th->flags & UT_FLAG_PERSIST) == 0)
    return (1);
  return (2);
}