int ovs_db_poll_thread_init(ovs_db_t *pdb) {
  pdb->poll_thread.tid = (pthread_t){0};
  /* init event thread mutex */
  if (pthread_mutex_init(&pdb->poll_thread.mutex, NULL)) {
    return -1;
  }
  /* start poll thread */
  pthread_t tid;
  pdb->poll_thread.state = OVS_DB_POLL_STATE_RUNNING;
  if (plugin_thread_create(&tid, NULL, ovs_poll_worker, pdb,
                           "utils_ovs:poll") != 0) {
    pthread_mutex_destroy(&pdb->poll_thread.mutex);
    return -1;
  }
  pdb->poll_thread.tid = tid;
  return 0;
}