static _Bool ovs_db_poll_is_running(ovs_db_t *pdb) {
  int state = 0;
  pthread_mutex_lock(&pdb->poll_thread.mutex);
  state = pdb->poll_thread.state;
  pthread_mutex_unlock(&pdb->poll_thread.mutex);
  return state == OVS_DB_POLL_STATE_RUNNING;
}