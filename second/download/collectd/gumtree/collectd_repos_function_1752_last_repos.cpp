int ovs_db_destroy(ovs_db_t *pdb) {
  int ovs_db_ret = 0;
  int ret = 0;

  /* sanity check */
  if (pdb == NULL)
    return -1;

  /* try to lock the structure before releasing */
  if ((ret = pthread_mutex_lock(&pdb->mutex))) {
    OVS_ERROR("pthread_mutex_lock() DB mutex lock failed (%d)", ret);
    return -1;
  }

  /* stop poll thread */
  if (ovs_db_event_thread_destroy(pdb) < 0) {
    OVS_ERROR("destroy poll thread failed");
    ovs_db_ret = -1;
  }

  /* stop event thread */
  if (ovs_db_poll_thread_destroy(pdb) < 0) {
    OVS_ERROR("stop event thread failed");
    ovs_db_ret = -1;
  }

  pthread_mutex_unlock(&pdb->mutex);

  /* unsubscribe callbacks */
  ovs_db_callback_remove_all(pdb);

  /* close connection */
  if (pdb->sock >= 0)
    close(pdb->sock);

  /* release DB handler */
  pthread_mutex_destroy(&pdb->mutex);
  sfree(pdb);
  return ovs_db_ret;
}