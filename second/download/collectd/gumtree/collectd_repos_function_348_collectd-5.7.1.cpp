static void cpu_commit_num_cpu(gauge_t value) /* {{{ */
{
  value_list_t vl = VALUE_LIST_INIT;

  vl.values = &(value_t){.gauge = value};
  vl.values_len = 1;

  sstrncpy(vl.plugin, "cpu", sizeof(vl.plugin));
  sstrncpy(vl.type, "count", sizeof(vl.type));

  plugin_dispatch_values(&vl);
}