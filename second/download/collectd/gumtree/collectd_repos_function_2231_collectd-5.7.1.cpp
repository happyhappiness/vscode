static void cipvs_submit_if(const char *pi, const char *t, const char *ti,
                            derive_t rx, derive_t tx) {
  value_t values[] = {
      {.derive = rx}, {.derive = tx},
  };
  value_list_t vl = VALUE_LIST_INIT;

  vl.values = values;
  vl.values_len = STATIC_ARRAY_SIZE(values);

  sstrncpy(vl.plugin, "ipvs", sizeof(vl.plugin));
  sstrncpy(vl.plugin_instance, pi, sizeof(vl.plugin_instance));
  sstrncpy(vl.type, t, sizeof(vl.type));
  sstrncpy(vl.type_instance, (NULL != ti) ? ti : "total",
           sizeof(vl.type_instance));

  plugin_dispatch_values(&vl);
  return;
}