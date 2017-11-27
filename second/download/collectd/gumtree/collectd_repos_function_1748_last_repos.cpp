static int ovs_db_event_thread_destroy(ovs_db_t *pdb) {
  if (pthread_equal(pdb->event_thread.tid, (pthread_t){0})