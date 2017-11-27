static void ovs_stats_conn_terminate() {
  WARNING("Lost connection to OVSDB server");
  pthread_mutex_lock(&g_stats_lock);
  ovs_stats_free_bridge_list(g_bridge_list_head);
  g_bridge_list_head = NULL;
  ovs_stats_free_port_list(g_port_list_head);
  g_port_list_head = NULL;
  pthread_mutex_unlock(&g_stats_lock);
}