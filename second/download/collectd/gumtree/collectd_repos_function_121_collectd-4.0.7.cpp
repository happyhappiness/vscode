static int parse_line (char *buffer)
{
  char *fields[4];
  int fields_num;

  char *hostname;
  char *plugin;
  char *plugin_instance;
  char *type;
  char *type_instance;

  const data_set_t *ds;
  value_list_t vl = VALUE_LIST_INIT;

  int status;

  fields_num = strsplit (buffer, fields, 4);
  if (fields_num != 2)
  {
    WARNING ("exec plugin: Number of fields is not 2.");
    return (-1);
  }

  status = parse_identifier (fields[0], &hostname,
      &plugin, &plugin_instance,
      &type, &type_instance);
  if (status != 0)
  {
    WARNING ("exec plugin: Cannot parse `%s'", fields[0]);
    return (-1);
  }

  if ((strlen (hostname) >= sizeof (vl.host))
      || (strlen (plugin) >= sizeof (vl.plugin))
      || ((plugin_instance != NULL)
	&& (strlen (plugin_instance) >= sizeof (vl.plugin_instance)))
      || ((type_instance != NULL)
	&& (strlen (type_instance) >= sizeof (vl.type_instance))))
  {
    WARNING ("exec plugin: An identifier is too long.");
    return (-1);
  }

  strcpy (vl.host, hostname);
  strcpy (vl.plugin, plugin);
  if (plugin_instance != NULL)
    strcpy (vl.plugin_instance, plugin_instance);
  if (type_instance != NULL)
    strcpy (vl.type_instance, type_instance);

  ds = plugin_get_ds (type);
  if (ds == NULL)
  {
    WARNING ("exec plugin: No such type: `%s'", type);
    return (-1);
  }

  vl.values_len = ds->ds_num;
  vl.values = (value_t *) malloc (sizeof (value_t) * vl.values_len);
  if (vl.values == NULL)
    return (-1);

  /* Sets vl.values and vl.time */
  status = parse_values (fields[1], &vl, ds);
  if (status != 0)
  {
    WARNING ("exec plugin: Cannot parse `%s'", fields[1]);
    sfree (vl.values);
    return (-1);
  }

  plugin_dispatch_values (type, &vl);

  sfree (vl.values);
  
  return (0);
}