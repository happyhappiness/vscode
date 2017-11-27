static void
swap_submit_derive(char const *type_instance, /* {{{ */
                   derive_t value) {
  value_list_t vl = VALUE_LIST_INIT;

  vl.values = &(value_t){.derive = value};
  vl.values_len = 1;
  sstrncpy(vl.plugin, "swap", sizeof(vl.plugin));
  sstrncpy(vl.type, "swap_io", sizeof(vl.type));
  sstrncpy(vl.type_instance, type_instance, sizeof(vl.type_instance));

  plugin_dispatch_values(&vl);
}