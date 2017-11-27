static void ovs_db_event_post(ovs_db_t *pdb, int event) {
  pthread_mutex_lock(&pdb->event_thread.mutex);
  pdb->event_thread.value = event;
  pthread_mutex_unlock(&pdb->event_thread.mutex);
  pthread_cond_signal(&pdb->event_thread.cond);
}