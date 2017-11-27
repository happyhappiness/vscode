static void lvm_submit(char const *plugin_instance, char const *type_instance,
                       uint64_t ivalue) {
  value_list_t vl = VALUE_LIST_INIT;

  vl.values = &(value_t){.gauge = (gauge_t)ivalue};
  vl.values_len = 1;

  sstrncpy(vl.plugin, "lvm", sizeof(vl.plugin));
  sstrncpy(vl.plugin_instance, plugin_instance, sizeof(vl.plugin_instance));
  sstrncpy(vl.type, "df_complex", sizeof(vl.type));
  sstrncpy(vl.type_instance, type_instance, sizeof(vl.type_instance));

  plugin_dispatch_values(&vl);
}