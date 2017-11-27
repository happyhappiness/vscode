static void numa_dispatch_value(int node, /* {{{ */
                                const char *type_instance, value_t v) {
  value_list_t vl = VALUE_LIST_INIT;

  vl.values = &v;
  vl.values_len = 1;

  sstrncpy(vl.plugin, "numa", sizeof(vl.plugin));
  snprintf(vl.plugin_instance, sizeof(vl.plugin_instance), "node%i", node);
  sstrncpy(vl.type, "vmpage_action", sizeof(vl.type));
  sstrncpy(vl.type_instance, type_instance, sizeof(vl.type_instance));

  plugin_dispatch_values(&vl);
}