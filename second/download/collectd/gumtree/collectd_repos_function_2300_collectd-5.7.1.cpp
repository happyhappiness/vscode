static void submit(const char *protocol_name, const char *str_key,
                   const char *str_value) {
  value_t value;
  value_list_t vl = VALUE_LIST_INIT;
  int status;

  status = parse_value(str_value, &value, DS_TYPE_DERIVE);
  if (status != 0) {
    ERROR("protocols plugin: Parsing string as integer failed: %s", str_value);
    return;
  }

  vl.values = &value;
  vl.values_len = 1;
  sstrncpy(vl.plugin, "protocols", sizeof(vl.plugin));
  sstrncpy(vl.plugin_instance, protocol_name, sizeof(vl.plugin_instance));
  sstrncpy(vl.type, "protocol_counter", sizeof(vl.type));
  sstrncpy(vl.type_instance, str_key, sizeof(vl.type_instance));

  plugin_dispatch_values(&vl);
}