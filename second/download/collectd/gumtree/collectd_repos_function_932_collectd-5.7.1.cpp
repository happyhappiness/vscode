static void submit_gauge2(const char *type, const char *type_inst,
                          gauge_t value0, gauge_t value1, memcached_t *st) {
  value_list_t vl = VALUE_LIST_INIT;
  value_t values[] = {
      {.gauge = value0}, {.gauge = value1},
  };

  memcached_init_vl(&vl, st);
  vl.values = values;
  vl.values_len = STATIC_ARRAY_SIZE(values);
  sstrncpy(vl.type, type, sizeof(vl.type));
  if (type_inst != NULL)
    sstrncpy(vl.type_instance, type_inst, sizeof(vl.type_instance));

  plugin_dispatch_values(&vl);
}