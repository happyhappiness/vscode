static void numusers_submit(const char *pinst, const char *tinst,
                            gauge_t value) {
  value_list_t vl = VALUE_LIST_INIT;

  vl.values = &(value_t){.gauge = value};
  vl.values_len = 1;
  sstrncpy(vl.plugin, "openvpn", sizeof(vl.plugin));
  sstrncpy(vl.type, "users", sizeof(vl.type));
  if (pinst != NULL)
    sstrncpy(vl.plugin_instance, pinst, sizeof(vl.plugin_instance));
  if (tinst != NULL)
    sstrncpy(vl.type_instance, tinst, sizeof(vl.type_instance));

  plugin_dispatch_values(&vl);
}