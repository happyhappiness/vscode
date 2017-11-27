static void md_submit (const int minor, const char *type_instance,
    gauge_t value)
{
  value_t values[1];
  value_list_t vl = VALUE_LIST_INIT;

  values[0].gauge = value;

  vl.values = values;
  vl.values_len = 1;
  sstrncpy (vl.host, hostname_g, sizeof (vl.host));
  sstrncpy (vl.plugin, "md", sizeof (vl.plugin));
  ssnprintf (vl.plugin_instance, sizeof (vl.plugin_instance),
      "%i", minor);
  sstrncpy (vl.type, "md_disks", sizeof (vl.type));
  sstrncpy (vl.type_instance, type_instance,
      sizeof (vl.type_instance));

  plugin_dispatch_values (&vl);
}