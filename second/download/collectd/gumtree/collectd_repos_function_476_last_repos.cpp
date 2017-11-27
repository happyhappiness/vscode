static int ovs_stats_plugin_shutdown(void) {
  pthread_mutex_lock(&g_stats_lock);
  DEBUG("OvS Statistics plugin shutting down");
  ovs_db_destroy(g_ovs_db);
  ovs_stats_free_bridge_list(g_bridge_list_head);
  ovs_stats_free_bridge_list(g_monitored_bridge_list_head);
  ovs_stats_free_port_list(g_port_list_head);
  pthread_mutex_unlock(&g_stats_lock);
  pthread_mutex_destroy(&g_stats_lock);
  return 0;
}