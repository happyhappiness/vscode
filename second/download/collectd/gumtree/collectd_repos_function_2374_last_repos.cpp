static void aquaero_submit(const char *type, const char *type_instance,
                           double value) {
  const char *instance = conf_device ? conf_device : "default";
  value_list_t vl = VALUE_LIST_INIT;

  /* Don't report undefined values. */
  if (value == AQ5_FLOAT_UNDEF)
    return;

  vl.values = &(value_t){.gauge = value};
  vl.values_len = 1;

  sstrncpy(vl.plugin, "aquaero", sizeof(vl.plugin));
  sstrncpy(vl.plugin_instance, instance, sizeof(vl.plugin_instance));
  sstrncpy(vl.type, type, sizeof(vl.type));
  sstrncpy(vl.type_instance, type_instance, sizeof(vl.type_instance));

  plugin_dispatch_values(&vl);
}