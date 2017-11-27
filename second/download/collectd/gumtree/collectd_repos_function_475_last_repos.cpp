static int ovs_stats_plugin_init(void) {
  ovs_db_callback_t cb = {.post_conn_init = ovs_stats_initialize,
                          .post_conn_terminate = ovs_stats_conn_terminate};

  INFO("%s: Connecting to OVS DB using address=%s, service=%s, unix=%s",
       plugin_name, ovs_stats_cfg.ovs_db_node, ovs_stats_cfg.ovs_db_serv,
       ovs_stats_cfg.ovs_db_unix);
  /* connect to OvS DB */
  if ((g_ovs_db =
           ovs_db_init(ovs_stats_cfg.ovs_db_node, ovs_stats_cfg.ovs_db_serv,
                       ovs_stats_cfg.ovs_db_unix, &cb)) == NULL) {
    ERROR("%s: plugin: failed to connect to OvS DB server", plugin_name);
    return -1;
  }
  int err = pthread_mutex_init(&g_stats_lock, NULL);
  if (err < 0) {
    ERROR("%s: plugin: failed to initialize cache lock", plugin_name);
    ovs_db_destroy(g_ovs_db);
    return -1;
  }
  return 0;
}