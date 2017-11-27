static void submit (time_t ts, const char *plugin_instance, /* {{{ */
    const char *type, const char *type_instance, value_t value)
{
  value_t values[1];
  value_list_t vl = VALUE_LIST_INIT;

  values[0] = value;

  vl.values = values;
  vl.values_len = 1;
  vl.time = ts;
  sstrncpy(vl.host, hostname_g, sizeof(vl.host));
  sstrncpy(vl.plugin, "bind", sizeof(vl.plugin));
  if (plugin_instance) {
    sstrncpy(vl.plugin_instance, plugin_instance,
        sizeof(vl.plugin_instance));
    remove_special (vl.plugin_instance, sizeof (vl.plugin_instance));
  }
  sstrncpy(vl.type, type, sizeof(vl.type));
  if (type_instance) {
    sstrncpy(vl.type_instance, type_instance,
        sizeof(vl.type_instance));
    remove_special (vl.plugin_instance, sizeof (vl.plugin_instance));
  }
  plugin_dispatch_values(&vl);
}