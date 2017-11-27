static void swap_submit_usage(char const *plugin_instance, /* {{{ */
                              gauge_t used, gauge_t free,
                              char const *other_name, gauge_t other_value) {
  value_t v[1];
  value_list_t vl = VALUE_LIST_INIT;

  vl.values = v;
  vl.values_len = STATIC_ARRAY_SIZE(v);
  sstrncpy(vl.host, hostname_g, sizeof(vl.host));
  sstrncpy(vl.plugin, "swap", sizeof(vl.plugin));
  if (plugin_instance != NULL)
    sstrncpy(vl.plugin_instance, plugin_instance, sizeof(vl.plugin_instance));
  sstrncpy(vl.type, "swap", sizeof(vl.type));

  if (values_absolute)
    plugin_dispatch_multivalue(&vl, 0, DS_TYPE_GAUGE, "used", used, "free",
                               free, other_name, other_value, NULL);
  if (values_percentage)
    plugin_dispatch_multivalue(&vl, 1, DS_TYPE_GAUGE, "used", used, "free",
                               free, other_name, other_value, NULL);
}