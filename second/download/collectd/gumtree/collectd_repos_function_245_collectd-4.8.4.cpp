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
  sstrncpy (vl.host, hostname_g, sizeof (vl.host));
  sstrncpy (vl.plugin, "netlink", sizeof (vl.plugin));
  sstrncpy (vl.plugin_instance, dev, sizeof (vl.plugin_instance));
  sstrncpy (vl.type, type, sizeof (vl.type));

  if (type_instance != NULL)
    sstrncpy (vl.type_instance, type_instance, sizeof (vl.type_instance));

  plugin_dispatch_values (&vl);
}