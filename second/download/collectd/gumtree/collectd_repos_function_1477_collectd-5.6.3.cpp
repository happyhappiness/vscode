static void uptime_submit(gauge_t uptime) {
  value_t values[1];
  value_list_t vl = VALUE_LIST_INIT;

  values[0].gauge = uptime;

  vl.values = values;
  vl.values_len = 1;

  sstrncpy(vl.host, hostname_g, sizeof(vl.host));
  sstrncpy(vl.plugin, "uptime", sizeof(vl.plugin));
  sstrncpy(vl.type, "uptime", sizeof(vl.type));

  plugin_dispatch_values(&vl);
}