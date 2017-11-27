static void submit (char *type, char *inst, long long value)
{
  value_t values[1];
  value_list_t vl = VALUE_LIST_INIT;

  if (strcmp (type, "nginx_connections") == 0)
    values[0].gauge = value;
  else if (strcmp (type, "nginx_requests") == 0)
    values[0].counter = value;
  else
    return;

  vl.values = values;
  vl.values_len = 1;
  vl.time = time (NULL);
  sstrncpy (vl.host, hostname_g, sizeof (vl.host));
  sstrncpy (vl.plugin, "nginx", sizeof (vl.plugin));
  sstrncpy (vl.plugin_instance, "", sizeof (vl.plugin_instance));

  if (inst != NULL)
  {
    strncpy (vl.type_instance, inst, sizeof (vl.type_instance));
    vl.type_instance[sizeof (vl.type_instance) - 1] = '\0';
  }

  plugin_dispatch_values (type, &vl);
}