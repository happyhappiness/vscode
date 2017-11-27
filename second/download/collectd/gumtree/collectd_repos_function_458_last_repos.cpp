static void ovs_stats_bridge_table_result_cb(yajl_val jresult,
                                             yajl_val jerror) {
  if (YAJL_IS_NULL(jerror))
    ovs_stats_bridge_table_change_cb(jresult);
  else
    ERROR("%s: Error received from OvSDB. Table: Bridge", plugin_name);
  return;
}