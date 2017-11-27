static void submit(time_t ts, const char *plugin_instance, /* {{{ */
                   const char *type, const char *type_instance, value_t value) {
  value_list_t vl = VALUE_LIST_INIT;

  vl.values = &value;
  vl.values_len = 1;
  if (config_parse_time)
    vl.time = TIME_T_TO_CDTIME_T(ts);
  sstrncpy(vl.plugin, "bind", sizeof(vl.plugin));
  if (plugin_instance) {
    sstrncpy(vl.plugin_instance, plugin_instance, sizeof(vl.plugin_instance));
    replace_special(vl.plugin_instance, sizeof(vl.plugin_instance));
  }
  sstrncpy(vl.type, type, sizeof(vl.type));
  if (type_instance) {
    sstrncpy(vl.type_instance, type_instance, sizeof(vl.type_instance));
    replace_special(vl.type_instance, sizeof(vl.type_instance));
  }
  plugin_dispatch_values(&vl);
}