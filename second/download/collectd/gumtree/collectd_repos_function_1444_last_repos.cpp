static void submit_octets(derive_t queries, derive_t responses) {
  value_t values[] = {
      {.derive = queries}, {.derive = responses},
  };
  value_list_t vl = VALUE_LIST_INIT;

  vl.values = values;
  vl.values_len = STATIC_ARRAY_SIZE(values);
  sstrncpy(vl.plugin, "dns", sizeof(vl.plugin));
  sstrncpy(vl.type, "dns_octets", sizeof(vl.type));

  plugin_dispatch_values(&vl);
}