static void nut_submit (nut_ups_t *ups, const char *type,
    const char *type_instance, gauge_t value)
{
  value_t values[1];
  value_list_t vl = VALUE_LIST_INIT;

  values[0].gauge = value;

  vl.values = values;
  vl.values_len = STATIC_ARRAY_SIZE (values);
  vl.time = time (NULL);
  strncpy (vl.host,
      (strcasecmp (ups->hostname, "localhost") == 0)
      ? hostname_g
      : ups->hostname,
      sizeof (vl.host));
  strcpy (vl.plugin, "nut");
  strncpy (vl.plugin_instance, ups->upsname, sizeof (vl.plugin_instance));
  strncpy (vl.type_instance, type_instance, sizeof (vl.type_instance));

  vl.host[sizeof (vl.host) - 1] = '\0';
  vl.plugin_instance[sizeof (vl.plugin_instance) - 1] = '\0';
  vl.type_instance[sizeof (vl.type_instance) - 1] = '\0';

  plugin_dispatch_values (type, &vl);
}