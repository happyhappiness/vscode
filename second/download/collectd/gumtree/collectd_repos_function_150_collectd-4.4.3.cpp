static void submit_two (const char *dev, const char *type,
    const char *type_instance,
    counter_t rx, counter_t tx)
{
  value_t values[2];
  value_list_t vl = VALUE_LIST_INIT;

  values[0].counter = rx;
  values[1].counter = tx;

  vl.values = values;
  vl.values_len = 2;
  vl.time = time (NULL);
  sstrncpy (vl.host, hostname_g, sizeof (vl.host));
  sstrncpy (vl.plugin, "netlink", sizeof (vl.plugin));
  strncpy (vl.plugin_instance, dev, sizeof (vl.plugin_instance));

  if (type_instance != NULL)
    strncpy (vl.type_instance, type_instance, sizeof (vl.type_instance));

  plugin_dispatch_values (type, &vl);
}