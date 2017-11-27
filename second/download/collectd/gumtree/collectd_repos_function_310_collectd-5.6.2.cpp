static void cpu_commit_num_cpu(gauge_t num_cpu) /* {{{ */
{
  value_t values[1];
  value_list_t vl = VALUE_LIST_INIT;

  values[0].gauge = num_cpu;

  vl.values = values;
  vl.values_len = 1;

  sstrncpy(vl.host, hostname_g, sizeof(vl.host));
  sstrncpy(vl.plugin, "cpu", sizeof(vl.plugin));
  sstrncpy(vl.type, "count", sizeof(vl.type));

  plugin_dispatch_values(&vl);
}