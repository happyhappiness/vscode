static void ovs_stats_bridge_table_delete_cb(yajl_val jupdates) {
  const char *path[] = {"Bridge", NULL};
  yajl_val bridges = yajl_tree_get(jupdates, path, yajl_t_object);
  yajl_val bridge;
  if (bridges && YAJL_IS_OBJECT(bridges)) {
    pthread_mutex_lock(&g_stats_lock);
    for (size_t i = 0; i < YAJL_GET_OBJECT(bridges)->len; i++) {
      bridge = YAJL_GET_OBJECT(bridges)->values[i];
      ovs_stats_del_bridge(bridge);
    }
    pthread_mutex_unlock(&g_stats_lock);
  }
  return;
}