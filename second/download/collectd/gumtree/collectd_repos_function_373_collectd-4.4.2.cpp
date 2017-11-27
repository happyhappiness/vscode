static void submit (const char *plugin_instance, /* {{{ */
    const char *pdns_type, const char *value)
{
  value_list_t vl = VALUE_LIST_INIT;
  value_t values[1];

  const char *type = NULL;
  const char *type_instance = NULL;
  const data_set_t *ds;

  int i;

  for (i = 0; i < lookup_table_length; i++)
    if (strcmp (lookup_table[i].name, pdns_type) == 0)
      break;

  if (lookup_table[i].type == NULL)
    return;

  if (i >= lookup_table_length)
  {
    INFO ("powerdns plugin: submit: Not found in lookup table: %s = %s;",
        pdns_type, value);
    return;
  }

  type = lookup_table[i].type;
  type_instance = lookup_table[i].type_instance;

  ds = plugin_get_ds (type);
  if (ds == NULL)
  {
    ERROR ("powerdns plugin: The lookup table returned type `%s', "
        "but I cannot find it via `plugin_get_ds'.",
        type);
    return;
  }

  if (ds->ds_num != 1)
  {
    ERROR ("powerdns plugin: type `%s' has %i data sources, "
        "but I can only handle one.",
        type, ds->ds_num);
    return;
  }

  if (ds->ds[0].type == DS_TYPE_GAUGE)
  {
    char *endptr = NULL;

    values[0].gauge = strtod (value, &endptr);

    if (endptr == value)
    {
      ERROR ("powerdns plugin: Cannot convert `%s' "
          "to a floating point number.", value);
      return;
    }
  }
  else
  {
    char *endptr = NULL;

    values[0].counter = strtoll (value, &endptr, 0);
    if (endptr == value)
    {
      ERROR ("powerdns plugin: Cannot convert `%s' "
          "to an integer number.", value);
      return;
    }
  }

  vl.values = values;
  vl.values_len = 1;
  vl.time = time (NULL);
  sstrncpy (vl.host, hostname_g, sizeof (vl.host));
  sstrncpy (vl.plugin, "powerdns", sizeof (vl.plugin));
  if (type_instance != NULL)
    sstrncpy (vl.type_instance, type_instance, sizeof (vl.type_instance));
  sstrncpy (vl.plugin_instance, plugin_instance, sizeof (vl.plugin_instance));

  plugin_dispatch_values (type, &vl);
}