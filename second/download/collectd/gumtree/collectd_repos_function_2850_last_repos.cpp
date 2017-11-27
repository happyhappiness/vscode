static int plugin_update_internal_statistics(void) { /* {{{ */
  gauge_t copy_write_queue_length = (gauge_t)write_queue_length;

  /* Initialize `vl' */
  value_list_t vl = VALUE_LIST_INIT;
  sstrncpy(vl.plugin, "collectd", sizeof(vl.plugin));
  vl.interval = plugin_get_interval();

  /* Write queue */
  sstrncpy(vl.plugin_instance, "write_queue", sizeof(vl.plugin_instance));

  /* Write queue : queue length */
  vl.values = &(value_t){.gauge = copy_write_queue_length};
  vl.values_len = 1;
  sstrncpy(vl.type, "queue_length", sizeof(vl.type));
  vl.type_instance[0] = 0;
  plugin_dispatch_values(&vl);

  /* Write queue : Values dropped (queue length > low limit) */
  vl.values = &(value_t){.gauge = (gauge_t)stats_values_dropped};
  vl.values_len = 1;
  sstrncpy(vl.type, "derive", sizeof(vl.type));
  sstrncpy(vl.type_instance, "dropped", sizeof(vl.type_instance));
  plugin_dispatch_values(&vl);

  /* Cache */
  sstrncpy(vl.plugin_instance, "cache", sizeof(vl.plugin_instance));

  /* Cache : Nb entry in cache tree */
  vl.values = &(value_t){.gauge = (gauge_t)uc_get_size()};
  vl.values_len = 1;
  sstrncpy(vl.type, "cache_size", sizeof(vl.type));
  vl.type_instance[0] = 0;
  plugin_dispatch_values(&vl);

  return 0;
}