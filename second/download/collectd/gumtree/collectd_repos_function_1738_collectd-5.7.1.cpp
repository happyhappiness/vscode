static void cs_submit(derive_t context_switches) {
  value_list_t vl = VALUE_LIST_INIT;

  vl.values = &(value_t){.derive = context_switches};
  vl.values_len = 1;
  sstrncpy(vl.plugin, "contextswitch", sizeof(vl.plugin));
  sstrncpy(vl.type, "contextswitch", sizeof(vl.type));

  plugin_dispatch_values(&vl);
}