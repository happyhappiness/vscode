static void ovs_db_callback_remove_all(ovs_db_t *pdb) {
  pthread_mutex_lock(&pdb->mutex);
  while (pdb->remote_cb != NULL) {
    ovs_callback_t *del_cb = pdb->remote_cb;
    pdb->remote_cb = del_cb->next;
    sfree(del_cb);
  }
  pthread_mutex_unlock(&pdb->mutex);
}