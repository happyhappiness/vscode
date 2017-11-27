static void nut_submit(nut_ups_t *ups, const char *type,
                       const char *type_instance, gauge_t value) {
  value_list_t vl = VALUE_LIST_INIT;

  vl.values = &(value_t){.gauge = value};
  vl.values_len = 1;
  sstrncpy(vl.host,
           (strcasecmp(ups->hostname, "localhost") == 0) ? hostname_g
                                                         : ups->hostname,
           sizeof(vl.host));
  sstrncpy(vl.plugin, "nut", sizeof(vl.plugin));
  sstrncpy(vl.plugin_instance, ups->upsname, sizeof(vl.plugin_instance));
  sstrncpy(vl.type, type, sizeof(vl.type));
  sstrncpy(vl.type_instance, type_instance, sizeof(vl.type_instance));

  plugin_dispatch_values(&vl);
}