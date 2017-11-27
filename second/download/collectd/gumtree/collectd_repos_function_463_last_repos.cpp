static void ovs_stats_port_table_delete_cb(yajl_val jupdates) {
  const char *path[] = {"Port", NULL};
  yajl_val ports = yajl_tree_get(jupdates, path, yajl_t_object);
  pthread_mutex_lock(&g_stats_lock);
  if (ports && YAJL_IS_OBJECT(ports))
    for (size_t i = 0; i < YAJL_GET_OBJECT(ports)->len; i++) {
      ovs_stats_del_port(YAJL_GET_OBJECT(ports)->keys[i]);
    }
  pthread_mutex_unlock(&g_stats_lock);
  return;
}