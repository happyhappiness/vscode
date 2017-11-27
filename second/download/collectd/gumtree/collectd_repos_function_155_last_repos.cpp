static void irq_submit(const char *irq_name, derive_t value) {
  value_list_t vl = VALUE_LIST_INIT;

  if (ignorelist_match(ignorelist, irq_name) != 0)
    return;

  vl.values = &(value_t){.derive = value};
  vl.values_len = 1;
  sstrncpy(vl.plugin, "irq", sizeof(vl.plugin));
  sstrncpy(vl.type, "irq", sizeof(vl.type));
  sstrncpy(vl.type_instance, irq_name, sizeof(vl.type_instance));

  plugin_dispatch_values(&vl);
}