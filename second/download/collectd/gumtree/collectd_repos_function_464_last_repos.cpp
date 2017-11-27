static int ovs_stats_update_iface_stats(port_list_t *port, yajl_val stats) {
  yajl_val stat;
  iface_counter counter_index = 0;
  char *counter_name = NULL;
  int64_t counter_value = 0;
  if (stats && YAJL_IS_ARRAY(stats))
    for (size_t i = 0; i < YAJL_GET_ARRAY(stats)->len; i++) {
      stat = YAJL_GET_ARRAY(stats)->values[i];
      if (!YAJL_IS_ARRAY(stat))
        return -1;
      counter_name = YAJL_GET_STRING(YAJL_GET_ARRAY(stat)->values[0]);
      counter_index = ovs_stats_counter_name_to_type(counter_name);
      counter_value = YAJL_GET_INTEGER(YAJL_GET_ARRAY(stat)->values[1]);
      if (counter_index == not_supported)
        continue;
      port->stats[counter_index] = counter_value;
    }

  return 0;
}