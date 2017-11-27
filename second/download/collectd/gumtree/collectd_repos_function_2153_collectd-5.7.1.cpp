static void sensors_submit(const char *plugin_instance, const char *type,
                           const char *type_instance, double value) {
  char match_key[1024];
  int status;

  value_list_t vl = VALUE_LIST_INIT;

  status = ssnprintf(match_key, sizeof(match_key), "%s/%s-%s", plugin_instance,
                     type, type_instance);
  if (status < 1)
    return;

  if (sensor_list != NULL) {
    DEBUG("sensors plugin: Checking ignorelist for `%s'", match_key);
    if (ignorelist_match(sensor_list, match_key))
      return;
  }

  vl.values = &(value_t){.gauge = value};
  vl.values_len = 1;

  sstrncpy(vl.plugin, "sensors", sizeof(vl.plugin));
  sstrncpy(vl.plugin_instance, plugin_instance, sizeof(vl.plugin_instance));
  sstrncpy(vl.type, type, sizeof(vl.type));
  sstrncpy(vl.type_instance, type_instance, sizeof(vl.type_instance));

  plugin_dispatch_values(&vl);
}