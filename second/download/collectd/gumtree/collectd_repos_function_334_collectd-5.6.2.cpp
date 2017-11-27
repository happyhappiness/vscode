static int zone_submit_value(char *zone, gauge_t value) {
  value_list_t vl = VALUE_LIST_INIT;
  value_t values[1];

  values[0].gauge = value;

  vl.values = values;
  vl.values_len = 1; /*STATIC_ARRAY_SIZE (values);*/
  sstrncpy(vl.host, hostname_g, sizeof(vl.host));
  sstrncpy(vl.plugin, "zone", sizeof(vl.plugin));
  sstrncpy(vl.type, "percent", sizeof(vl.type));
  sstrncpy(vl.type_instance, zone, sizeof(vl.type_instance));

  return (plugin_dispatch_values(&vl));
}