static void submit(const char *type, const char *inst, long long value) {
  value_t values[1];
  value_list_t vl = VALUE_LIST_INIT;

  if (strcmp(type, "nginx_connections") == 0)
    values[0].gauge = value;
  else if (strcmp(type, "nginx_requests") == 0)
    values[0].derive = value;
  else if (strcmp(type, "connections") == 0)
    values[0].derive = value;
  else
    return;

  vl.values = values;
  vl.values_len = STATIC_ARRAY_SIZE(values);
  sstrncpy(vl.plugin, "nginx", sizeof(vl.plugin));
  sstrncpy(vl.type, type, sizeof(vl.type));

  if (inst != NULL)
    sstrncpy(vl.type_instance, inst, sizeof(vl.type_instance));

  plugin_dispatch_values(&vl);
}