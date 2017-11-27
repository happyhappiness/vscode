static void mic_submit_temp(int micnumber, const char *type, gauge_t val) {
  value_t values[1];
  value_list_t vl = VALUE_LIST_INIT;

  values[0].gauge = val;

  vl.values = values;
  vl.values_len = 1;

  strncpy(vl.host, hostname_g, sizeof(vl.host));
  strncpy(vl.plugin, "mic", sizeof(vl.plugin));
  ssnprintf(vl.plugin_instance, sizeof(vl.plugin_instance), "%i", micnumber);
  strncpy(vl.type, "temperature", sizeof(vl.type));
  strncpy(vl.type_instance, type, sizeof(vl.type_instance));

  plugin_dispatch_values(&vl);
}