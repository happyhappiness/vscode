static void submit_octets(derive_t queries, derive_t responses) {
  value_t values[2];
  value_list_t vl = VALUE_LIST_INIT;

  values[0].derive = queries;
  values[1].derive = responses;

  vl.values = values;
  vl.values_len = 2;
  sstrncpy(vl.host, hostname_g, sizeof(vl.host));
  sstrncpy(vl.plugin, "dns", sizeof(vl.plugin));
  sstrncpy(vl.type, "dns_octets", sizeof(vl.type));

  plugin_dispatch_values(&vl);
}