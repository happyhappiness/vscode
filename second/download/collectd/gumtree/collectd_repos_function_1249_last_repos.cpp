static void entropy_submit(value_t value) {
  value_list_t vl = VALUE_LIST_INIT;

  vl.values = &value;
  vl.values_len = 1;
  sstrncpy(vl.plugin, "entropy", sizeof(vl.plugin));
  sstrncpy(vl.type, "entropy", sizeof(vl.type));

  plugin_dispatch_values(&vl);
}