static void submit_derive(const char *type, const char *type_inst,
                          derive_t value, memcached_t *st) {
  value_list_t vl = VALUE_LIST_INIT;

  memcached_init_vl(&vl, st);
  vl.values = &(value_t){.derive = value};
  vl.values_len = 1;
  sstrncpy(vl.type, type, sizeof(vl.type));
  if (type_inst != NULL)
    sstrncpy(vl.type_instance, type_inst, sizeof(vl.type_instance));

  plugin_dispatch_values(&vl);
}