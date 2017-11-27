static int ovs_db_poll_thread_destroy(ovs_db_t *pdb) {
  if (pthread_equal(pdb->poll_thread.tid, (pthread_t){0})