static int ovs_db_event_thread_init(ovs_db_t *pdb) {
  pdb->event_thread.tid = (pthread_t){0};
  /* init event thread condition variable */
  if (pthread_cond_init(&pdb->event_thread.cond, NULL)) {
    return -1;
  }
  /* init event thread mutex */
  if (pthread_mutex_init(&pdb->event_thread.mutex, NULL)) {
    pthread_cond_destroy(&pdb->event_thread.cond);
    return -1;
  }
  /* Hold the event thread mutex. It ensures that no events
   * will be lost while thread is still starting. Once event
   * thread is started and ready to accept events, it will release
   * the mutex */
  if (pthread_mutex_lock(&pdb->event_thread.mutex)) {
    pthread_mutex_destroy(&pdb->event_thread.mutex);
    pthread_cond_destroy(&pdb->event_thread.cond);
    return -1;
  }
  /* start event thread */
  pthread_t tid;
  if (plugin_thread_create(&tid, NULL, ovs_event_worker, pdb,
                           "utils_ovs:event") != 0) {
    pthread_mutex_unlock(&pdb->event_thread.mutex);
    pthread_mutex_destroy(&pdb->event_thread.mutex);
    pthread_cond_destroy(&pdb->event_thread.cond);
    return -1;
  }
  pdb->event_thread.tid = tid;
  return 0;
}