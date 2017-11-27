static int plugin_submit(const pinba_statnode_t *res) /* {{{ */
{
  value_list_t vl = VALUE_LIST_INIT;

  vl.values_len = 1;
  sstrncpy(vl.plugin, "pinba", sizeof(vl.plugin));
  sstrncpy(vl.plugin_instance, res->name, sizeof(vl.plugin_instance));

  vl.values = &(value_t){.derive = res->req_count};
  sstrncpy(vl.type, "total_requests", sizeof(vl.type));
  plugin_dispatch_values(&vl);

  vl.values = &(value_t){
      .derive = float_counter_get(&res->req_time, /* factor = */ 1000)};
  sstrncpy(vl.type, "total_time_in_ms", sizeof(vl.type));
  plugin_dispatch_values(&vl);

  vl.values = &(value_t){.derive = res->doc_size};
  sstrncpy(vl.type, "total_bytes", sizeof(vl.type));
  plugin_dispatch_values(&vl);

  vl.values = &(value_t){
      .derive = float_counter_get(&res->ru_utime, /* factor = */ 100)};
  sstrncpy(vl.type, "cpu", sizeof(vl.type));
  sstrncpy(vl.type_instance, "user", sizeof(vl.type_instance));
  plugin_dispatch_values(&vl);

  vl.values = &(value_t){
      .derive = float_counter_get(&res->ru_stime, /* factor = */ 100)};
  sstrncpy(vl.type, "cpu", sizeof(vl.type));
  sstrncpy(vl.type_instance, "system", sizeof(vl.type_instance));
  plugin_dispatch_values(&vl);

  vl.values = &(value_t){.gauge = res->mem_peak};
  sstrncpy(vl.type, "memory", sizeof(vl.type));
  sstrncpy(vl.type_instance, "peak", sizeof(vl.type_instance));
  plugin_dispatch_values(&vl);

  return (0);
}