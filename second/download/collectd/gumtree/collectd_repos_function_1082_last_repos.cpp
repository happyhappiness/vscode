static int mcelog_shutdown(void) {
  int ret = 0;
  if (mcelog_thread_running) {
    pthread_cancel(g_mcelog_config.tid);
    if (pthread_join(g_mcelog_config.tid, NULL) != 0) {
      ERROR(MCELOG_PLUGIN ": Stopping thread failed.");
      ret = -1;
    }
  }
  pthread_mutex_lock(&g_mcelog_config.dimms_lock);
  mcelog_free_dimms_list_records(g_mcelog_config.dimms_list);
  llist_destroy(g_mcelog_config.dimms_list);
  g_mcelog_config.dimms_list = NULL;
  pthread_mutex_unlock(&g_mcelog_config.dimms_lock);
  pthread_mutex_destroy(&g_mcelog_config.dimms_lock);
  ret = socket_adapter.close(&socket_adapter) || ret;
  pthread_rwlock_destroy(&(socket_adapter.lock));
  return -ret;
}