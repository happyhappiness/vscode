static void ovs_db_callback_add(ovs_db_t *pdb, ovs_callback_t *new_cb) {
  pthread_mutex_lock(&pdb->mutex);
  if (pdb->remote_cb)
    pdb->remote_cb->prev = new_cb;
  new_cb->next = pdb->remote_cb;
  new_cb->prev = NULL;
  pdb->remote_cb = new_cb;
  pthread_mutex_unlock(&pdb->mutex);
}