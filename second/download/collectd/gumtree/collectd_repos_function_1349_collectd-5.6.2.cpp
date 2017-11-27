static void
swap_submit_derive(char const *type_instance, /* {{{ */
                   derive_t value) {
  value_list_t vl = VALUE_LIST_INIT;
  value_t v[1];

  v[0].derive = value;

  vl.values = v;
  vl.values_len = STATIC_ARRAY_SIZE(v);
  sstrncpy(vl.host, hostname_g, sizeof(vl.host));
  sstrncpy(vl.plugin, "swap", sizeof(vl.plugin));
  sstrncpy(vl.type, "swap_io", sizeof(vl.type));
  sstrncpy(vl.type_instance, type_instance, sizeof(vl.type_instance));

  plugin_dispatch_values(&vl);
}