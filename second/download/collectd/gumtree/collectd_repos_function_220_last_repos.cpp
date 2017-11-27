static void rdt_submit_gauge(char *cgroup, char *type, char *type_instance,
                             gauge_t value) {
  value_list_t vl = VALUE_LIST_INIT;

  vl.values = &(value_t){.gauge = value};
  vl.values_len = 1;

  sstrncpy(vl.plugin, RDT_PLUGIN, sizeof(vl.plugin));
  snprintf(vl.plugin_instance, sizeof(vl.plugin_instance), "%s", cgroup);
  sstrncpy(vl.type, type, sizeof(vl.type));
  if (type_instance)
    sstrncpy(vl.type_instance, type_instance, sizeof(vl.type_instance));

  plugin_dispatch_values(&vl);
}